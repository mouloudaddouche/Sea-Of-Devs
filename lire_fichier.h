#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "conver.h"

typedef struct { //Strecture du fichier
	int descripteur;
	char * chemin;
	int acces;
} SE_FICHIER;

//Les Fonctions

SE_FICHIER SE_ouverture (const char * chemin,int acces); //Fonction qui permet d'ouvrir un fichier

int SE_Fermeture(SE_FICHIER f); //Fonction qui permet de fermer un fichier

char** SE_LireFichier(const char* chemin); //Fonction qui permet de lire un fichier et sauvgarder ses données dans un tableau de string

int nombre_donne_fichier(const char* chemin);

void free_fichier(char** f);
