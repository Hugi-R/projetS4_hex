#ifndef _GRILLE_H_
#define _GRILLE_H_
#include <stdbool.h>

#define VID 0
#define RED 1
#define BLU 2
#define BBLU1 -1
#define BRED1 -2
#define BBLU2 -11
#define BRED2 -22
typedef struct s_grille *Grille ;

/**
 * @brief construction d'une grille de taille t 
 */
Grille creation( int t );

/**
 * @brief detruit la grille 
 */
void destruction( Grille g);

/**
 * @brief ajoute un pion a une case
 *	@param l la ligne de la case a modifier
 *	@param c la colonne de la case a modifier
 *	@param pion la valeur du pion 
 */
void ajouterPion( Grille g ,int l , int c , int pion );



/**
 * @brief verifie la validiter du coup 
 *	@param l la ligne du coup a verifier
 *	@param c la colonne du coup a verifier
 * @return true si le coup est jouable 
 */
bool coupValide ( Grille g , int l , int c );

/**
 * @brief verifie si un joueur a gagner
 * @return 0 si aucun gagnant sinon retourne la valeur du gagnant
 */
int vainqueur ( Grille g) ;

/**
 * @return la grille sous forme d'un tableau
 */
int* grilleToTab( Grille g );

/**
 * @return la grille sous forme d'un string
 */
char* grilleToString (Grille g );

/**
 * @brief construit une grille depuis un tableau de valeur 
 */
Grille grilleFromTab ( int* tab );

#endif