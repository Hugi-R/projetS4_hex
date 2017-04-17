//gcc sauvegarde.c -o test

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//#include "grille.h"

bool verifHistorique(/*Grille g, Historique h*/){
	return true;
}

int sauvegarder ( /*Grille g, Historique h*/ char slot[1]){
	mkdir("save", S_IRWXU);
	char name[15] = "save/";
	strcat(name, slot);
	strcat(name, ".txt");
	FILE *file;
	file = fopen(name, "wt");
	if (file == NULL){
		perror(name);
		return 1;
	}
	
	if (!verifHistorique(/*g, h*/)){
		fprintf(stderr, "historique incohérent avec la grille\n");
		return 2;
	}
	
	fprintf(file, "\\hex\n\\dim %d\n", 12/*getDim(g)*/);//TODO
	fprintf(file, "\\board\ncontenue de la grille\n\\endboard\n" /*grilleToString(g)*/);//TODO
	fprintf(file, "\\game\nhistorique de jeu\n\\endgame\n" /*historiqueToString(g)*/);//TODO
	fprintf(file, "\\hex\n");
	
	fclose(file);
	return 0;
}
/*
void charger ( // Grille *g, Historique *h 
){
	
	int dim = ; //lecture fichier
	*g = creerGrille(dim);
	setHistorique(*h, .....);
	//remplir grille avec historique
}
*/
int main(){
	sauvegarder( "B");
	return 0;
}