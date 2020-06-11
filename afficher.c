#include "afficher.h"

char* Dessiner_Bateau(){
	char* array = malloc(18*sizeof(char));
	strcpy(array, u8"\u25c6");
	return array;
	
}

coord_t* Trie_Position(coord_t* const tab,int n){
	coord_t cdmin; int imin;
	for (int i=0;i<n-1;i++){
		cdmin.x=tab[i].x; cdmin.y=tab[i].y;
		imin=i;
		for(int j=i+1;j<n;j++){
			if (tab[j].x<cdmin.x) {
				cdmin.x=tab[j].x;cdmin.y=tab[j].y;imin=j;}
			else if (tab[j].x == cdmin.x){
				if (tab[j].y<cdmin.y) {cdmin.x=tab[j].x;cdmin.y=tab[j].y;imin=j;}
			}
		
	}
	if (tab[i].x != tab[imin].x || tab[i].y != tab[imin].y){
		coord_t temp;
		temp.x=tab[i].x; temp.y=tab[i].y;
		tab[i].x=tab[imin].x; tab[i].y=tab[imin].y;
		tab[imin].x=temp.x;tab[imin].y=temp.y;
		
	}
	
}
return tab;
}

void Dessiner_Map(int x,int y,coord_t* bt,int nb){
	int temp=0;
	for(int k=0;k<x;k++){
		if (k==0) printf("  \e(0\x6c\e(B\e(0\x71\e(B\e(0\x71\e(B\e(0\x71\e(B");
		else printf("  \e(0\x74\e(B\e(0\x71\e(B\e(0\x71\e(B\e(0\x71\e(B");
	for(int j=0;j<y-1;j++){
		if (k==0) printf("\e(0\x77\e(B\e(0\x71\e(B\e(0\x71\e(B\e(0\x71\e(B");
		else printf("\e(0\x6e\e(B\e(0\x71\e(B\e(0\x71\e(B\e(0\x71\e(B");
	}
	if (k==0) printf("\e(0\x6b\e(B\n");
	else printf("\e(0\x75\e(B\n");
	printf("  \e(0\x78\e(B");
	for(int j=0;j<y;j++){
		if (k!=bt[temp].x) printf("   \e(0\x78\e(B");
		else{ if (j==bt[temp].y){
			 printf(" %s \e(0\x78\e(B",Dessiner_Bateau());
			 temp++;}
			else printf("   \e(0\x78\e(B"); }
}
printf("\n");
}
//Derniere ligne
for (int i=0;i<y;i++){
	if(i==0) printf("  \e(B\e(0\x6d\e(B\e(B\e(0\x71\e(B\e(B\e(0\x71\e(B\e(B\e(0\x71\e(B");
else printf("\e(B\e(0\x76\e(B\e(B\e(0\x71\e(B\e(B\e(0\x71\e(B\e(B\e(0\x71\e(B");
 }
 printf("\e(B\e(0\x6a\e(B\n");
}

void Affichage_Menu_Principale(){
	system("clear");
	printf("\n		 Sea        Of        Devs\n\n");
	printf(" 1- Single Player \n");
	printf(" 2- Multi Player \n");
	printf(" 3- Quitter \n");
	
}

int Choix_Menu_Principale(){
	int temp=0;
	int i=0;
	do { 
		if(i !=0 ) printf(" Veuillez choisir un choix disponible\n");
		scanf("%d",&temp);
		i++;
	}while((temp<=0) || (temp >3));
	return(temp);
}

void Affichage_Menu_Secondaire(){
	system("clear");
	printf("\n		 Sea        Of        Devs\n\n");
	printf(" 1- JR Vs IA\n");
	printf(" 2- IA Vs IA\n");
	printf(" 3- Return \n");
}

int Choix_Menu_Secondaire(){
	int temp=0;
	int i=0;
	do { 
		if(i !=0 ) printf(" Veuillez choisir un choix disponible\n");
		scanf("%d",&temp);
		i++;
	}while((temp<=0) || (temp >3));
	return(temp);
}

void Affichage_Quitter(){
	system("clear");
	printf("\n		 Sea        Of        Devs\n\n");
	printf("     			 Au Revoir     \n\n");
	
}
	
	
	
