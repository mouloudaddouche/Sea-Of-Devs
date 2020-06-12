#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include "action.h"
#include "SoD.h"

#define TAILLE_MESSAGE 10

char messageEcrire[TAILLE_MESSAGE];

char messageLire[TAILLE_MESSAGE];

void creat_process(int n); //Fonction qui permet de creer les n processus

void FILS_PERE(navalmap_t* nmap,joueur*jr,int n,ACT** tab_act,int mode);

void PERE_FILS(int n);

void Pere_Fils_etat(navalmap_t* nmap,joueur* jr,ACT** tab_act,int nbjr);

