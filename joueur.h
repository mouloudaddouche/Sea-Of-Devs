#include <stdio.h>
#include <stdlib.h>
#include "conver.h"
#include "navalmap.h"

typedef struct{
	int id_ship_ennemi;
	coord_t pos;
	int C;
	int K;
}info_radar;

typedef struct{
	int id;
	int C;
	int K;
	int BE;
	info_radar* rdr;
	
}joueur;

joueur* Init_Joueur(int n,char* s1,char* s2);

void Affich_Joueur(navalmap_t* nvmap,joueur* jr,int n);

coord_t* Copier_tab_cord_joueurs(coord_t* tab_orig,int nbjr);

void Afficher_Radar(navalmap_t* bmap,joueur* jr,int id);

void Actualiser_Joueur(joueur* jr,int nbjr);

int Coque_Max(joueur* jr, int nbjr);

int Kerosene_Max(joueur* jr, int nbjr);

void Afficher_Gagnant(joueur* jr,int nbjr);

int nb_des_gagnant(joueur* jr,int nbjr);

void Actualiser_Map(navalmap_t* nmap,joueur*jr,int nbjr);

void free_joueur(joueur* jr);
