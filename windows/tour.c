#include "tour.h"
#include <stdlib.h>
#include <stdio.h>
#include "ConsoleTools.h"

int nbTour = 1;

TOUR initTour(int hauteur)
{
	TOUR tower;
	tower.hauteur = hauteur;
	tower.nbDisk = 0;
	tower.premier = NULL;
	tower.numTour = nbTour;
	nbTour++;
	return tower;
}

void addDisk(TOUR* tower, int largeur)
{
	Disk *disque = malloc(sizeof(Disk));
	disque->largeur = largeur;

	if (tower->premier != NULL) {
		if (largeur >= tower->premier->largeur) {
			return;
		}
		disque->next = tower->premier;
	}
	else {
		disque->next = NULL;
	}
	tower->premier = disque;
	tower->nbDisk++;
}

void afficher(TOUR * tower1, TOUR * tower2, TOUR * tower3, int hauteur)
{
	system("cls");
	/* AFFICHAGE DES BARRES DE LA STRUCTURE */
	{
		for (size_t i = 1; i <= hauteur + 1; i++)
		{
			GotoXY(hauteur, i);
			PlotChar('|');
		}
		for (size_t i = 1; i <= hauteur + 1; i++)
		{
			GotoXY(hauteur * 3 + 1, i);
			PlotChar('|');
		}
		for (size_t i = 1; i <= hauteur + 1; i++)
		{
			GotoXY(hauteur * 5 + 2, i);
			PlotChar('|');
		}
		GotoXY(0, hauteur + 1);
		for (size_t i = 0; i < (hauteur * 2 + 1) * 3; i++)
		{
			printf("_");
		}
	}


	/* AFFICHAGE DES DISQUES*/
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	Disk *tmp = tower1->premier;
	for (size_t i = tower1->nbDisk; i > 0; i--)
	{
		if (tmp == NULL) break;
		GotoXY(hauteur - tmp->largeur, hauteur - i + 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), tmp->largeur * 16);
		for (size_t k = 0; k < tmp->largeur * 2 + 1; k++)
			PlotChar(' ');

		tmp = tmp->next;
	}
	tmp = tower2->premier;
	for (size_t i = tower2->nbDisk; i > 0; i--)
	{
		if (tmp == NULL) break;
		GotoXY(hauteur * 3 + 1 - tmp->largeur, hauteur - i + 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), tmp->largeur * 16);
		for (size_t k = 0; k < tmp->largeur * 2 + 1; k++)
			PlotChar(' ');

		tmp = tmp->next;
	}
	tmp = tower3->premier;
	for (size_t i = tower3->nbDisk; i > 0; i--)
	{
		if (tmp == NULL) break;
		GotoXY(hauteur * 5 + 2 - tmp->largeur, hauteur - i + 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), tmp->largeur * 16);
		for (size_t k = 0; k < tmp->largeur * 2 + 1; k++)
			PlotChar(' ');

		tmp = tmp->next;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

}

