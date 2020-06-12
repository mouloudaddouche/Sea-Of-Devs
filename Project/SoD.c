#include "processus.h"
#include "conver.h"
#include "navalmap.h"
#include "lire_fichier.h"
#include "conver.h"
#include "nm_rect.h"
#include <string.h>
#include "afficher.h"
#include <sys/wait.h>

elt* tab;
pid_t pid;
int descripteurtube4[2];
int nbj;
int main(int argc, char* argv[]){
	if (argc !=2){perror("La ligne de commande n'est pas compatible pour lancer le jeu !!!\n"); exit(1);}
	if( nombre_donne_fichier(argv[1]) !=7){perror("Le Fichier en entre n'est pas compatible pour lancer le jeu !!!\n"); exit(2);}
   initNavalMapLib();
   char** tab_f=SE_LireFichier(argv[1]); // Lire le fichier d'entré
   coord_t cd=construire_cord(StrToInt(tab_f[1]),StrToInt(tab_f[2])); //Transformer x et y d'entrés en un struct coord
   map_t map_type;
   if(!strcmp(tab_f[0],"rectangle")) map_type=MAP_RECT; // verification du type de map d'entré
   else {perror(" Type de map n'est pas admis \n"); exit(3);}
    navalmap_t* nvmap;
    nvmap=init_navalmap(map_type,cd,StrToInt(tab_f[3])); //initialisation de la map
	placeRemainingShipsAtRandom(nvmap); // placé les bateaux non placés
	joueur* jr=Init_Joueur(nvmap->nbShips,tab_f[4],tab_f[5]); //Initialisation tableau de joueurs
	ACT** tab_act=(ACT**)malloc(StrToInt(tab_f[3])*sizeof(ACT*));
	etiq_1 : Affichage_Menu_Principale();
	pipe(descripteurtube4);
	int choix1=Choix_Menu_Principale();
	switch(choix1){
		case 1:{ 	// SignlePlayer
					Affichage_Menu_Secondaire();
					int choix2=Choix_Menu_Secondaire();
						switch(choix2){
							case 1 :{ // JR VS IA
							system("clear");
								printf("Debut:");
								coord_t* tab_aff;
								ACTTYPE** actt;
								ACT** acttrie;
								int stat;
								tab_aff=Copier_tab_cord_joueurs(nvmap->shipPosition,nvmap->nbShips);
								Affich_Joueur(nvmap,jr,nvmap->nbShips);
								Dessiner_Map(cd.x,cd.y,Trie_Position(tab_aff,nvmap->nbShips),nvmap->nbShips); // Dessiner Map
								for(int i=1;i<=StrToInt(tab_f[6]);i++){
									if (i==1)creat_process(StrToInt(tab_f[3]));
									if (pid>0)printf("Tour %d : \n",i);
									PERE_FILS(StrToInt(tab_f[3]));
									FILS_PERE(nvmap,jr,	StrToInt(tab_f[3]),tab_act,1);
									if (pid>0){
									actt=Actiontype(tab_act,StrToInt(tab_f[3]));
									acttrie=Trie_Les_Actions(actt,StrToInt(tab_f[3]));
									printf("Les Actions : \n");
									Executer_Les_Actions(nvmap,jr,StrToInt(tab_f[3]),acttrie,1);
									Actualiser_Joueur(jr,StrToInt(tab_f[3]));
									Actualiser_Map(nvmap,jr,StrToInt(tab_f[3]));
									tab_aff=Copier_tab_cord_joueurs(nvmap->shipPosition,nvmap->nbShips);
									printf("\nEtat Joueurs : ");
									Affich_Joueur(nvmap,jr,nvmap->nbShips);
									Dessiner_Map(cd.x,cd.y,Trie_Position(tab_aff,nvmap->nbShips),nvmap->nbShips); // Dessiner Map								
									}	
								Pere_Fils_etat(nvmap,jr,tab_act,StrToInt(tab_f[3]));
								if (pid==0){
									Executer_Les_Actions(nvmap,jr,StrToInt(tab_f[3]),tab_act,0);
									Actualiser_Joueur(jr,StrToInt(tab_f[3]));
									Actualiser_Map(nvmap,jr,StrToInt(tab_f[3]));
										if(i==StrToInt(tab_f[6])){
									///////////// Les Free Des Fils  ////////////////////
										free_navalmap(nvmap);
										close(descripteurtube4[0]);
										close(descripteurtube4[1]);
										free_fichier(tab_f);
										free_joueur(jr);
										free_tabact(tab_act,StrToInt(tab_f[3]));
										free_tabact(acttrie,StrToInt(tab_f[3]));
										free_tabactype(actt,StrToInt(tab_f[3]));
										////////////////////////////////////////////
										exit(4); // Terminaison Des Processus 
											}
									}
							}
							if (pid>0){
							printf("\nResultat Finale : \n");
							Afficher_Gagnant(jr,StrToInt(tab_f[3]));
							for(int i=0;i<StrToInt(tab_f[3]);i++) wait(NULL);
							}
							///////////// Les Free  ////////////////////
							free_navalmap(nvmap);
							close(descripteurtube4[0]);
							close(descripteurtube4[1]);
							free_fichier(tab_f);
							free_joueur(jr);
							free_tabact(tab_act,StrToInt(tab_f[3]));
							free_tabact(acttrie,StrToInt(tab_f[3]));
							free_tabactype(actt,StrToInt(tab_f[3]));
							////////////////////////////////////////////
							}break;
							
							case 2:{ // IA VS IA
								system("clear");
								printf("Debut:");
								coord_t* tab_aff;
								ACTTYPE** actt;
								ACT** acttrie;
								int stat;
								tab_aff=Copier_tab_cord_joueurs(nvmap->shipPosition,nvmap->nbShips);
								Affich_Joueur(nvmap,jr,nvmap->nbShips); // Afficher l'états des joueurs
								Dessiner_Map(cd.x,cd.y,Trie_Position(tab_aff,nvmap->nbShips),nvmap->nbShips); // Dessiner Map
									for(int i=1;i<=StrToInt(tab_f[6]);i++){
									if (i==1)creat_process(StrToInt(tab_f[3])); //Création des processus
									if (pid>0)printf("Tour %d : \n",i);
									PERE_FILS(StrToInt(tab_f[3]));
									FILS_PERE(nvmap,jr,	StrToInt(tab_f[3]),tab_act,2);
									if (pid>0){	
									actt=Actiontype(tab_act,StrToInt(tab_f[3]));
									acttrie=Trie_Les_Actions(actt,StrToInt(tab_f[3]));
									printf("Les Actions : \n");
									Executer_Les_Actions(nvmap,jr,StrToInt(tab_f[3]),acttrie,1);
									Actualiser_Joueur(jr,StrToInt(tab_f[3]));
									Actualiser_Map(nvmap,jr,StrToInt(tab_f[3]));
									tab_aff=Copier_tab_cord_joueurs(nvmap->shipPosition,nvmap->nbShips);
									printf("\nEtat Joueurs : ");
									Affich_Joueur(nvmap,jr,nvmap->nbShips);
									Dessiner_Map(cd.x,cd.y,Trie_Position(tab_aff,nvmap->nbShips),nvmap->nbShips); // Dessiner Map
									
								}	
								Pere_Fils_etat(nvmap,jr,tab_act,StrToInt(tab_f[3]));
								if (pid==0){
									Executer_Les_Actions(nvmap,jr,StrToInt(tab_f[3]),tab_act,0);
									Actualiser_Joueur(jr,StrToInt(tab_f[3]));
									Actualiser_Map(nvmap,jr,StrToInt(tab_f[3]));
									if(i==StrToInt(tab_f[6])){
										///////////// Les Free Des Fils  ////////////////////
										free_navalmap(nvmap);
										close(descripteurtube4[0]);
										close(descripteurtube4[1]);
										free_fichier(tab_f);
										free_joueur(jr);
										free_tabact(tab_act,StrToInt(tab_f[3]));
										free_tabact(acttrie,StrToInt(tab_f[3]));
										free_tabactype(actt,StrToInt(tab_f[3]));
										////////////////////////////////////////////
										exit(5); // Terminaison Des Processus 
										}
									}
							}
							if (pid>0){
							printf("\nResultat Finale : \n");
							Afficher_Gagnant(jr,StrToInt(tab_f[3]));
							for(int i=0;i<StrToInt(tab_f[3]);i++) wait(NULL);
							}
							///////////// Les Free Du Pére  ////////////////////
							free_navalmap(nvmap);
							close(descripteurtube4[0]);
							close(descripteurtube4[1]);
							free_fichier(tab_f);
							free_joueur(jr);
							free_tabact(tab_act,StrToInt(tab_f[3]));
							free_tabact(acttrie,StrToInt(tab_f[3]));
							free_tabactype(actt,StrToInt(tab_f[3]));
							////////////////////////////////////////////
							}break;
							
							case 3 : goto etiq_1;break;	
						}
			}break;
			
	case 2 :{ //MultiPlayer
		
		
	}break;
	
	case 3 :Affichage_Quitter(); break; //Quitter
	}

}
