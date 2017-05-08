#ifndef _SAUVEGARDE_H_
#define _SAUVEGARDE_H_

/*
 * @brief sauvegarde la partie
 * @param [input] g pointeur vers la grille
 * @param [input] nomPartie est le dossier ou se trouvent les sauvegardes de la partie
 * @param [input] historique String contenant l'historique déjà formaté
 * @return retourne le numero de sauvegarde, ou un code erreur (-x)
 * 	code d'erreur:	-1: historique incohérent avec la grille 
 * 			-2: erreur lors de l'ouverture de répertoire nomPartie
 * 			-3: erreur lors de l'ouverture du fichier de sauvegarde
 */
int sauvegarderPartie(Grille g, const char *nomPartie, const char *historique);

/*
 * @brief crée une grille selon la sauvegarde indiquée
 * @param [input] nomPartie est le dossier ou se trouvent les sauvegardes de la partie
 * @param [input] numeroSauvegarde 
 * @param [output] g le pointeur vers la grille initialisé
 * @param [output] historique le String contenant l'historique
 * @return 0 si tout c'est bien passé, code d'erreur sinon
 */
int chargerPartie(const char *nomPartie, int numeroSauvegarde, Grille *g, char *historique);

#endif