#ifndef _PLAYGROUND_H_
#define _PLAYGROUND_H_

#include "types.h"
#include <stdint.h>

#define MAX_RATING 10000		/* Maximale Bewertungszahl (+|-) */

class Playground
{
	private:
		bool	isRated;
		int8_t	winnerCache;
		uint8_t	cols[4][4]; // 4x4 Säulen
		int8_t	turnColor; // WHITE begins

	public:
		Playground();

		Playground* clone();
		void copyFrom(Playground* pg);

		// Prüft auf Siegbedingung. Gibt 0 zurück, falls kein Spieler gewonnen
		// hat oder 1 für BLACK oder 2 für WHITE.
		int isGameOver();
		
		void markWinLine();

		int get (uint8_t x, uint8_t y, uint8_t z);
		void set (uint8_t x, uint8_t y, uint8_t z, uint8_t);

		// Setze Kugel an die angegebene Position und gibt true zurück,
		// wenn der Zug möglich war, anderfalls false
		bool move(int x, int y);

		bool hasLines3(int color, int* x, int* y);

		int rating();

		void setTurnColor(int color);
		int getTurnColor();
};

#endif
