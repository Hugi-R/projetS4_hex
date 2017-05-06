#include "grille.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

typedef struct s_node *Node;
 
struct s_node{
   Node *cote; // tableau de 6 node 
   int numero ;
   int color;
  };
  
  
struct s_grille{
  Node bord[4];
  int size ;
  Node *Tab;
 };
 
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
   g->bord[2]->color = BBLU2 ;
   g->bord[3]->color = BBLU2 ;
   g->bord[0]->numero = -10;
   g->bord[1]->numero = -11;
   g->bord[2]->numero = -12;
   g->bord[3]->numero = -13;
   g->Tab = creaAllNode(t);
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

int vainqueur(Grille g)
{
  NULL;
}


void ajouterPion(Grille *g, int l, int c, int pion)
{
    assert(coupValide(*g,l,c));
    (*g)->Tab[l*(*g)->size+c]->color = pion ;
     
}

int getSizeGrille(Grille g){
  return g->size;
}

int* grilleToTab(Grille g, int *size) 
{
  int t = g->size*g->size;
  *size = t;
  int *tab = (int*) calloc ((size_t)t , sizeof (int));
  for ( int i = 0; i<t;i++){
    tab[i]=g->Tab[i]->color;
    //printf(" %d ",tab[i]);
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

