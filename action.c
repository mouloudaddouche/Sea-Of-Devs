#include "action.h"
#include <ctype.h>


int Est_Adjacent(coord_t b1,coord_t b2){
	if (b1.x == b2.x && b1.y ==b2.y-1) return 1;
	if (b1.x == b2.x && b1.y ==b2.y+1) return 1;
	if (b1.y == b2.y && b1.x ==b2.x+1) return 1;
	if (b1.y == b2.y && b1.x ==b2.x-1) return 1;
	return 0;
	
}

int postion_adverse_inconnu(navalmap_t* nmap,joueur* jr, int idjr){
	if (jr[idjr].rdr !=NULL) return 0;
	else return 1;
}
	

int radar_vieux(navalmap_t* nmap,joueur* jr, int idjr,int nbjr){

		info_radar* rdr=SCN(nmap,jr,idjr,nbjr,0);
		if (rdr->id_ship_ennemi == jr[idjr].rdr->id_ship_ennemi){
		return 0;}
		else return 1;
	
	
}

int possible_attaque(navalmap_t* nmap,joueur* jr, int idjr){
	int dst;
	dst=abs((nmap->shipPosition[jr[idjr].id].x)-(nmap->shipPosition[jr[idjr].rdr->id_ship_ennemi].x)) + abs((nmap->shipPosition[jr[idjr].id].y)-(nmap->shipPosition[jr[idjr].rdr->id_ship_ennemi].y));
	if (dst >= 2 && dst <=4) return 1;
	else return 0;
	
	
}

void MOV(navalmap_t* nmap, coord_t movevect,joueur* jr, int idjr,int nbjr,int pf){
	Actualiser_Joueur(jr,nbjr);
			coord_t casvol;
			casvol.x=nmap->shipPosition[idjr].x+movevect.x;
			casvol.y=nmap->shipPosition[idjr].y+movevect.y;
			if (pf ==1){
				if (movevect.x >0 && movevect.y>0)
				printf("J%d : MOV (+%d,+%d)",idjr+1,movevect.x,movevect.y);
				else if (movevect.x >0 && (movevect.y<0 || movevect.y==0))
				printf("J%d : MOV (+%d,%d)",idjr+1,movevect.x,movevect.y);
				else if (movevect.y >0 && (movevect.x<0 || movevect.x==0))
				printf("J%d : MOV (%d,+%d)",idjr+1,movevect.x,movevect.y);
				else printf("J%d : MOV (%d,%d)",idjr+1,movevect.x,movevect.y);
			}
	if(nmap->isMovePossible(nmap,idjr,movevect)){
		
		int dist=abs(movevect.x)+abs(movevect.y);
		if(dist>= 1 && dist <= 2){
			if (nmap->map[casvol.y][casvol.x].type == ENT_SHIP){
				jr[idjr].C-=5;
				for(int i=0;i<nbjr;i++){
					if (nmap->shipPosition[i].x == casvol.x && nmap->shipPosition[i].y == casvol.y) {
					jr[i].C-=5;
						if (pf ==1) printf(" -> J%d se situe deja dans cette case\n",i+1);
					}
				}
			}
			else{
				if (pf==1) ("ouiiii possible\n");
			moveShip(nmap,idjr,movevect);
			jr[idjr].K-=2;
			if (pf ==1)	printf(" -> Deplacement reussi\n"); }
			
		}
		 else if (pf ==1) printf(" -> Deplacement impossible\n");
   }
   else if (pf ==1) printf(" -> Deplacement impossible\n");

}
void NON(navalmap_t* nmap,joueur* jr,int idjr,int pf){
	if (pf ==1) printf ("J%d : NON\n",idjr+1);
	jr[idjr].K-=1;
	
}

