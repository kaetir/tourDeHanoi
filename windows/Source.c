#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "ConsoleTools.h"
#include "tour.h"


int main(int argc, char *argv[])
{
	time_t debut, fin;
	OpenConsole();

	/*le nombre de disk*/
	int nbDisk = 0;
	char mode;

	printf("saisir le nombre de disques : ");
	scanf_s("%d", &nbDisk);
	while (_kbhit()) _getch();
	printf("saisir le mode (a : auto / m : manuel) : ");
	mode = (char)_getch();


	/* REDIMENTIONNEMENT DE LA CONSOLE */
	{
		char commande[100];
		sprintf_s(commande, 100, "mode con cols=%d lines=%d", (nbDisk * 2 + 2) * 3 + 3, nbDisk + 5);
		system(commande);
	}

	/* INITIALISATION */
	TOUR tour1 = initTour(nbDisk + 1), tour2 = initTour(nbDisk + 1), tour3 = initTour(nbDisk + 1);
	for (size_t i = nbDisk; i > 0; i--)
		addDisk(&tour1, i);

	afficher(&tour1, &tour2, &tour3, nbDisk + 1);
	debut = time(NULL);
	if (mode == 'm')
		playerInteract(&tour1, &tour2, &tour3);
	else {
		setCursorVisibility(0);
		autointeract(&tour1, &tour2, &tour3, nbDisk, &tour1, &tour2, &tour3);
	}
	fin = time(NULL);
	GotoXY(0, nbDisk + 4);
	printf("temps de resolution :%ld secondes",fin - debut );
	_getch();

	CloseConsole();
}

