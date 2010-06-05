#ifndef _PLAYGROUND_H_
#define _PLAYGROUND_H_

#include "types.h"
#include <stdint.h>

#define MAX_RATING 1000		/* Maximale Bewertungszahl (+|-) */

class Playground
{
	private:
		int8_t winnerCache;
	
	public:
		uint8_t cols[4][4]; // 4x4 Säulen
		//playground_t playground;
		int turnColor; // WHITE begins

	public:
		Playground();

		Playground* clone();

		// Prüft auf Siegbedingung. Gibt 0 zurück, falls kein Spieler gewonnen
		// hat oder 1 für BLACK oder 2 für WHITE.
		int isGameOver();

		int get (uint8_t x, uint8_t y, uint8_t z);
		void set (uint8_t x, uint8_t y, uint8_t z, uint8_t);

		// Setze Kugel an die angegebene Position und gibt true zurück,
		// wenn der Zug möglich war, anderfalls false
		bool move(int x, int y);

		bool hasLines3(int color, int* x, int* y);

		int rating();
};

#endif