void ATK(navalmap_t* nmap,joueur* jr,coord_t vectatk,int idjr,int nbjr,int pf){
	if(jr[idjr].C>0 && jr[idjr].K>=5){
	int bool=0;
	int adj=0;
	if (pf ==1) printf("J%d : ATK (%d,%d)",idjr+1,vectatk.x,vectatk.y);
		int dist=abs(vectatk.x-nmap->shipPosition[idjr].x)+abs(vectatk.y-nmap->shipPosition[idjr].y);
		if (dist >= 2 && dist <=4){
			for(int i=0;i<nbjr;i++){
			if (i!=idjr){
			if (jr[i].BE==0){
			if (Est_Adjacent(nmap->shipPosition[i],vectatk)){
				if (pf==1) {if (adj==0) printf (" -> ");
				else  printf (" + ");}
				if (pf ==1) printf ("J%d subit 20C",i+1);
				adj=1;
				//bool=1;
				 jr[i].C-=20;}
			else if (nmap->shipPosition[i].x == vectatk.x && nmap->shipPosition[i].y == vectatk.y){
				if (pf==1){if (adj==0) printf (" -> ");
					else if (bool==0) printf (" + ");}
				
				if (pf ==1) printf ("J%d subit 40C",i+1);
				//adj=1;
				bool=1;
				adj=1;
				 jr[i].C-=40;}
			 }
			}
			}
		if (bool ==0) {if (pf ==1) printf(" -> Aucune cible touchee");}
	}
	else{ if (pf ==1) printf(" -> Impossible d'attaquer");}
	if (pf==1)printf("\n");
	jr[idjr].K-=5;
  }
}
void BBS(navalmap_t* nmap,joueur* jr,coord_t casebmb,int idjr,int nbjr,int pf){
	int dist=abs(nmap->shipPosition[idjr].x-casebmb.x)+abs(nmap->shipPosition[idjr].y-casebmb.y);
	if (dist >= 1 && dist <=5){
		for(int i=0;i<nbjr;i++){
			if (i!=idjr){
				if (nmap->shipPosition[i].x == casebmb.x && nmap->shipPosition[i].y == casebmb.y) jr[i].C-=30;}
			}
		}
		jr[idjr].K-=3;

}

void BST(navalmap_t* nmap,joueur* jr,coord_t casevis,int idjr,int nbjr,int pf){
	if (pf ==1) printf("J%d : BST ->",idjr+1);
	if (nmap->shipPosition[idjr].x == casevis.x || nmap->shipPosition[idjr].y == casevis.y){
	 int dist=abs(nmap->shipPosition[idjr].x-casevis.x)+abs(nmap->shipPosition[idjr].y-casevis.y);
	  if (dist >= 4 && dist <=5){
	   for(int i=0;i<nbjr;i++){
			if (i!=idjr){
				if (nmap->shipPosition[i].x == casevis.x && nmap->shipPosition[i].y == casevis.y){
					 if (pf ==1) printf(" J%d subit 50C\n",i+1);
					if (nmap->shipPosition[i].x ==nmap->shipPosition[idjr].x){
						
						if (nmap->shipPosition[i].y > nmap->shipPosition[idjr].y) nmap->shipPosition[i].y +=1;
						if (nmap->shipPosition[i].y < nmap->shipPosition[idjr].y) nmap->shipPosition[i].y +=-1;
						
					} 
					
					if (nmap->shipPosition[i].y ==nmap->shipPosition[idjr].y){
						if (nmap->shipPosition[i].x > nmap->shipPosition[idjr].x) nmap->shipPosition[i].x +=1;
						if (nmap->shipPosition[i].x < nmap->shipPosition[idjr].x) nmap->shipPosition[i].x +=-1;
					}
					
					 jr[i].C-=50;
					 jr[idjr].C-=5;}
				
			}
		  }
		  
				nmap->shipPosition[idjr].x=casevis.x ; nmap->shipPosition[idjr].y=casevis.y;
				
		}
		jr[idjr].K-=3;
	 }

}


void RPR(joueur* jr,int idjr,int Cmax,int pf){
	if (jr[idjr].C>0 && jr[idjr].K>=20){
		if (pf ==1) printf("J%d : RPR -> +25C\n",idjr+1);
		jr[idjr].K-=20;
		if (Cmax- jr[idjr].C <= 25) jr[idjr].C=Cmax;
		else jr[idjr].C+=25;
	
}
}

info_radar* SCN (navalmap_t* nmap,joueur* jr,int idjr,int nbjr,int pf){
	Actualiser_Joueur(jr,nbjr);
	int dist;
	int tabdist[nbjr];
	int i=0;
	if (pf ==1) printf("J%d : SCN",idjr+1);
	while(i<nbjr){
		if (i==idjr){ tabdist[i]=1000;i++;}
		else {dist=abs(nmap->shipPosition[idjr].x-nmap->shipPosition[i].x)+abs(nmap->shipPosition[idjr].y-nmap->shipPosition[i].y);
		tabdist[i]=dist;
		i++;}
	}
			if(pf==1)printf("\n");
		
		int imin;
		if (idjr !=0) imin=0;
		else imin=1;
		for(int i=0;i<nbjr;i++){
			if(i==idjr) continue;
			else if(tabdist[i]<tabdist[imin]){ imin=i;}
			}
			info_radar* inf=malloc(sizeof(info_radar));
			inf->id_ship_ennemi=imin;
			inf->pos.x=nmap->shipPosition[imin].x;
			inf->pos.y=nmap->shipPosition[imin].y;
			inf->C=jr[imin].C;
			inf->K=jr[imin].K;
			jr[idjr].K-=3;
			
		return inf;	
	}
	


