#ifndef _PLAYGROUND_H_
#define _PLAYGROUND_H_

#include "types.h"
#include <stdint.h>

class Playground
{
	public: // Fürs Debuggen
		playground_t playground;

	public:
		Playground();

		// Prüft auf Siegbedingung. Gibt 0 zurück, falls kein Spieler gewonnen
		// hat oder 1 für BLACK oder 2 für WHITE.
		int isGameOver();

		int get (uint8_t x, uint8_t y, uint8_t z);
		void set (uint8_t x, uint8_t y, uint8_t z, uint8_t);
};

#endif
