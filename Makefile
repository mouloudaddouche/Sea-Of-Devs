all: SoD
	./SoD fichier
	
SoD: SoD.o processus.o nm_rect.o navalmap.o lire_fichier.o conver.o  afficher.o joueur.o action.o
	gcc -o SoD SoD.o nm_rect.o navalmap.o lire_fichier.o conver.o afficher.o joueur.o  processus.o action.o -L./lib -lnm
	
SoD.o : SoD.c nm_rect.h navalmap.h lire_fichier.h conver.h  processus.h afficher.h
	gcc -c SoD.c
nm_rect.o : nm_rect.c nm_rect.h navalmap.h 
	gcc -c nm_rect.c
navalmap.o : navalmap.c nm_rect.h navalmap.h 
	gcc -c navalmap.c
lire_fichier.o : lire_fichier.c  nm_rect.h navalmap.h lire_fichier.h conver.h  processus.h afficher.h
	gcc -c lire_fichier.c
conver.o : conver.c conver.h 
	gcc -c conver.c
joueur.o : joueur.c joueur.h
	gcc -c joueur.c
processus.o : processus.c processus.h SoD.h
	gcc -c processus.c
action.o : action.c action.h navalmap.h joueur.h SoD.h
	gcc -c action.c
afficher.o : afficher.c afficher.h navalmap.h SoD.h
	gcc -c afficher.c


# Le clean	
clean :
	rm -f *.o
	rm -f SoD
	@rm -f *.gch

# Pour faire un zip
LENOM=Addouche_Brahimi
zip:
	rm -rf ${LENOM}
	rm -rf ${LENOM}.zip
	mkdir ${LENOM}
	cp Makefile ${LENOM}
	cp *.h *.c ${LENOM}
	cp README.txt ${LENOM}
	cp enonce-projet.pdf ${LENOM}
	cp fichier ${LENOM}
	cp -R lib ${LENOM}
	zip -r ${LENOM}.zip ${LENOM}
	rm -rf ${LENOM}



