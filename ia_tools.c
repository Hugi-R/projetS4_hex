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

int* cherchePont ( Grille g , int numCase , int *nbpont ){
  int *Tab = (int*) malloc (sizeof (int)); 
  *nbpont = 0;
  for ( int i = 0 ;  i <6 ; i++ ){
    if (g->Tab[numCase]->cote[i]->color == VID){
      printf("case %d ",g->Tab[numCase]->cote[i]->numero);
      if (g->Tab[numCase]->cote[i]->cote[(i+1)%6]->color == VID && g->Tab[numCase]->cote[(i+1)%6]->color == VID){
	printf(" %d:%d et %d:%d vide \n",g->Tab[numCase]->cote[i]->cote[(i+1)%6]->numero,g->Tab[numCase]->cote[i]->cote[(i+1)%6]->color,g->Tab[numCase]->cote[(i+1)%6]->numero,g->Tab[numCase]->cote[(i+1)%6]->color);
	*nbpont+=1;
	Tab = (int*) realloc (Tab , sizeof(int*)* *nbpont);
	Tab[*nbpont-1] = g->Tab[numCase]->cote[i]->cote[(i+1)%6]->numero ;
      }else
	printf(" %d:%d et %d:%d pas vide \n",g->Tab[numCase]->cote[i]->cote[(i+1)%6]->numero,g->Tab[numCase]->cote[i]->cote[(i+1)%6]->color,g->Tab[numCase]->cote[(i+1)%6]->numero,g->Tab[numCase]->cote[(i+1)%6]->color);
    }else
      printf("\n");
  }
  return Tab;
}

