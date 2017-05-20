#include "grille.h"
#include <stdlib.h>
#include <stdio.h>
typedef struct s_node *Node;
 
typedef struct s_groupe{
	Node *tab;
	int size;
} *Groupe;
 
struct s_node{
   Node *cote; // tableau de 6 node, plus pour les bords
   int numero ;
   int color;
   Groupe groupe; // le groupe de la node
};
  
  
struct s_grille{
  Node bord[4];
  int size ;
  Node *Tab; //tableau des nodes
  Groupe *groupesRED; //tableau des groupes
  int nbGroupesRED;
  Groupe *groupesBLU;
  int nbGroupesBLU;
};


int* cherchePont ( Grille g , int numCase , int *nbpont ,  int couleur){
  int *Tab = (int*) malloc (sizeof (int)); 
  *nbpont = 0;
  for ( int i = 0 ;  i <6 ; i++ ){
    if (g->Tab[numCase]->cote[i]->color == VID){
      if (g->Tab[numCase]->cote[i]->cote[(i+1)%6]->color == couleur && g->Tab[numCase]->cote[(i+1)%6]->color == VID){
	*nbpont+=1;
	Tab = (int*) realloc (Tab , sizeof(int*)* *nbpont);
	Tab[*nbpont-1] = g->Tab[numCase]->cote[i]->cote[(i+1)%6]->numero ;
	}
	    
     }
  }
  return Tab;
}

int* coupDejaJouer ( Grille g , int couleur,  int *nbCoup ){
  int *Tab = (int*) malloc (sizeof (int)); 
  *nbCoup = 0;
  Groupe *tabGroupe;
  int nbG ;
  if ( couleur ==  RED ){
	tabGroupe = g->groupesRED;
	nbG = g->nbGroupesRED;
  }else{
	tabGroupe = g->groupesBLU;
	nbG = g->nbGroupesBLU;
  }
  for ( int i = 0 ; i < nbG ; i++ ){
	  for ( int j = 0 ; j < tabGroupe[i]->size ; j++){
		  if (tabGroupe[i]->tab[j]->numero >0 ){
			 *nbCoup = *nbCoup + 1;
			Tab = (int*) realloc (Tab , sizeof(int*)* (*nbCoup ));
			Tab[*nbCoup-1] = tabGroupe[i]->tab[j]->numero;   
			
		  }
	  }
  }
  return Tab;
}
/** @brief fonction interne qui recherche si un entier et dans le tableau d'entier donné en paramètre
 * @param Tab le tableau d'entier a analyser
 * @param Element entier que l'on va chercher dans le tableau
 * @param nbElement nombre d'entier dans le tableau
 * @return true si trouvé
 */
static bool appartient ( int *Tab , int Element , int nbElement){
	bool estDansTab = true ;
	for ( int i  = 0; i < nbElement && estDansTab ; i++){
		estDansTab = ( Tab[i] != Element);
	}
	return estDansTab;
}
	
int* coupPossible ( Grille g , int couleur, int *nbcoup ){
  int pionDejaPoser ;
  int *tabPont;
  int nbPont ;
  int *TabCoup = (int*) malloc (sizeof (int)); 
  int * TabPionPose = coupDejaJouer(g,couleur,&pionDejaPoser);
  if ( pionDejaPoser == 0){
	  *nbcoup = 1 ;
		  if ( couleur == RED ){
			  if ( coupValide(g,g->size-2,1))
				TabCoup[0]=(g->size-1)*(g->size-1);
			  else
				TabCoup[0]=(g->size-1)*(g->size);
		  }else{
			  if (coupValide(g,1,g->size-2))
				TabCoup[0] = g->size + g->size-2 ;
			  else
				 TabCoup[0] = g->size-1;
		  }
	  
  }else{
	  *nbcoup =0 ;
	  for ( int i = 0 ; i< pionDejaPoser ; i++){
		  for ( int j = 0 ; j <6 ; j++){
			  if ( g->Tab[TabPionPose[i]]->cote[j]->color == VID ){
				if (appartient(TabCoup,g->Tab[TabPionPose[i]]->cote[j]->numero,*nbcoup)){
					*nbcoup= *nbcoup+1;
					
					TabCoup = (int*) realloc (TabCoup , sizeof(int*)* (*nbcoup));
					TabCoup[*nbcoup-1]=g->Tab[TabPionPose[i]]->cote[j]->numero;
				}
			}
		  }
		  tabPont = cherchePont(g,g->Tab[TabPionPose[i]]->numero,&nbPont,VID);
		  for ( int i = 0; i < nbPont ; i++ ){
			  if (appartient( TabCoup,tabPont[i] , *nbcoup)){
				*nbcoup= *nbcoup+1;
				TabCoup = (int*) realloc (TabCoup , sizeof(int*)* (*nbcoup));
				TabCoup[*nbcoup-1]= tabPont[i];
			  }
		  }
		  free(tabPont);
	  }
  }
  free(TabPionPose);
  return TabCoup ;
}


