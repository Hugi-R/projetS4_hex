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
/** fonction interne qui calcul la distance
 *tant que la 1ere direction est bloqué on continue sur la 2e
 *@param numcase numero de la node de depart
 *@param g grille pour accès ;
 *@param dir1 la 1ere direction
 *@param dir2 la 2e direction
 *@param couleur couleur du joueur 
 */ 
static int dist( Grille g , int numcase , int couleur , int dir1 , int dir2);

int* cherchePont ( Grille g , int numCase , int *nbpont ,  int couleur){
  int *Tab = (int*) malloc (sizeof (int)); 
  *nbpont = 0;
  for ( int i = 0 ;  i <6 ; i++ ){
    if (g->Tab[numCase]->cote[i]->color == VID){
      //printf("case %d ",g->Tab[numCase]->cote[i]->numero);
      if (g->Tab[numCase]->cote[i]->cote[(i+1)%6]->color == couleur && g->Tab[numCase]->cote[(i+1)%6]->color == VID){
	//printf(" %d:%d et %d:%d vide \n",g->Tab[numCase]->cote[i]->cote[(i+1)%6]->numero,g->Tab[numCase]->cote[i]->cote[(i+1)%6]->color,g->Tab[numCase]->cote[(i+1)%6]->numero,g->Tab[numCase]->cote[(i+1)%6]->color);
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
	  Tab = (int*) realloc (Tab , sizeof(int*)* (*nbCoup + tabGroupe[i]->size));
	  for ( int j = 0 ; j < tabGroupe[i]->size ; j++){
		  Tab[*nbCoup] = tabGroupe[i]->tab[j]->numero;
		  *nbCoup+=1;
	  }
  }
  return Tab;
}

static bool appartient ( int *Tab , int Element , int nbElement){
	bool estDansTab = true ;
	for ( int i  = 0; i < nbElement && estDansTab ; i++){
		estDansTab = ( Tab[i] != Element);
	}
	return estDansTab;
}
	
int* coupPossible ( Grille g , int couleur, int *nbcoup ){
  int pionDejaPoser ;
  int *tabRecup;
  int n ;
  int *TabCoup = (int*) malloc (sizeof (int)); 
  int * TabPionPose = coupDejaJouer(g,couleur,&pionDejaPoser);
  if ( pionDejaPoser == 0){
	  TabCoup = (int*) realloc (TabCoup , sizeof(int*)* (g->size));
	  *nbcoup = g->size ;
	  for( int i = 0 ;  i < g->size ; i++ ){
		  if ( couleur == RED ){
			  TabCoup[i]= i + g->size;
			  printf(" %d \n",i + g->size);
		  }else{
			  TabCoup[i] = i*g->size +1;
			  printf(" %d \n",i + g->size);
		  }
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
		  tabRecup = cherchePont(g,g->Tab[TabPionPose[i]]->numero,&n,VID);
		  for ( int i = 0; i < n ; i++ ){
			  if (appartient( TabCoup,tabRecup[i] , *nbcoup)){
				*nbcoup= *nbcoup+1;
				TabCoup = (int*) realloc (TabCoup , sizeof(int*)* (*nbcoup));
				TabCoup[*nbcoup-1]= tabRecup[i];
			  }
		  }
	  }
	  
  }
  return TabCoup ;
}



 int calDistance ( Grille g ,  int numcase, int couleur , int direction){
	int cas = numcase ;
	int dis =0;
	int a ,b;
	while(g->Tab[cas]->cote[direction]->color == couleur || g->Tab[cas]->cote[direction]->color == VID){
		cas = g->Tab[cas]->cote[direction]->numero;
		dis++;
	}
	if ( g->Tab[cas]->cote[direction]->color >-1){
		a = dist( g ,cas , couleur , direction,(6+direction+1)%6 );
		b = dist( g ,cas , couleur , direction,(6+direction-1)%6 );
		if ( a>b)
			return b+dis;
		else 
			return a+dis ;
	}else{
		return dis;
	}
		
 }

static int dist( Grille g , int numcase , int couleur , int dir1 , int dir2){
	int cas = numcase ;
	int dis =0;
	bool conti = true;
	while(( g->Tab[cas]->cote[dir1]->color != couleur && g->Tab[cas]->cote[dir1]->color != VID)&& conti){
		if (g->Tab[cas]->cote[dir2]->color == VID){
			cas = g->Tab[cas]->cote[dir2]->numero;
			dis++;
		}else if ( g->Tab[cas]->cote[dir2]->color == couleur ){
			cas = g->Tab[cas]->cote[dir2]->numero;
		}else{
			conti = false ;
		}
	}
	printf("dis = %d \n",dis);
	if ( conti ){
		return dis+calDistance(g,cas,couleur,dir1);
	}else{
		return 1000;
	}
}

void afficheTab ( int *Tab , int nb){
	printf("valeur des %d cases tableau :",nb); 
	for ( int i = 0 ; i < nb ; i ++){
		printf(" %d ",Tab[i]);
	}
	printf("\n");
}
		
	  
	  
	  
	  
	 
	  
  