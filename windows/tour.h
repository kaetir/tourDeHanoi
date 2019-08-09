#pragma once

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13

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



TOUR initTour(int);

void addDisk(TOUR *, int);

void afficher(TOUR *, TOUR *, TOUR *, int);

int move(TOUR * tower1, TOUR * tower2);

void playerInteract(TOUR * tower1, TOUR * tower2, TOUR * tower3);

void autointeract(TOUR * tower1, TOUR * tower2, TOUR * tower3, int nbDisk, TOUR * Dtower1, TOUR * Dtower2, TOUR * Dtower3);

//change la visibilité du curseur
void setCursorVisibility(int statut);

