//gcc -std=c99 sauvegarde.c grille.c -o test

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "grille.h"
#include "sauvegarde.h"

#define TAILLE_COUP_HISTORIQUE 5

int _verifHistorique(Grille g, const char *historique){
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
			cur++;
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
	free(tabGrid);
	return 1;
}

//penser a free le char* qui est retourné
char* _formaterGrille(Grille g){
	int sizeGrid;
	int *tabGrid = grilleToTab(g);
	sizeGrid=getSizeGrille(g);
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
	free(tabGrid);
	return grilleFormatee;
}

//penser a free le char* qui est retourné
char* _formaterHistorique(const char *historique){
	int l = (int)strlen(historique);
	char *h=malloc(l/TAILLE_COUP_HISTORIQUE*12+1);
	int curseur=0;
	for (int i=0; i<l; i++){
		if (i%TAILLE_COUP_HISTORIQUE == 0){
			if (i != 0){
				h[curseur]='\n';
				curseur++;
			}
			strcat(h, "\\play ");
			curseur += 6;
		}
		h[curseur] = historique[i];
		curseur++;
		h[curseur+1] = '\0';
	}
	return h;
}

int sauvegarderPartie(Grille g, const char *nomPartie, const char *historique){
	int error = 0;
	if (!_verifHistorique(g, historique))
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
	char *grilleFormatee = _formaterGrille(g);
	fprintf(saveFile, "\\hex\n\\dim %d\n", getSizeGrille(g));
	fprintf(saveFile, "\\board\n%s\n\\endboard\n", grilleFormatee);
	free(grilleFormatee);
	if (strcmp(historique, "")){
		char *historiqueFormate = _formaterHistorique(historique);
		fprintf(saveFile, "\\game\n%s\n\\endgame\n", historiqueFormate);
		free(historiqueFormate);
	}
	fprintf(saveFile, "\\endhex\n");
	
	fclose(saveFile);
	closedir(dir);
	return 0;
}

int* _initGrille(FILE *save, int dim){
	const int d = dim;
	int *grille = malloc (sizeof (int)*d*d);
	fscanf(save, "\\board\n");
	char temp[d];
	int pion;
	char c;
	for (int i=0; i < dim; i++){
		fscanf(save, "%s\n", temp);
		for (int j=0; j<d; j++){
			c = temp[j];
			switch (c){
				case 'o': pion = BLU;
				case '*': pion = RED;
				default : pion = VID;
			}
			grille[i*d+j]=pion;
		}
	}
	fscanf(save, "\n\\endboard\n");
	return grille;
}

char* _initHistorique(FILE *save){
	int taille=1;
	char *histo = malloc(taille);
	strcpy(histo, "");
	char coup[TAILLE_COUP_HISTORIQUE];
	while ( fscanf (save, "\\play %c%c%c%c%c\n", &coup[0], &coup[1], &coup[2], &coup[3], &coup[4]) == TAILLE_COUP_HISTORIQUE){
		taille += TAILLE_COUP_HISTORIQUE;
		if (realloc(histo, taille) == NULL)
			return NULL;
		strcat(histo, coup);
	}
	histo[strlen(histo)]='\0';
	return histo;
}

int chargerPartie(const char *nomPartie, Grille *g, char **historique){
	int error = 0;
	char saveName[256];
	sprintf(saveName, "%s/save.txt", nomPartie);
	FILE* save = fopen(saveName, "rt");
	if (save == NULL)
		return --error;
	int dim;
	fscanf(save, "\\hex\n\\dim %d\n", &dim);
	
	int *grille = _initGrille(save, dim);
	*g = grilleFromTab ( grille , dim );
	
	char x, h;
	char coup[6];
	fscanf(save, "%c%c", &x, &h);
	if (h == 'g'){
		fscanf(save, "ame\n");
		*historique = _initHistorique(save);
	}
	else {
		*historique = NULL;
		if (h !='e')
			return --error;
	}
	return 0;
}

int _testSave(const char *nomPartie){
	char *historique = "* 1 1o 3 3* 2 2o 0 0";
	Grille g = creation(5);
	ajouterPion( &g ,1 , 1 , RED );
	ajouterPion( &g ,3 , 3 , BLU );
	ajouterPion( &g ,2 , 2 , RED );
	ajouterPion( &g ,0 , 0 , BLU );
	int retour = sauvegarderPartie(g, nomPartie, historique);
	destruction(g);
	return retour;
}

int _testLoad(const char *nomPartie){
	Grille g;
	char *historique;
	int retour = chargerPartie(nomPartie, &g, &historique);
	printf("historique:\n\033[42m%s\033[00m\n", historique);
	return retour;
}

int main(){
	const char *nomPartie="Partie2";
	printf("\033[31mtestSave\033[00m\n");
	if ( _testSave(nomPartie) == 0){
		printf("\033[31mtestLoad\033[00m\n");
		_testLoad(nomPartie);
	}
	return 0;
}

