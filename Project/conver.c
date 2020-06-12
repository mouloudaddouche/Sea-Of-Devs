#include "conver.h"

int StrToInt(char* str){ //Fonction qui traduit un nombre qui est en string to int
	char *endptr;
	 return((int) strtol(str, &endptr,10));
	  
}
coord_t construire_cord(int x,int y){
	coord_t cd;
	cd.x=x; cd.y=y;
	return cd;
}

