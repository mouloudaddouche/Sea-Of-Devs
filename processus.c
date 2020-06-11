#include "processus.h"
#include <ctype.h>



//Fonction qui permet de creer les n processus
void creat_process(int n){
	tab=malloc(n*sizeof(elt));
  for(int i = 0; i < n; i++){
  pipe(tab[i].descripteurtube);
  tab[i].id=i;
  tab[i].pid=fork();
  pid=tab[i].pid;
  if (pid > 0) {
	 /* Processus père on continue la boucle	 */}
	  else if (pid == 0) {
		  tab[i].pid=getpid();
   break; 
	/* Processus fils on sort de la boucle pour que seul le père crée des fork()	 */
	}	
  }	
}


void FILS_PERE(navalmap_t* nmap,joueur*jr,int n,ACT** tab_act,int mode){
char messageEcriretemp[TAILLE_MESSAGE];
char messageLiretemp[TAILLE_MESSAGE];
if(pid>0){ //Pére
	//wait_procc(4);
	close(descripteurtube4[1]);
        for(int i=0;i<n;i++){
        read(descripteurtube4[0], messageLiretemp,TAILLE_MESSAGE);
        if(isalpha(messageLiretemp[1]))
		tab_act[messageLiretemp[0]-'0']=Chaine_To_Act(messageLiretemp);
		else{
			int indice=(messageLiretemp[0]-'0')*10 + messageLiretemp[1]-'0';
			tab_act[indice]=Chaine_To_Act(messageLiretemp);
		}
       }
        
	}	
if (pid ==0){
	if(mode==1){
		if (getpid() == tab[0].pid){
			Actualiser_Joueur(jr,n); //Joueur
			if(jr[0].BE==0){
		close(descripteurtube4[0]);
		char * s=malloc(15*sizeof(char));
		s[0]='0';
		char* s1=malloc(15*sizeof(char));
		scanf("%s",s1);;
		strcat(s,s1);
		write(descripteurtube4[1],s, TAILLE_MESSAGE);
		
	}
	else {
	  sprintf(messageEcrire,jouer(nmap,jr,StrToInt(messageLire),n));
	  write(descripteurtube4[1], messageEcrire, TAILLE_MESSAGE);
		
	}
	}
	else{ //IA
	close(descripteurtube4[0]);
	sprintf(messageEcrire,jouer(nmap,jr,StrToInt(messageLire),n));
	  write(descripteurtube4[1], messageEcrire, TAILLE_MESSAGE);
  }	
	}
	else if(mode ==2){ // les Fils
	close(descripteurtube4[0]);
	sprintf(messageEcrire,jouer(nmap,jr,StrToInt(messageLire),n));
	  write(descripteurtube4[1], messageEcrire, TAILLE_MESSAGE);
	}
}
}
void PERE_FILS(int n){
    
	if(pid ==0){ //FILS
		for(int i=0;i<n;i++){
			if(getpid() ==tab[i].pid){
				close(tab[i].descripteurtube[1]);
				 read(tab[i].descripteurtube[0], messageLire, TAILLE_MESSAGE);}
			}
		}
	if (pid>0){ //Pere
		for(int i=0;i<n;i++){
			close(tab[i].descripteurtube[0]);
			sprintf(messageEcrire, "%d  ",tab[i].id);
			 write(tab[i].descripteurtube[1], messageEcrire, TAILLE_MESSAGE);
		
	}	
  }
}

void Pere_Fils_etat(navalmap_t* nmap,joueur* jr,ACT** tab_act,int nbjr){
	if (pid>0){
		for (int i=0;i<nbjr;i++){ //nb jr
						close(tab[i].descripteurtube[0]);
			for (int j=0;j<nbjr;j++){ // chaque joueur

			char* s=malloc(15*sizeof(char));
			strcpy(s,Act_To_Chaine(tab_act[j]));
			sprintf(messageEcrire,"%s",Act_To_Chaine(tab_act[j]));
			write(tab[i].descripteurtube[1], messageEcrire, TAILLE_MESSAGE);
			
		}
	}
	}
	if (pid==0){//FILS
		for(int i=0;i<nbjr;i++){
			if(getpid() ==tab[i].pid){
				close(tab[i].descripteurtube[1]);
				for(int j=0;j<nbjr;j++){
				 read(tab[i].descripteurtube[0], messageLire, TAILLE_MESSAGE);
				 char* s=malloc(15*sizeof(char));
				 strcpy(s,messageLire);
				 tab_act[j]=Chaine_To_Act(s);
				//printf( " %d %s \n",getpid(),Act_To_Chaine(tab_act[i]));
			}
		}
		}
		
	}

}

