#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include <string.h>

typedef struct{
	int id;
	char* nom;
	coord_t vect;
}ACT;

typedef struct{
	ACT* act;
	char type;
}ACTTYPE;

int Est_Adjacent(coord_t b1,coord_t b2);

int postion_adverse_inconnu(navalmap_t* nmap,joueur* jr, int idjr);

int radar_vieux(navalmap_t* nmap,joueur* jr, int idjr,int nbjr);

ACT* Chaine_To_Act(char* s);

void MOV(navalmap_t* nmap, coord_t pos,joueur* jr, int idjr,int nbjr,int pf);

void NON(navalmap_t* nmap,joueur* jr,int idjr,int pf);

void ATK(navalmap_t* nmap,joueur* jr,coord_t vectatk,int idjr,int nbjr,int pf);

void BBS(navalmap_t* nmap,joueur* jr,coord_t casebmb,int idjr,int nbjr,int pf);

void BST(navalmap_t* nmap,joueur* jr,coord_t casevis,int idjr,int nbjr,int pf);

void RPR(joueur* jr,int idjr,int Cmax,int pf);

info_radar* SCN (navalmap_t* nmap,joueur* jr,int idjr,int nbjr,int pf);

char* jouer(navalmap_t* nmap,joueur* jr,int idjr,int nbjr);

void Afficher_ACT(ACT* act);

char* Act_To_Chaine(ACT* act);

ACT* Copie_action(ACT* acti);

ACTTYPE** Actiontype(ACT** tabact,int nbjr);

ACT** Trie_Les_Actions(ACTTYPE** tabi,int nbjr);

void free_tabact(ACT** tabact,int n);
