#include "joueur.h"

joueur* Init_Joueur(int n,char* s1,char* s2){
	joueur* jr=malloc(n*sizeof(joueur));
	for(int i=0;i<n;i++){
		jr[i].id=i;
		jr[i].C=StrToInt(s1);
		jr[i].K=StrToInt(s2);
		jr[i].BE=0;
		jr[i].rdr=NULL;
	}
	return jr;
}

void Affich_Joueur(navalmap_t* nmap, joueur* jr,int n){
	printf("\n");
	for(int i=0;i<n;i++){
		if (jr[i].BE ==0)
		printf("Joueur %d : Position (%d,%d) Coque %d  Kerosene %d\n",jr[i].id+1,nmap->shipPosition[i].x,nmap->shipPosition[i].y,jr[i].C,jr[i].K);
		else printf("Joueur %d : Navire Ecoule\n",jr[i].id+1);
		
	}
	
}

coord_t* Copier_tab_cord_joueurs(coord_t* tab_orig,int nbjr){
	coord_t* tab_cop=malloc(nbjr*sizeof(coord_t));
	for(int i=0;i<nbjr;i++){
		tab_cop[i].x=tab_orig[i].x;
		tab_cop[i].y=tab_orig[i].y;
	}
	
	return tab_cop;
	
}

void Afficher_Radar(navalmap_t* bmap,joueur* jr,int id){
	printf(" J%d id ennemi = %d ",id,jr[id].rdr->id_ship_ennemi);
	printf(" position ennemi = %d %d ",jr[id].rdr->pos.x,jr[id].rdr->pos.y);
	printf(" C = %d",jr[id].rdr->C);
	printf(" K = %d \n",jr[id].rdr->K);
}

int Coque_Max (joueur* jr, int nbjr){
	int cq=0;
	for(int i=0;i<nbjr;i++){
		if (jr[i].C > cq) cq=jr[i].C;
	}
	return cq;
}

int nb_des_gagnant(joueur* jr,int nbjr){
	int coquemax=Coque_Max(jr,nbjr);
	int nb=0;
	for(int i=0;i<nbjr;i++){
		if (jr[i].C ==coquemax) nb++;
	}
	
	return nb;
	
}

int Kerosene_Max(joueur* jr, int nbjr){
	int coqmax=Coque_Max(jr,nbjr);
	int kr=0;
	for(int i=0;i<nbjr;i++){
		if(jr[i].C ==coqmax){
		if (jr[i].K > kr) kr=jr[i].K;
	}
	
}
return kr;
}

void Afficher_Gagnant(joueur* jr,int nbjr){
	int nb=nb_des_gagnant(jr,nbjr);
	if (nb==1){ 
		printf("Le Gagant est : ");
		for(int i=0;i<nbjr;i++){
		if (jr[i].C ==Coque_Max(jr,nbjr)) printf("Joueur %d \n",i+1);
		}
	}
	
	else{ 
		int nbk=0;
		for(int i=0;i<nbjr;i++){
		if (jr[i].C==Coque_Max(jr,nbjr) && jr[i].K == Kerosene_Max(jr,nbjr)){ 
		nbk++;}
		}
		if(nbk==1){
		printf("Le Gagant est : ");
		for(int i=0;i<nbjr;i++){
		if (jr[i].C ==Coque_Max(jr,nbjr) && jr[i].K == Kerosene_Max(jr,nbjr))  printf("Joueur %d \n",i+1);
		}
		
	}	
	else{	
		printf("Les Gagnants Sont : ");
		int bol=0;
		for(int i=0;i<nbjr;i++){
		if (jr[i].C ==Coque_Max(jr,nbjr) && jr[i].K == Kerosene_Max(jr,nbjr)) {
			if (bol==0){
			printf("Joueur %d",i+1);
			bol=1;	
			}
			else{
				printf(" + Joueur %d",i+1);
			}
			
			} 
		
		
	}
	printf("\n");
}
}
}

void Actualiser_Joueur(joueur* jr,int nbjr){
	for(int i=0;i<nbjr;i++){
		if(jr[i].K <=0 || jr[i].C<=0)
			 jr[i].BE=1;
	}
}

void Actualiser_Map(navalmap_t* nmap,joueur*jr,int nbjr){
	for(int i=0;i<nbjr;i++){
		if (jr[i].BE ==1){
			//nmap->map[nmap->shipPosition[jr[i].id].x][nmap->shipPosition[jr[i].id].y].type==ENT_SEA;
			nmap->shipPosition[i].x=100;
			nmap->shipPosition[i].y=100;
			
		}
	}
}

void free_joueur(joueur* jr){
	
	free(jr);
}
