#include "grille.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct s_node *Node;
 
struct s_node{
   Node *cote; // tableau de 6 node 
   int numero ;
   int color;
  };
  
  
struct s_grille{
  Node bord[4];
  int size ;
 };

Grille creaGrille( int t){
   Grille g = (Grille) malloc ( sizeof (struct s_grille));
   if (g == NULL){
       printf("Unable to allocate memory");
       exit(3);
   }
   g->size = t ;
   for ( int i = 0 ; i<4 ; i++ ){
     g->bord[i] = (Node) malloc (sizeof (struct s_node));
     g->bord[i]->cote = (Node*) calloc ((size_t)6,sizeof(struct s_node));
   } 
   g->bord[0]->color = BRED1 ;
   g->bord[1]->color = BBLU1 ;
   g->bord[2]->color = BBLU2 ;
   g->bord[3]->color = BBLU2 ;
   g->bord[0]->numero = g->bord[1]->numero = g->bord[2]->numero = g->bord[3]->numero = -1;
   
   return g ;
}
Node creaNode( int color , int numero , Node n1 , Node n2 ,Node n3, Node n4 ,Node n5 ,Node n6){
  Node n = (Node) malloc (sizeof ( struct s_node )) ;
  if ( n == NULL){
      printf("Unable to allocate memory");
      exit(1);
  }
  n->color = color ;
  n->numero = numero ;
  n->cote = (Node*) calloc ((size_t)6,sizeof(struct s_node));
  for ( int i = 0 ; i<6 ; i++ ){
    n->cote[i] = (Node) malloc (sizeof (struct s_node));
  }
  if (n->cote == NULL){
      printf("Unable to allocate memory");
      exit(2);
  }
  n->cote[0] = n1;
  n->cote[1] = n2;
  n->cote[2] = n3;
  n->cote[3] = n4;
  n->cote[4] = n5;
  n->cote[5] = n6;
  return n;
}
void creaBordDuGraph( Grille* g ){
 Node n = creaNode( VID ,0,(*g)->bord[0],(*g)->bord[0],NULL,NULL,(*g)->bord[3],(*g)->bord[3]);
 (*g)->bord[0]->cote[0] = n;
 (*g)->bord[3]->cote[(*g)->size-1] = n;
  Node m ;
  int cpt = 1 ;
 for ( int i = 0 ; i < 2 ; i++){
   for ( int j = 1 ; j< (*g)->size ; j++ ){
     if ( i ==0 ){
      m = creaNode(VID ,cpt ,(*g)->bord[0],(*g)->bord[0],NULL,NULL,NULL,n);
      n->cote[2] = m ;
      (*g)->bord[0]->cote[j] = m ;
      if ( j == (*g)->size-1){
	m->cote[2] = (*g)->bord[1];
	(*g)->bord[1]->cote[0] = m ;      
      }
      n = m ; 
      cpt++;
    }else{
      cpt += (*g)->size ;
      m = creaNode(VID,cpt,n,n->cote[2],NULL,NULL,(*g)->bord[3],(*g)->bord[3]);
      n->cote[3] = m;
      (*g)->bord[3]->cote[(*g)->size-(j+1)] = m ;
      if ( j == (*g)->size-1 ){
	m->cote[3] = (*g)->bord[2];
	(*g)->bord[2]->cote[(*g)->size-1] = m ;
      }
      n = m ;
    }
   }
   n = (*g)->bord[0]->cote[0];
   cpt = 0;
  }
}  

void creaGraph( Grille *g){
  Node m ,n ;
  int cpt ;
  for ( int i =1 ; i < (*g)->size ; i++ ){
    m = (*g)->bord[3]->cote[(*g)->size-(1+i)];
    m->cote[1] = m->cote[0]->cote[2];
    for ( int j = 1 ; j < (*g)->size ; j++){
      cpt = (i * (*g)->size) + j ;
      n = creaNode(VID,cpt,m->cote[1],m->cote[1]->cote[2],NULL,NULL,NULL,m);
      m->cote[2] = n;
      m->cote[1]->cote[3] = n ;
      if ( j == 1){
	n->cote[4] = m->cote[3] ;
      }
      if ( j == (*g)->size-1){
	n->cote[2] = (*g)->bord[1];
	(*g)->bord[1]->cote[i] = n ;
      }else{
      m->cote[1]->cote[2]->cote[4] = n ;	
      }
      if ( i == (*g)->size-1){
	n->cote[4] = n->cote[3] = (*g)->bord[2];
	(*g)->bord[2]->cote[(*g)->size-(j+1)] = n;
      }
      m = n ;
    }
  }
}

void affichage (Grille g){
  Node n;
  printf("bord[3] :\n");
 for (int i=g->size-1; i>=0;i--){
   n = g->bord[3]->cote[i];
   for (int j=0; j <g->size;j++){
     printf(" %d ",n->numero);
     n = n->cote[2];
   }
 } 
 printf("\nbord[0] :\n");
 for (int k=0; k<g->size;k++){
   n = g->bord[0]->cote[k];
   for (int o=0; o <g->size;o++){
     printf(" %d ",n->numero);
     n = n->cote[3];
   }
 }
  printf("\nbord[1] :\n");
 for (int k=0; k<g->size;k++){
   n = g->bord[1]->cote[k];
   for (int o=0; o <g->size;o++){
     printf(" %d ",n->numero);
     n = n->cote[5];
   }
 }
 printf("\nbord[2] :\n");
 for (int i=g->size-1; i>=0;i--){
   n = g->bord[2]->cote[i];
   for (int j=0; j <g->size;j++){
     printf(" %d ",n->numero);
     n = n->cote[0];
   }
 }
  printf("\n");
}

void deplacement(Grille g)
{
  int o = 0;
  Node n = g->bord[0]->cote[0];
  while ( o != 9){
    printf(" veuillez saisir une direction");
    scanf("%d",&o);
    if( o <6){
      n = n->cote[o];
      printf("numero de votre case : %d \n",n->numero);
    }
  }
}

Grille creation( int t )
{
  Grille g = creaGrille(t);
  creaBordDuGraph(&g);
  creaGraph(&g);
  return g ;
}
