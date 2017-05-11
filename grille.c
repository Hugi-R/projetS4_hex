#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "grille.h"

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
 
Groupe _creaGroupe(){
	Groupe g = (Groupe) malloc( sizeof(struct s_groupe) );
	g->tab = NULL;
	g->size = 0;
}

void _destroyGroupe(Groupe grp){
	free(grp->tab);
	free(grp);
}

Groupe _addGroupe(Groupe *grp, Node n){
	(*grp)->size += 1;
	(*grp)->tab = (Node*) realloc((*grp)->tab, (size_t)(*grp)->size*sizeof(Node) );
	(*grp)->tab[(*grp)->size - 1] = n;
}

/** Fusionne 2 groupes. Le groupe suplémentaire est free
 * @return le groupe fusionné.
 */
Groupe _fusion2Groupes(Groupe *grp1, Groupe *grp2){
	Groupe new = NULL;
	Groupe old = NULL;
	if( (*grp1)->size > (*grp2)->size ){
		new = *grp1;
		old = *grp2;
	} else {
		new = *grp2;
		old = *grp1;
	}
	for( int i = 0; i<old->size; i++ ){
		old->tab[i]->groupe = new;
		_addGroupe(&new, old->tab[i]);
	}
	_destroyGroupe(old);
	return new;
}

/** Fusionne 3 groupes. Les groupes suplémentaires sont free
 * @return le groupe fusionné.
 */
Groupe _fusion3Groupes(Groupe *grp1, Groupe *grp2, Groupe *grp3){
	Groupe new = NULL;
	Groupe old1 = NULL;
	Groupe old2 = NULL;
	if( (*grp1)->size > (*grp2)->size ){
		old1 = *grp2;
		if( (*grp1)->size > (*grp3)->size ){
			new = *grp1;
			old2 = *grp3;
		} else {
			new = *grp3;
			old2 = *grp1;
		}
	} else {
		old1 = *grp1;
		if( (*grp2)->size > (*grp3)->size ){
			new = *grp2;
			old2 = *grp3;
		} else {
			new = *grp3;
			old2 = *grp2;
		}
	}
	
	for( int i = 0; i<old1->size; i++ ){
		old1->tab[i]->groupe = new;
		_addGroupe(&new, old1->tab[i]);
	}
	for( int i = 0; i<old2->size; i++ ){
		old2->tab[i]->groupe = new;
		_addGroupe(&new, old2->tab[i]);
	}
	_destroyGroupe(old1);
	_destroyGroupe(old2);
	return new;
}

Node* creaAllNode( int t ){
    int cpt =t*t;
    Node* tab = (Node*) calloc ((size_t)cpt,sizeof(Node )); // a faire dynamiquement
    Node n ;
    for ( int i = 0 ; i < cpt ;i++){
      n = (Node) malloc (sizeof ( struct s_node )) ;
      if ( n == NULL){
		printf("Unable to allocate memory");
		exit(1);
      }
      n->cote = (Node*) calloc ((size_t)t,sizeof(struct s_node));
      n->color = VID ;
      n->numero = i ;
	  n->groupe = NULL;
      tab[i]=n;
    }
    return tab ;
}

Grille creaGrille( int t){
   Grille g = (Grille) malloc ( sizeof (struct s_grille));
   if (g == NULL){
       printf("Unable to allocate memory");
       exit(3);
   }
   g->size = t ;
   for ( int i = 0 ; i<4 ; i++ ){
     g->bord[i] = (Node) malloc (sizeof (struct s_node));
     g->bord[i]->cote = (Node*) calloc ((size_t)t,sizeof(struct s_node));
   } 
   g->bord[0]->color = BRED1 ;
   g->bord[1]->color = BBLU1 ;
   g->bord[2]->color = BRED2 ;
   g->bord[3]->color = BBLU2 ;
   g->bord[0]->numero = -10;
   g->bord[1]->numero = -11;
   g->bord[2]->numero = -12;
   g->bord[3]->numero = -13;
   g->Tab = creaAllNode(t);
   g->groupesRED = NULL;
   g->nbGroupesRED = 0;
   g->groupesBLU = NULL;
   g->nbGroupesBLU = 0;
   return g ;
}

void creaBordHautGraph (Grille *g){
  int t = (*g)->size ;
  Node n ;
  for ( int i = 0 ; i < t ; i++){
      n = (*g)->Tab[i];
      if ( i == 0){
	  (*g)->bord[3]->cote[t-1] = n ;
	   n->cote[5] = n->cote[4] = (*g)->bord[3];
      }else{
	  n->cote[5] = (*g)->Tab[i-1] ;
	  (*g)->Tab[i-1]->cote[2] = n ;
	  n->cote[4] = (*g)->Tab[i+t-1];
      }
      if (i == t-1){
	  (*g)->bord[1]->cote[0] = n;
	  n->cote[2] = (*g)->bord[1] ;
      }
      (*g)->bord[0]->cote[i] = n ;
      n->cote[0] = n->cote[1] = (*g)->bord[0] ;
      n->cote[3] = (*g)->Tab[i+t] ; 
  }
  
}

