#include "grille.h"
#include <stdlib.h>
int main(){
  Grille g;
  g = creation(100);
  verif(g);
  //affichage(g);
  destruction(g);
}

