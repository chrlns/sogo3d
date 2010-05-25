#include "playground.h"
#include "types.h"

Playground::Playground()
{	
	for(int x = 0; x < 4; x++) {
		for(int y = 0; y < 4; y++) {
			this->cols[x][y] = 0;
		}
	}
	
	this->turnColor = WHITE;
}

// Prüft auf Siegbedingung. Gibt 0 zurück, falls kein Spieler gewonnen
// hat oder 1 für BLACK oder 2 für WHITE.
int Playground::isGameOver()
{
	return 0;
}

// Gibt den Wert an der Stelle (x, y, z) zurück. Durch die Bitschiebereien
// ist diese Methode möglicherweise nicht sehr effizient.
int Playground::get (uint8_t x, uint8_t y, uint8_t z)
{
	uint8_t v = this->cols[x][y];
	return (v & (3 << z * 2)) >> (z * 2);
}

// Diese Methode kann nur Bits setzen, jedoch nicht löschen
// (was für das Spiel im Grunde auch nicht benötigt wird)
void Playground::set (uint8_t x, uint8_t y, uint8_t z, uint8_t value)
{
	this->cols[x][y] |= value << (z * 2);
}

// Bewertung des aktuellen Spielfeldes
int Playground::rating(int color)
{
	return 1;
}

Playground* Playground::clone()
{
	Playground* clone = new Playground();
	for(int x = 0; x < 4; x++) {
		for(int y = 0; y < 4; y++) {
			clone->cols[x][y] = this->cols[x][y];
		}
	}
	clone->turnColor = this->turnColor;
	return clone;
}

bool Playground::move(int x, int y)
{
	for(int z = 0; z < 4; z++) {
		if(get(x, y, z) == EMPTY) {
			set(x, y, z, this->turnColor);
			this->turnColor = switchColor(this->turnColor);
			return true;
		}
	}
	return false;
}