int Cal_Distance (Grille g ,  int numCase, int couleur , int direction){
	if ( g->Tab[numCase]->cote[direction]->color <0){
		return 0 ;
	}
	if ( g->Tab[numCase]->cote[(6+direction+1)%6]->color == couleur ){
		return Cal_Distance(g,g->Tab[numCase]->cote[(6+direction+1)%6]->numero,couleur,direction);
	}else if ( g->Tab[numCase]->cote[(direction)]->color == couleur){
		return Cal_Distance(g,g->Tab[numCase]->cote[(direction)]->numero,couleur,direction);
	}else if (g->Tab[numCase]->cote[(6+direction-1)%6]->color == couleur){
		return Cal_Distance(g,g->Tab[numCase]->cote[(6+direction-1)%6]->numero,couleur,direction);
	}else if (g->Tab[numCase]->cote[(direction)]->color == VID ){
		return Cal_Distance(g,g->Tab[numCase]->cote[direction]->numero,couleur,direction) +1;
	}else if (g->Tab[numCase]->cote[(6+direction+1)%6]->color == VID ){
		return Cal_Distance(g,g->Tab[numCase]->cote[(6+direction+1)%6]->numero,couleur,direction)+1;
	}else if (g->Tab[numCase]->cote[(6+direction-1)%6]->color == VID ){
		return Cal_Distance(g,g->Tab[numCase]->cote[(6+direction-1)%6]->numero,couleur,direction)+1;
	}else{
		return 1000;
	}
}
		
	
int pontEnDanger ( Grille g , int couleur,int *TabCoup, int nbcoup ){
	int couleurAdverse ;
	int coup;
	bool Danger = false ;
	if (couleur == RED)
		couleurAdverse = BLU ;
	else
		couleurAdverse = RED ;
	for( int i = 0 ; i< nbcoup && !Danger ; i++ ){
		for ( int j=0 ; j<6 && !Danger; j++){
			if(g->Tab[TabCoup[i]]->cote[j]->color == couleurAdverse){
				if ( g->Tab[TabCoup[i]]->cote[j]->cote[(6+j-1)%6]->color == couleur && g->Tab[TabCoup[i]]->cote[(6+j-1)%6]->color == VID){
					Danger = true ;
					coup = g->Tab[TabCoup[i]]->cote[(6+j-1)%6]->numero;
				}else if (g->Tab[TabCoup[i]]->cote[j]->cote[(6+j+1)%6]->color == couleur && g->Tab[TabCoup[i]]->cote[(6+j+1)%6]->color == VID){
					Danger = true ;
					coup = g->Tab[TabCoup[i]]->cote[(6+j+1)%6]->numero;
				}
			}
		}
	}
	if (!Danger)
		coup = -1;
	return coup ;
}
int minimax ( Grille g , int couleur ){
	int *Tab;
	int nbCoup ;
	Node NodeAAnaliser;
	int case_a_jouer =-1 ;
	int a ,b ;
	int pts_du_coup_a_jouer = -100000000;
	bool pont;
	int pts_du_coup ,direction1 , direction2 ;
	int couleurAdverse ;
	
	
	if (couleur == RED)
		couleurAdverse = BLU ;
	else
		couleurAdverse = RED ;
	Tab = coupDejaJouer(g,couleur,&nbCoup);
	case_a_jouer = pontEnDanger(g,couleur,Tab,nbCoup);
	if (case_a_jouer != -1){
		free(Tab);
		return case_a_jouer;
	}
	free(Tab);
	Tab = coupPossible(g,couleur,&nbCoup);
	
	if ( couleur == RED ){
		direction1 = 0 ;
		direction2 = 3 ;
	}else{
		direction1 = 2 ;
		direction2 = 5 ;
	}
	
	for ( int i = 0 ; i < nbCoup ; i++){
		pts_du_coup = 0 ; 
		pont = true ;
		for ( int j = 0 ; j < 6 ; j ++){
			NodeAAnaliser = g->Tab[Tab[i]]->cote[j];
			if ( NodeAAnaliser->color == couleur){
				pont = false ;
				pts_du_coup += 1;
			}
			if (NodeAAnaliser->color == couleurAdverse && (j == direction1 || j == direction2)  ){
				pts_du_coup+= -2 ;
			}
			if (pont){
				pts_du_coup+= 2;
			}
		}
		a= Cal_Distance(g,g->Tab[Tab[i]]->numero,couleur ,direction1);
		b = Cal_Distance(g,g->Tab[Tab[i]]->numero,couleur ,direction2);
		pts_du_coup= pts_du_coup - ((a +b)*10*g->size);
		if (pts_du_coup > pts_du_coup_a_jouer){
			pts_du_coup_a_jouer = pts_du_coup;
			case_a_jouer = g->Tab[Tab[i]]->numero;
		}
	}
	free(Tab);
	return case_a_jouer;
}

void convertisseur ( Grille g , int numcase , int *ligne , int *colonne ){
	int cas = numcase ;
	*ligne =0;
	*colonne = 0 ;
	while ( cas > g->size ){
		*ligne = *ligne +1;
		cas = cas- g->size;
	}
	*colonne = cas ;
}

		
	  
	  
	  
	  
	 
	  
  