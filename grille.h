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
 * 	@param g la grille pour accéder 
 *	@param l la ligne de la case a modifier
 *	@param c la colonne de la case a modifier
 *	@param pion la valeur du pion ( RED ou BLU )
 */
void ajouterPion( Grille *g ,int l , int c , int pion );



/**
 * @brief verifie la validiter du coup 
 * 	@param g la grille pour accéder 
 *	@param l la ligne du coup a verifier
 *	@param c la colonne du coup a verifier
 * @return true si le coup est jouable 
 */
bool coupValide ( Grille g , int l , int c );

/**
 * @brief verifie si un joueur a gagner
 * 	@param g la grille pour accéder 
 * @return 0 si aucun gagnant sinon retourne la valeur du gagnant
 */
int vainqueur ( Grille g) ;

/**
 * @return la taille de la grille
 */
int getSizeGrille(Grille g);

/**
 * @param g la grille pour accéder .
 * @return la grille sous forme d'un tableau qui devra est libéré avec free
 */
int* grilleToTab(Grille g);

/**
 * @param g la grille pour accéder 
 * @return la grille sous forme d'un string qui devra être libéré avec free
 */
char* grilleToString (Grille g );

/**
 * @brief construit une grille depuis un tableau de valeur 
 * @param g la grille pour accéder 
 * @param t la taille de la grille
 */
Grille grilleFromTab ( int* tab , int t );

/**
 * @brief return les numeros des différents voisin
 * @param g la grille pour accéder
 * @param node le numero de la node à analyser
 * @param un tableau de 6 entiers correspondant aux voisins
 */
void voisin ( Grille g, int node, int Tab[] );

void affichage (Grille g) ;

void verif (Grille g);

void deplacement ( Grille g);


#endif