//retourne 0 si ok, -1 si erreur, 1 si disque du dessous plus petit
int move(TOUR * tower1, TOUR * tower2)
{
	if (tower1 == NULL || tower2 == NULL)
		return -1;
	if (tower1->nbDisk <= 0)
		return -1;
	if (!(tower1->premier == NULL || tower2->premier == NULL))
		if ((tower1->premier->largeur >= tower2->premier->largeur) && (tower1->nbDisk > 0 && tower2->nbDisk > 0))
			return 1;



	/*affichage a gerer ici*/
	//suppression de l'ancien disque
	if (tower1->numTour == 1) 
		GotoXY(tower1->hauteur - tower1->premier->largeur, tower1->hauteur - tower1->nbDisk + 1);
	if (tower1->numTour == 2) 
		GotoXY(tower1->hauteur * 3 + 1 - tower1->premier->largeur, tower1->hauteur - tower1->nbDisk + 1);
	if (tower1->numTour == 3) 
		GotoXY(tower1->hauteur * 5 + 2 - tower1->premier->largeur, tower1->hauteur - tower1->nbDisk + 1);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (size_t i = 0; i < tower1->premier->largeur; i++)
		PlotChar(' ');
	PlotChar('|');
	for (size_t i = 0; i < tower1->premier->largeur; i++)
		PlotChar(' ');

	// suppression des étoiles
	GotoXY(tower1->hauteur, 1);
	PlotChar('|');
	GotoXY(tower1->hauteur * 3 + 1, 1);
	PlotChar('|');
	GotoXY(tower1->hauteur * 5 + 2, 1);
	PlotChar('|');

	//ajout du nouveau 
	if (tower2->numTour == 1) 
		GotoXY(tower1->hauteur - tower1->premier->largeur, tower1->hauteur - tower2->nbDisk);

	if (tower2->numTour == 2) 
		GotoXY(tower1->hauteur * 3 + 1 - tower1->premier->largeur, tower1->hauteur - tower2->nbDisk);
	
	if (tower2->numTour == 3) 
		GotoXY(tower1->hauteur * 5 + 2 - tower1->premier->largeur, tower1->hauteur - tower2->nbDisk);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), tower1->premier->largeur * 16);
	for (size_t k = 0; k < tower1->premier->largeur * 2 + 1; k++)
		PlotChar(' ');

	Disk * tmp = tower1->premier;
	tower1->premier = tower1->premier->next;
	tmp->next = tower2->premier;
	tower2->premier = tmp;

	tower1->nbDisk--;
	tower2->nbDisk++;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void playerInteract(TOUR * tower1, TOUR * tower2, TOUR * tower3)
{
	unsigned char saisie, pos = 0;
	int posPossibles[3] = { tower1->hauteur, 3 * tower1->hauteur + 1, 5 * tower1->hauteur + 2 }, tour[2];

	COORD curs;
	curs.X = posPossibles[pos];
	curs.Y = 1;
	do {
		for (size_t i = 0; i < 2; i++)
		{
			do {
				GotoXY(curs.X, curs.Y);

				saisie = _getch();
				if (saisie == 224)
					saisie = _getch();
				switch (saisie)
				{
				case KEY_RIGHT:
				{
					if (curs.X < posPossibles[2]) {
						pos++;
						curs.X = posPossibles[pos];
					}
					break;
				}
				case KEY_LEFT:
				{if (curs.X > posPossibles[0]) {
					pos--;
					curs.X = posPossibles[pos];
				}

				break;
				}

				default:
					break;
				}

			} while (saisie != ENTER);
			PlotChar('*');
			tour[i] = pos;
		}
		switch (tour[0])
		{
		case 0:
			switch (tour[1])
			{
			case 1:
				move(tower1, tower2);
				break;
			case 2:
				move(tower1, tower3);
				break;
			}
			break;
		case 1:
			switch (tour[1])
			{
			case 0:
				move(tower2, tower1);
				break;
			case 2:
				move(tower2, tower3);
				break;
			}
			break;
		case 2:
			switch (tour[1])
			{
			case 0:
				move(tower3, tower1);
				break;
			case 1:
				move(tower3, tower2);
				break;
			}
			break;
		}
		//afficher(tower1, tower2, tower3, tower1->hauteur);
	} while (tower3->nbDisk != tower3->hauteur -1);

}

void setCursorVisibility(int statut) //change la visibilité du curseur
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hConsole, &cci);
	cci.bVisible = statut;
	SetConsoleCursorInfo(hConsole, &cci);
}

void autointeract(TOUR * tower1, TOUR * tower2, TOUR * tower3, int nbDisk, TOUR * Dtower1, TOUR * Dtower2, TOUR * Dtower3)
{
	if (nbDisk != 0) {
		autointeract(tower1, tower3, tower2, nbDisk - 1, Dtower1, Dtower2, Dtower3);
		move(tower1, tower3);
		autointeract(tower2, tower1, tower3, nbDisk - 1, Dtower1, Dtower2, Dtower3);
	}
	//afficher(Dtower1, Dtower2, Dtower3, Dtower1->hauteur);
	Sleep(30);
}


