#include <stdlib.h>
#include <stdio.h>
#include "tour.h"

#include <time.h>

int main(int argc, char *argv[])
{
	time_t debut, fin;

	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	start_color();


    /*le nombre de disk*/
    int nbDisk = 0;
    char mode;

    printw("saisir le nombre de disques : ");
    scanw("%d", &nbDisk);
    printw("saisir le mode (a : auto / m : manuel) : ");
    mode = (char)getch();



    /* INITIALISATION */

    clear();
    /* Initialisation des couleurs */
    init_pair(1, COLOR_RED, COLOR_RED );
    init_pair(2, COLOR_GREEN, COLOR_GREEN );
    init_pair(3, COLOR_BLUE, COLOR_BLUE );
    init_pair(4, COLOR_CYAN, COLOR_CYAN );
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA );
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW );
    init_pair(7, COLOR_WHITE, COLOR_WHITE );
    init_pair(8, COLOR_BLACK, COLOR_BLACK );

    TOUR tour1 = initTour(nbDisk + 1), tour2 = initTour(nbDisk + 1), tour3 = initTour(nbDisk + 1);
    for (size_t i = nbDisk; i > 0; i--) {
        addDisk(&tour1, i);
    }

    afficher(&tour1, &tour2, &tour3, nbDisk + 1);
    if (mode == 'm') {
        debut = time(NULL);
        playerInteract(&tour1, &tour2, &tour3);
        noecho();
    }
	else {
        curs_set(0);
        int speed= 1;
        mvprintw(0,0, "nombre de deplacement par secondes : ");
        scanw("%d", &speed);
        noecho();
        refresh();
        debut = time(NULL);
        autointeract(&tour1, &tour2, &tour3, nbDisk, &tour1, &tour2, &tour3, speed);
    }
    fin = time(NULL);
    move(nbDisk + 4, 0);
    printw("temps de resolution :%ld secondes",fin - debut );

	getch();

	endwin();
}

