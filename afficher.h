#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "navalmap.h"


char* Dessiner_Bateau(); //Fonction pour dessiner un bateau

coord_t* Trie_Position(coord_t* tab,int n); //Fonction qui trie les positions de bateau de maniére croissant

void Dessiner_Map(int x,int y,coord_t* bt,int nb); // Fonction qui permet de dessiner la map

void Affichage_Menu_Principale(); //Afficher le menu principale

int Choix_Menu_Principale(); // le choix que l'utilisateur a fait dans le menu principale

void Affichage_Menu_Secondaire(); //Afficher le menu secondaire 

int Choix_Menu_Secondaire(); // le choix que l'utilisateur a fait dans le menu secondaire

void Affichage_Quitter();

