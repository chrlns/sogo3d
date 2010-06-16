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
#ifdef SCHROTTI
		uint8_t cols[4][4][4];
#else
		uint8_t	cols[4][4]; // 4x4 Säulen
#endif
		int8_t	turnColor; // WHITE begins

	public:
		Playground();

		Playground* clone();
		void copyFrom(Playground* pg);

		// Prüft auf Siegbedingung. Gibt 0 zurück, falls kein Spieler gewonnen
		// hat oder 1 für BLACK oder 2 für WHITE.
		int isGameOver();
		
		void markWinLine();

		// Gibt den Wert an der Stelle (x, y, z) zurück. Durch die Bitschiebereien
		// ist diese Methode möglicherweise nicht sehr effizient.
		inline int get (uint8_t x, uint8_t y, uint8_t z)
		{
#ifdef SCHROTTI
			return this->cols[x][y][z];
#else
			uint8_t v = this->cols[x][y];
			return (v & (3 << z * 2)) >> (z * 2);
#endif
		}

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