ACT* Chaine_To_Act(char* s){
	int bol=0;
	ACT* act=malloc(sizeof(ACT));
	act->id=s[0]-'0';
	if (isalpha(s[1])){
	act->nom=malloc(4*sizeof(char));
	for (int i=0;i<3;i++){
		act->nom[i]=s[i+1];
	}
	act->nom[3]='\0';
	
	if ((!strcmp(act->nom,"SCN")) || (!strcmp(act->nom,"RPR")) || (!strcmp(act->nom,"NON"))){
		 act->vect.x=0;
		 act->vect.y=0;}
	else{
		if (s[4]=='-'){
		 act->vect.x=s[5]-'0';
		 act->vect.x= act->vect.x*(-1);
		 bol=1;}
		else {
		act->vect.x=s[4]-'0';}
		if (bol==1){
		 if (s[6]=='-'){
		act->vect.y=s[7]-'0';
		 act->vect.y= act->vect.y*(-1);}
		 else
		 act->vect.y=s[6]-'0';
		}
		else{
		 if (s[5]=='-'){
		act->vect.y=s[6]-'0';
		 act->vect.y= act->vect.y*(-1);}
		 else
		 act->vect.y=s[5]-'0';
			
			
		}
	
		 
	}
	return act;}
	else{
		char* sc=malloc(3*sizeof(char));
		for(int i=0;i<2;i++){
			sc[i]=s[i];
		}
		sc[2]='\0';
		act->id=atoi(sc);
		act->nom=malloc(4*sizeof(char));
	for (int i=0;i<3;i++){
		act->nom[i]=s[i+2];
	}
	act->nom[3]='\0';
	
	if ((!strcmp(act->nom,"SCN")) || (!strcmp(act->nom,"RPR")) || (!strcmp(act->nom,"NON"))){
		 act->vect.x=0;
		 act->vect.y=0;}
	else{
		if (s[5]=='-'){
		 act->vect.x=s[6]-'0';
		 act->vect.x= act->vect.x*(-1);
		 bol=1;}
		else {
		act->vect.x=s[5]-'0';}
		if (bol==1){
		 if (s[7]=='-'){
		act->vect.y=s[8]-'0';
		 act->vect.y= act->vect.y*(-1);}
		 else
		 act->vect.y=s[7]-'0';
		}
		else{
		 if (s[6]=='-'){
		act->vect.y=s[7]-'0';
		 act->vect.y= act->vect.y*(-1);}
		 else
		 act->vect.y=s[6]-'0';
		} 
	}
	return act;
	}
		
		
	}
	

char* Act_To_Chaine(ACT* act){
	int bol=0;
	char* s=malloc(15*sizeof(char));
	s[0]=act->id+'0';
	strcat(s,act->nom);
	if ((!strcmp(act->nom,"SCN")) || (!strcmp(act->nom,"RPR")) || (!strcmp(act->nom,"NON"))){}
	else{
		if (act->vect.x<0){
		s[4]='-';
		s[5]=abs(act->vect.x)+'0';
		bol=1;}
		else s[4]=act->vect.x+'0';
		if (bol==1){
		if (act->vect.y<0){
		s[6]='-';
		s[7]=abs(act->vect.y)+'0';
		}
		else s[6]=act->vect.y+'0';
		}
		else{
		if (act->vect.y<0){
		s[5]='-';
		s[6]=abs(act->vect.y)+'0';
		}
		else s[5]=act->vect.y+'0';
			
		}
		}
	return s;
}

