#pragma once

#include <ncurses.h>

typedef struct disque {
	int largeur;
	struct Disk *next;

}Disk;


typedef struct labonnetour{
	int hauteur;
	int	nbDisk;
	int numTour;
	Disk* premier;

}TOUR;

typedef struct coord{
    int X, Y;
}COORD;


TOUR initTour(int);

void addDisk(TOUR *, int);

void afficher(TOUR *, TOUR *, TOUR *, int);

int moveTower(TOUR * tower1, TOUR * tower2);

void playerInteract(TOUR * tower1, TOUR * tower2, TOUR * tower3);

void autointeract(TOUR * tower1, TOUR * tower2, TOUR * tower3, int nbDisk, TOUR * Dtower1, TOUR * Dtower2, TOUR * Dtower3, int speed);

//change la visibilit� du curseur
void setCursorVisibility(int statut);