void creaMilieuGraph (Grille *g){
  Node n ; 
  int t = (*g)->size ;
  int cpt ;
  for ( int i = 1 ; i < t-1; i++){
    for ( int j = 0 ; j < t ; j++){
      cpt = i*t+j ;
      n = (*g)->Tab[cpt];
      if (j == 0){
	(*g)->bord[3]->cote[t-(i+1)] = n;
	n->cote[5] = n->cote[4] = (*g)->bord[3];
	
      }else{
	n->cote[5] = (*g)->Tab[cpt-1];
	n->cote[4] = (*g)->Tab[cpt+t-1];
      }
      n->cote[3] = (*g)->Tab[cpt+t];
      n->cote[0] = (*g)->Tab[cpt-t];
      if (j == t-1){
	(*g)->bord[1]->cote[i] = n;
	n->cote[1] = n->cote [2] = (*g)->bord[1] ;
      }else{
	n->cote[1] = (*g)->Tab[cpt-(t-1)] ;
	n->cote[2] = (*g)->Tab[cpt+1];
      }
    }
  }
}

void creaBordBasGraph (Grille *g){
  int t = (*g)->size ;
  Node n ;
  int cpt = (t*(t-1));
  for ( int i = 0; i < t ; i++){
      n = (*g)->Tab[cpt] ;
      
      if ( i == 0){
	  (*g)->bord[3]->cote[0] = n ;
	   n->cote[5] = (*g)->bord[3];
      }else{
	  n->cote[5] = (*g)->Tab[cpt-1] ;
	  (*g)->Tab[cpt-1]->cote[2] = n ;
	  n->cote[4] = (*g)->bord[2];
      }
      if (i == t-1){
	  (*g)->bord[1]->cote[t-1] = n;
	  n->cote[1] = n->cote[2]= (*g)->bord[1] ;
      }else{
	n->cote[1] = (*g)->Tab[cpt-t+1];
      }
      n->cote[4] = n->cote[3] = (*g)->bord[2] ;
      n->cote[0] = (*g)->Tab[cpt-t] ;
      (*g)->bord[2]->cote[t-(1+i)] = n;
      cpt ++ ;
   }
}
  

Grille creation( int t )
{
  Grille g = creaGrille(t);
  creaBordHautGraph(&g);
  creaMilieuGraph(&g);
  creaBordBasGraph(&g);
  return g ;
}

void verif(Grille g){
  for (int i = 0 ; i < g->size *g->size; i++){
    printf("\ncote de %d ",i); 
      for (int j = 0 ; j< 6 ; j++){
	printf(": %d ",g->Tab[i]->cote[j]->numero);
      }
  }
  printf("\n");
}

void destructionNode ( Node n ) {
  free(n->cote);
  free(n);
}

void destruction(Grille g)
{
    for (int i=0; i<(g->size*g->size);i++){
      destructionNode(g->Tab[i]);
    }
    
    free(g->Tab);
    
    for ( int i=0 ; i<4 ; i++ ){
      destructionNode(g->bord[i]);
    }
    free(g->bord);
}

bool coupValide(Grille g, int l, int c)
{
  return g->Tab[l*(g->size)+c]->color == VID;
}

//----Fonctions utilisées par _fixGroupes---
bool _grpNotInTab(Groupe *grTab, int size, Groupe grp){
	bool ok = true;
	for(int i = 0; i<size && ok; i++){
		ok = ok && (grTab[i] != grp);
	}
	return ok;
}

bool _nodeNotInTab(Node *nTab, int size, Node n){
	bool ok = true;
	for(int i = 0; i<size && ok; i++){
		ok = ok && (nTab[i] != n);
	}
	return ok;
}

void _addToTab(Groupe *grTab[], int *size, Groupe grp){
	*size += 1;
	*grTab = (Groupe*) realloc(*grTab, (size_t)(*size)*sizeof(Groupe) );
	(*grTab)[*size - 1] = grp;
}

void _removeFromTab(Groupe *grTab[], int *size, Groupe grp){
	int i;
	for(i = 0; (i<*size) && ((*grTab)[i] != grp); i++);
	if(i<*size){
		*size -= 1;
		(*grTab)[i] = (*grTab)[*size];
		*grTab = (Groupe*) realloc(*grTab, (size_t)(*size)*sizeof(Groupe) );
	}
}

Node _bordNode(Node n){
	assert(n->color != VID);
	int b1,b2;
	if(n->color == BLU){
		b1 = BBLU1;
		b2 = BBLU2;
	} else {
		b1 = BRED1;
		b2 = BRED2;
	}
	for(int i = 0; i<6; i++){
		if(n->cote[i]->color == b1 || n->cote[i]->color == b2)
			return n->cote[i];
	}
	return NULL;
}
//-----------------------------------------

/**
 * Met à jour les groupe en fonction de l'ajout d'une node
 */
