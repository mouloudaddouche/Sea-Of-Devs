#include "lire_fichier.h"

SE_FICHIER SE_ouverture (const char * chemin,int acces){ //Fonction qui permet d'ouvrir un fichier
	SE_FICHIER f;
	f.descripteur=open(chemin,acces);
	if(f.descripteur == -1){
		perror("ERROR OUVERTURE FICHIER\n");}
	else{
		f.chemin=malloc(strlen(chemin)*sizeof(char));
		strcpy(f.chemin,chemin);
		f.acces=acces;
			
		}
	return f;
}

int SE_Fermeture(SE_FICHIER f){ //Fonction qui permet de fermer un fichier
	return close(f.descripteur);
	
}

int nombre_donne_fichier(const char* chemin){
	int nb=0;
	SE_FICHIER f;
	f=SE_ouverture(chemin,O_RDONLY);
	char * buf=malloc(50*sizeof(char));
	while(read(f.descripteur, buf, 1)){
		if (buf[0] == ';' || buf[0] == '\n') nb++;
	}
	return nb;
}

char** SE_LireFichier(const char* chemin){ //Fonction qui permet de lire un fichier et sauvgarder ses données dans un tableau de string
	SE_FICHIER f;
	f=SE_ouverture(chemin,O_RDONLY);
	char * buf=malloc(50*sizeof(char));
	char** tab=malloc(7*sizeof(char*));
	for (int i=0;i<7;i++){
		tab[i]=malloc(50*sizeof(char));}
	char* str;
	int c=0;
	int i=0;
	int j=0;
	
	while(read(f.descripteur, buf, 1)){
		
		if (buf[0] == ';'){
		strcpy(tab[j],str);
			j++;
			c=0;
			i=0;
		}
		else if (buf[0] == '\n'){
			strcpy(tab[j],str);
			j++;
			c=0;
			i=0;
			
		}
		else{
		if((buf[0] !=';') && (buf[0] !='\n')){
		{if (c==0) {str=malloc(50*sizeof(char));c=1; }
		str[i]=buf[0];
		i++;}
		}
	}
		
	}
	SE_Fermeture(f);
	return tab;
} 

void free_fichier(char** f){
	for (int i=0;i<7;i++){
		free(f[i]);}
	free(f);
	
}


