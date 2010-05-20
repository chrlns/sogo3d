#include "playground.h"

Playground::Playground()
{
	this->playground.layer[0] = 0;
	this->playground.layer[1] = 0;
	this->playground.layer[2] = 0;
	this->playground.layer[3] = 0;
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
	return (this->playground.layer[y] & (3 << (x + z * 4) * 2)) >> 2 * (x + z * 4);	
}

void Playground::set (uint8_t x, uint8_t y, uint8_t z, uint8_t value)
{
	this->playground.layer[y] |= (value << ((x + z * 4) * 2));
}

int Playground::rating(int color)
{
	return 1;
}

Playground* Playground::clone()
{
	Playground* clone = new Playground();
	clone->playground = this->playground;
	return clone;
}

bool Playground::move(int x, int z, int color)
{
	return false;
}
