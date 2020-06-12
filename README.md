# Sea of devs
Conception d'une application multi-thread console qui permet de jouer au jeu d’une bataille navale.

## À propos du projet :

L’application permettra a un nombre donné de joueurs ( chaque joueur est un thread ), chacun représenté par 
un navire et ils doivent parcourir un océan à la recherche des autres pour être le dernier survivant. La vie du navire
est symbolisée par une valeur C appelée coque, et son endurance par une valeur K appelée kerosene.
Le jeu fonctionne en tour par tour, durant un tour : 
- chaque joueur déterminela prochaine action à effectuer puis en informe le serveur.
- ce dernier effectue les actions en fonction de différents critères (priorité par exemple).
- puis il informe les joueurs de leur nouvel état (nouvelles coordonnées, perte de points de coque ou de kerosene,etc...). 
Le jeu se termine lorsqu’il ne reste plus qu’un seul survivant, ou si un nombre de tours prédéfini a été atteint.


## Langage utilisé :

- [C](https://fr.wikipedia.org/wiki/C_(langage)) - Langage de programmation de l'application.


## Utilisation
il suffit de se positionner dans le dossier Project et de lancer la commande : ./SoD fichier.
fichier est le nom du fichier passé en entré qui est constitué de deux lignes :
1. la caractérisation de la carte, avec son type, sa taille en longueur et en hauteur.
2. la caractérisation de la partie, avec le nombre de joueurs, les valeurs initiales de coque et de kerosene et le nombre
   de tours maximum joués.
