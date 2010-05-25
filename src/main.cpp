#include "gui.h"
#include "types.h"
#include "playground.h"
#include <stdint.h>
#include <iostream>
#include <GL/glut.h>

Playground* currentPlayground = NULL;

/*
 * Führt einen Spielzug aus. Diese Methode wird entweder aufgerufen,
 * wenn der menschliche Spieler eine Kugel legt oder die KI für den Computer-
 * spieler einen neuen Spielzug berechnet hat.
 * color: Farbe des Spielers
 * x, y, z: Position der neuen Kugel
 * playground: aktueller Spielstatus
 */
int move(int color, int x, int y, int z, Playground* playground)
{
	return 0;
}

int main(int argc, char* argv[])
{
 	/* Startet die grafische Oberfläche */
	init_gamewindow(&argc, argv);
 
	/* Leeren Playground erzeugen */
	currentPlayground = new Playground();

	glutMainLoop();

 	delete currentPlayground;
	return 0;
}
