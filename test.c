#include "grille.h"
#include <stdlib.h>
int main(){
  Grille g;
  int tab[25] = {0,0,1,0,2,0,1,0,2,0,1,2,1,0,0,0,2,0,2,2,2,0,1,0,2};
  g = grilleFromTab(tab, 5);
  //verif(g);
  //affichage(g);
  destruction(g);
}

