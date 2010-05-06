#ifndef _PLAYGROUND_H_
#define _PLAYGROUND_H_

#include "types.h"

class Playground
{
	private:
		playground_t playground;

	public:
		// Prüft auf Siegbedingung. Gibt 0 zurück, falls kein Spieler gewonnen
		// hat oder 1 für BLACK oder 2 für WHITE.
		int isGameOver();
};

#endif
