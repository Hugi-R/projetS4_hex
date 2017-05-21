#ifndef IATOOLS_H_
#define IATOOLS_H_
#include "grille.h"


/**
 * @brief return un tableau des node qui font des pont avec la node numCase
 * @param g la grille pour accéder
 * @param numCase numero de la case a analyser
 * @param nbpont sera modifier en le nombre de pont dans la tableau
 * @param couleur de la case final du pont 
 * @return un tableau de pont alloué dynamiquement 
 */
int* cherchePont ( Grille g , int numCase , int *nbpont ,  int couleur);
/**
 * @brief fonction qui rend un tableau des numéros des case déjà joué par le joueur
 * @param couleur couleur du joueur 
 * @param nbCoup sera modifier en le nombre d'element du tableau
 * @return un tableau dynamique 
 */
int* coupDejaJouer ( Grille g , int couleur,  int *nbCoup );

/**
 * @brief fonction qui rend un tableau des numeros des cases qui sont jouable par l'ia
 * l'ia peut jouer que des coup proche ou des coups qui forment un pont avec ses autres pions
 * @param couleur couleur du joueur 
 * @param nbCoup sera modifier en le nombre d'element du tableau
 * @return un tableau dynamique 
 */
int* coupPossible ( Grille g , int couleur, int *nbcoup );

/**
 * @brief calcule la distance d'une node entre ces bords ainsi on se deplace qu'entre les 
 *cases du joueur et les cases vide et on compte les cases vide traversée 
 * @param numcase numero de la case de depart
 * @param couleur couleur du joueur 
 * @param direction direction dans la quelle on se déplace
 * @return 1000 si le pion est bloqué ou le nombre de déplacement minimun avec le bord
 */
int Cal_Distance (Grille g ,  int numCase, int couleur , int direction);

/**
 * @brief analyse chaque coup et garde le coup qui aura le plus de piont .
 * on attribut des points en fonction de plusieur paramètre pour obtenir un score indiquant a quel point le coup est interressant 
 * @param couleur : couleur du joueur
 * @return le numero de la case a jouer 
 */
int minimax ( Grille g , int couleur );
/**
 * @brief convertie un numero de case en une ligne et une colonne 
 * @param numCase numero de la case a convertir 
 * @param ligne est modifier en la valeur de la ligne de la case numCase
 * @param colonne est mofidier en la valeur de la colonne de la case numCase
 */
void convertisseur ( Grille g , int numcase , int *ligne , int *colonne );

#endif