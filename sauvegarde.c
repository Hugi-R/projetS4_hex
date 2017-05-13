//gcc -std=c99 sauvegarde.c grille.c -o test

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "grille.h"
#include "sauvegarde.h"

int verifHistorique(Grille g, const char *historique){
	char pion, x, y;
	const int size = getSizeGrille(g);
	int tab[size][size];
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			tab[i][j]='.';
		}
	}
	int cur=0;
	int couleur;
	int longueur = (int)strlen(historique);
	if ( longueur != 0){
		while(cur < longueur){
			pion = historique[cur];
			switch (pion){
				case 'o': couleur = BLU;break;
				case '*': couleur = RED;break;
				default : couleur = VID;
			}
			cur+=2;
			x = historique[cur]-'0';
			cur+=2;
			y = historique[cur]-'0';
			cur+=2;
			tab[x][y]=couleur;
		}
	}
	int *tabGrid;
	tabGrid = grilleToTab(g);
	
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			if (tab[x][y]!=tabGrid[x*size+y])
				return 0;
		}
	}
	return 1;
}

char* formaterGrille(Grille g){
	int sizeGrid = getSizeGrille(g);
	int *tabGrid = malloc (sizeof (int)*sizeGrid*sizeGrid);
	tabGrid = grilleToTab(g);
	char *grilleFormatee = malloc (sizeGrid*(sizeGrid+1)+1);
	int curseur = 0;
	for (int i = 0; i<sizeGrid*sizeGrid; i++){
		if (i%sizeGrid==0 && i != 0){
			grilleFormatee[curseur] = '\n';
			curseur ++;
		}
		switch (tabGrid[i]){
			case RED : grilleFormatee[curseur] = '*';break;
			case BLU : grilleFormatee[curseur] = 'o';break;
			default  : grilleFormatee[curseur] = '.';
		}
		curseur ++;
	}
	return grilleFormatee;
}

char* formaterHistorique(const char *historique){ //TODO
	char *h=malloc(256);
	strcat(h, historique);
	return h;
}

int sauvegarderPartie(Grille g, const char *nomPartie, const char *historique){
	int error = 0;
	if (!verifHistorique(g, historique))
		return --error;
	mkdir(nomPartie, S_IRWXU);
	DIR *dir = opendir (nomPartie);
	if (dir == NULL)
		return --error;
	//ouverture du fichier de sauvegarde
	char save[256];
	sprintf(save, "%s/save.txt", nomPartie);
	FILE *saveFile = fopen (save, "wt");
	if (saveFile == NULL)
		return --error;
	//écriture formatée dans le fichier saveFile
	char *grilleFormatee = formaterGrille(g);
	fprintf(saveFile, "\\hex\n\\dim %d\n", getSizeGrille(g));
	fprintf(saveFile, "\\board\n%s\n\\endboard\n", grilleFormatee);
	if (strcmp(historique, "")){
		char *historiqueFormate = formaterHistorique(historique);
		fprintf(saveFile, "\\game\n%s\n\\endgame\n", historiqueFormate);
	}
	fprintf(saveFile, "\\endhex\n");
	
	fclose(saveFile);
	closedir(dir);
	return 0;
}

int chargerPartie(const char *nomPartie, int numeroSauvegarde, Grille *g, char *historique){
	
	int dim = 0; //lecture fichier
	int *grille;//lecture fichier
	*g = grilleFromTab ( grille , dim );
	return 0;
}

int main(){
	char *historique = "* 1 1 o 3 3";
	Grille g = creation(4);
	ajouterPion( &g ,1 , 1 , RED );
	ajouterPion( &g ,3 , 3 , BLU );
	
	sauvegarderPartie(g, "Partie1", historique);
	
	//destruction(g);
	return 0;
}
/* TODO
 * 	sauvegarderPartie
 * 		incrementation nom fichier, gestion index
 * 		formaterHistorique				quand format defini
 * 	chargerPartie
 */
