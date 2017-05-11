#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "grille.h"

int nbTestvalide = 0 ;
int nbTestTotal = 0 ;

void test ( char* message , bool resultat){
  printf(" %-60s [%s]\n", message, (resultat ? "OK" : "KO"));
  if (resultat) 
    nbTestvalide ++ ;
  nbTestTotal ++ ;
}

int main (){
  int taille = 5 ;
  char * msg ;
  printf("génération des tests : \n");
  Grille g = creation(taille); 
  test("creation d'une grille",verif(g));
  test("test de coup valide dans une case de la grille vide",coupValide(g,taille-2,taille-2));
  test("test de coup valide hors de la grille ",!coupValide(g,taille+1,taille+1));
  if (coupValide(g,taille-2,taille-2))
    ajouterPion(&g,taille-2,taille-2,BLU);
  test("test de coup valide sur une case remplie",!coupValide(g,taille-2,taille-2));
  destruction(g);
  g = creation(3);
    if (coupValide(g,0,0))
      ajouterPion(&g,0,0,RED);
    if (coupValide(g,0,1))
      ajouterPion(&g,0,1,RED);
    if (coupValide(g,2,1))
      ajouterPion(&g,2,1,RED);
    if (coupValide(g,2,2))
      ajouterPion(&g,2,2,RED);
  test("test de 4 ajouts avec grilleToString ",strcmp("110000011",msg = grilleToString(g))==0);
  free(msg);
  test("test vainqueur sans vainqueur",vainqueur(g) == 0);
  if (coupValide(g,1,1))
      ajouterPion(&g,1,1,RED);
  test("test vainqueur avec un vainqueur",vainqueur(g) == RED);
  destruction(g);
  printf("resultat des tests : %d/%d test(s) valide \n",nbTestvalide,nbTestTotal);
  return 0 ;
}
  