void _fixGroupes(Grille *g, Node *n){
	Groupe *grTab = NULL;
	int *nbGroupes = NULL;
	if( (*n)->color == RED ){
		grTab = (*g)->groupesRED;
		nbGroupes = &((*g)->nbGroupesRED);
	} else if( (*n)->color == BLU ){
		grTab = (*g)->groupesBLU;
		nbGroupes = &((*g)->nbGroupesBLU);
	} else {
		return;
	}
	
	Groupe gr[3]; //il y a max 3 groupes differents touchant une node
	int nbGr = 0;
	for(int i = 0; i<6; i++){
		if( (*n)->cote[i]->color == (*n)->color ){
			if( ((*n)->cote[i]->groupe != NULL) && (_grpNotInTab(gr, nbGr, (*n)->cote[i]->groupe)) )
				gr[nbGr++] = (*n)->cote[i]->groupe;
		}
	}
	
	Groupe grp = NULL;
	switch(nbGr){
		case 0 :
			grp = _creaGroupe();
			_addGroupe(&grp, *n);
			(*n)->groupe = grp;
			_addToTab( &grTab, nbGroupes, grp );
			break;
		case 1 :
			grp = gr[0];
			_addGroupe(&grp, *n);
			(*n)->groupe = grp;
			break;
		case 2 :
			grp = _fusion2Groupes(&gr[0], &gr[1]);
			_addGroupe(&grp, *n);
			(*n)->groupe = grp;
			if(grp != gr[0]){
				_removeFromTab(&grTab, nbGroupes, gr[0]);
			} else {
				_removeFromTab(&grTab, nbGroupes, gr[1]);
			}
			break;
		case 3 :
			grp = _fusion3Groupes(&gr[0], &gr[1], &gr[2]);
			_addGroupe(&grp, *n);
			(*n)->groupe = grp;
			if(grp == gr[0]){
				_removeFromTab(&grTab, nbGroupes, gr[1]);
				_removeFromTab(&grTab, nbGroupes, gr[2]);
			} else {
				_removeFromTab(&grTab, nbGroupes, gr[0]);
				if(grp == gr[1]){
					_removeFromTab(&grTab, nbGroupes, gr[2]);
				} else {
					_removeFromTab(&grTab, nbGroupes, gr[1]);
				}
			}
			break;
		default:
			fprintf(stderr, "ERREUR : dans _fixGroupes nbGr>3. Fermeture.\n");
			exit(4);
	}
	
	Node b = _bordNode(*n);
	if(b != NULL){
		if( _nodeNotInTab((*n)->groupe->tab, (*n)->groupe->size, b) ){
			_addGroupe( &((*n)->groupe), b );
		}
	}
}

int vainqueur(Grille g)
{
	bool b1,b2;
	for(int i = 0; i < g->nbGroupesBLU; i++){
		b1 = false;
		b2 = false;
		for(int j = 0; j < g->groupesBLU[i]->size; j++){
			if( g->groupesBLU[i]->tab[j]->color == BBLU1 ) b1 = true;
			if( g->groupesBLU[i]->tab[j]->color == BBLU2 ) b2 = true;
		}
		if(b1 && b2) return BLU;
	}
	for(int i = 0; i < g->nbGroupesRED; i++){
		b1 = false;
		b2 = false;
		for(int j = 0; j < g->groupesRED[i]->size; j++){
			if( g->groupesRED[i]->tab[j]->color == BRED1 ) b1 = true;
			if( g->groupesRED[i]->tab[j]->color == BRED2 ) b2 = true;
		}
		if(b1 && b2) return RED;
	}
	return VID;
}

void ajouterPion(Grille *g, int l, int c, int pion)
{
    assert(coupValide(*g,l,c));
    Node n = (*g)->Tab[l*(*g)->size+c];
    n->color = pion;
    if(n->color != VID)
	_fixGroupes(g, &n);
}

int getSizeGrille(Grille g){
  return g->size;
}

int* grilleToTab(Grille g) 
{
  int t = g->size*g->size;
  int *tab = (int*) calloc ((size_t)t , sizeof (int));
  for ( int i = 0; i<t;i++){
    tab[i]=g->Tab[i]->color;
  }
  return tab ;
}

char* grilleToString(Grille g)
 {
   int t = g->size*g->size;
   char *tab = (char*) malloc ( sizeof (char)*t+1);
   for ( int i = 0; i<t;i++){
     tab[i] = (char)(g->Tab[1]->color)+48;
   }
   tab[t] = '\0';
  return tab ;
}

Grille grilleFromTab(int* tab, int t)
{
  Grille g = creation(t);
  for ( int i = 0; i<t;i++){
    for (int j = 0 ;j<t;j++){
		if(tab[i*t+j] != VID)
			ajouterPion(&g,i,j,tab[i*t+j]);
    }
  }
  return g ;
}

void voisin(Grille g, int node , int Tab[])
{
  for (int i = 0 ; i <6 ; i++){
    Tab[i] = g->Tab[node]->cote[i]->numero;
  }
}