void Executer_Les_Actions(navalmap_t* nmap,joueur* jr,int nbjr,ACT** tab_act,int pid){
	for(int i=0;i<nbjr;i++){
		Actualiser_Joueur(jr,nbjr);
		if(jr[tab_act[i]->id].BE==0){
		if (!strcmp(tab_act[i]->nom,"SCN")){
			if (pid >0)jr[i].rdr=SCN(nmap,jr,tab_act[i]->id,nbjr,1);
			else jr[i].rdr=SCN(nmap,jr,tab_act[i]->id,nbjr,0);
			}
		if (!strcmp(tab_act[i]->nom,"ATK")){
			coord_t vectatk;
			vectatk.x=tab_act[i]->vect.x;
			vectatk.y=tab_act[i]->vect.y;
			if (pid >0) ATK(nmap,jr,vectatk,tab_act[i]->id,nbjr,1);
			else ATK(nmap,jr,vectatk,tab_act[i]->id,nbjr,0);
		}
		if (!strcmp(tab_act[i]->nom,"MOV")){
			coord_t vectmov;
			vectmov.x=tab_act[i]->vect.x;
			vectmov.y=tab_act[i]->vect.y;
			if (pid >0) MOV(nmap,vectmov,jr,tab_act[i]->id,nbjr,1);
			else  MOV(nmap,vectmov,jr,tab_act[i]->id,nbjr,0);
	}
}
}
}	
	
char* jouer(navalmap_t* nmap,joueur* jr,int idjr,int nbjr){
		char* messageEcrire=malloc(15*sizeof(char));
	if (((jr[idjr].rdr == NULL)) || (radar_vieux(nmap,jr,idjr,nbjr)))  { sprintf(messageEcrire,"%dSCN\n",idjr);}
	else if (possible_attaque(nmap,jr,idjr)) sprintf(messageEcrire,"%dATK%d%d\n",idjr,nmap->shipPosition[jr[idjr].rdr->id_ship_ennemi].x,nmap->shipPosition[jr[idjr].rdr->id_ship_ennemi].y);
	else {coord_t movvect;
		movvect.x=jr[idjr].rdr->pos.x-nmap->shipPosition[jr[idjr].id].x;
		movvect.y=jr[idjr].rdr->pos.y-nmap->shipPosition[jr[idjr].id].y;
		sprintf(messageEcrire,"%dMOV%d%d\n",idjr,movvect.x,movvect.y);}
		return messageEcrire;

}

void Afficher_ACT(ACT* act){
	printf(" id = %d    ",act->id);
	printf(" %s   ",act->nom);
	printf(" %d  %d  \n",act->vect.x,act->vect.y);
	
	
}

ACTTYPE** Actiontype(ACT** tabact,int nbjr){
	ACTTYPE** tabf=malloc(nbjr*sizeof(ACTTYPE*));
	for (int i=0;i<nbjr;i++){
		tabf[i]=malloc(nbjr*sizeof(ACTTYPE));
	}
	for (int i=0;i<nbjr;i++){
		tabf[i]->act=Copie_action(tabact[i]);
		if(!strcmp(tabf[i]->act->nom,"ATK") || (!strcmp(tabf[i]->act->nom,"BBS"))) tabf[i]->type='A';
		else if(!strcmp(tabf[i]->act->nom,"BST") || (!strcmp(tabf[i]->act->nom,"MOV")) || (!strcmp(tabf[i]->act->nom,"MIN"))) tabf[i]->type='M';
		else tabf[i]->type='S';
				}
		return tabf;
	}

ACT* Copie_action(ACT* acti){
	ACT* actf=malloc(sizeof(ACT));
	actf->id=acti->id;
	actf->nom=malloc(15*sizeof(char));
	strcpy(actf->nom,acti->nom);
	actf->vect.x=acti->vect.x;
	actf->vect.y=acti->vect.y;
	return actf;
}

ACT** Trie_Les_Actions(ACTTYPE** tabi,int nbjr){
	ACT** tabf=malloc(nbjr*sizeof(ACT*));
	for (int i=0;i<nbjr;i++){
		tabf[i]=malloc(nbjr*sizeof(ACT));
		tabf[i]->nom=malloc(15*sizeof(char));
	}
	int j=0;
	for (int i=0;i<nbjr;i++){
		if(tabi[i]->type=='A'){
			tabf[j]=Copie_action(tabi[i]->act);
			j++;
		}
	}
	
	for (int i=0;i<nbjr;i++){
		if(tabi[i]->type=='M'){
			tabf[j]=Copie_action(tabi[i]->act);
			j++;
		}
	}
	
	for (int i=0;i<nbjr;i++){
		if(tabi[i]->type=='S'){
			tabf[j]=Copie_action(tabi[i]->act);
			j++;
		}
	}
	
return tabf;
}

void free_tabact(ACT** tabact,int n){
	for (int i=0;i<n;i++){
		free(tabact[i]);
		free(tabact);
	}
	
	
}

void free_tabactype(ACTTYPE** tabact,int n){
	for (int i=0;i<n;i++){
		free(tabact[i]);
		free(tabact);
	}
	
	
}
