#ifndef IATOOLS_H_
#define IATOOLS_H_
#include "grille.h"


/**
 * @brief return un tableau des node qui font des pont avec la node numCase
 * @param g la grille pour accéder
 * @param numCase numero de la case a analyser
 * @param nbpont sera modifier en le nombre de pont dans la tableau
 * @return un tableau de pont alloué dynamiquement 
 */
int* cherchePont ( Grille g , int numCase , int *nbpont );
#endif