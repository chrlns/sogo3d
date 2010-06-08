#include "playground.h"
#include "types.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>

#include <map>

//std::map<uint64_t, std::map<uint64_t, int16_t>> ratings;

Playground::Playground()
{	
	for(int x = 0; x < 4; x++) 
	{
		for(int y = 0; y < 4; y++) 
		{
			this->cols[x][y] = 0;
		}
	}
	
	this->turnColor = WHITE;
	this->winnerCache = -1;
}

// Prüft auf Siegbedingung. Gibt 0 zurück, falls kein Spieler gewonnen
// hat oder 1 für BLACK oder 2 für WHITE.
int Playground::isGameOver()
{
	if(this->winnerCache != -1)
	{
		return this->winnerCache;
	}
	
	this->winnerCache = 0;

	// Vertical staves
	for(int x = 0; x < 4; x++)
	{
		for(int y = 0 ; y < 4; y++)
		{                   
			if((get(x, y, 0)!=EMPTY) 
			&& (get(x, y, 0)==get(x, y, 1)) && (get(x, y, 1)==get(x, y, 2)) && (get(x, y, 2)==get(x, y, 3)) )
			{
				this->winnerCache = get(x, y, 0);
				return this->winnerCache;
			}
		}
	}

	// horizontal lines direction: [x] ------------------------------------------------------------
	for(int y = 0; y < 4; y++)
	{
		for(int z = 0; z < 4; z++)
		{                   
			if((get(0, y, z)!=EMPTY) 
			&& (get(0, y, z)==get(1, y, z)) && (get(1, y, z)==get(2, y, z)) && (get(2, y, z)==get(3, y, z)) )
			{
				// winner=get(0, y, z);
				this->winnerCache = get(0, y, z);
				return this->winnerCache;
			}
		}
	}

	// horizontal lines direction: [y]
	for(int x = 0; x <4 ; x++)
	{
		for(int z = 0; z < 4; z++)
		{                   
			if( (get(x, 0, z)!=EMPTY) && (get(x, 0, z)==get(x, 1, z)) && (get(x, 1, z)==get(x, 2, z)) && (get(x, 2, z)==get(x, 3, z)) )
			{
				// winner=get(0, y, z);
				this->winnerCache = get(x, 0, z);
				return this->winnerCache;
			}
		}
	}

	// diagonal bars (low to high) ------------------------------------------------------------------------
	// direction: [x]
	for(int y = 0; y < 4; y++)
	{
		if( (get(0,y,0)!=EMPTY) && (get(0,y,0)==get(1,y,1)) && (get(1,y,1)==get(2,y,2)) && (get(2,y,2)==get(3,y,3)) )
		{ 
			this->winnerCache = get(0,y,0);
			return this->winnerCache;
		}

		if( (get(3,y,0)!=EMPTY) && (get(3,y,0)==get(2,y,1)) && (get(2,y,1)==get(1,y,2)) && (get(1,y,2)==get(0,y,3)) )
		{
			this->winnerCache = get(3,y,0);
			return this->winnerCache;
		}
	}

	// direction: [y] (low to high)
	for(int x = 0; x < 4; x++)
	{
		if( (get(x,0,0)!=EMPTY) && (get(x,0,0)==get(x,1,1)) && (get(x,1,1)==get(x,2,2)) && (get(x,2,2)==get(x,3,3)) )
		{ 
			this->winnerCache = get(x,0,0);
			return this->winnerCache;
		}

		if( (get(x,3,0)!=EMPTY) && (get(x,3,0)==get(x,2,1)) && (get(x,2,1)==get(x,1,2)) && (get(x,1,2)==get(x,0,3)) )
		{
			this->winnerCache = get(x,3,0);
			return this->winnerCache;
		}
	}


	// inner diagonal cross (low to high) --------------------------------------------------------------
	if( (get(0,0,0)!=EMPTY) && (get(0,0,0)==get(1,1,1)) &&(get(1,1,1)==get(2,2,2)) && (get(2,2,2)==get(3,3,3)) )
	{ 
		this->winnerCache = get(0,0,0); // eigentlich besser erst auf 3,3,3 zu testen da unwahrscheinlicher
		return this->winnerCache;
	}
	if( (get(3,3,0)!=EMPTY) && (get(3,3,0)==get(2,2,1)) && (get(2,2,1)==get(1,1,2)) && (get(1,1,2)==get(0,0,3)) )
	{
		this->winnerCache = get(3,3,0);
		return this->winnerCache;
	}
	    
	    
	if( (get(3,0,0)!=EMPTY) && (get(3,0,0)==get(2,1,1)) && (get(2,1,1)==get(1,2,2)) && (get(1,2,2)==get(0,3,3)) )
	{
		this->winnerCache = get(3,0,0);
		return this->winnerCache;
	}
	if( (get(0,3,0)!=EMPTY) && (get(0,3,0)==get(1,2,1)) && (get(1,2,1)==get(2,1,2)) && (get(2,1,2)==get(3,0,3)) )
	{
		this->winnerCache = get(0,3,0);
		return this->winnerCache;
	}
	// inner diagonal cross (horizontal bars)
	for(int z = 0; z <= 3; z++)
	{
	    if( (get(3,3,z)!=EMPTY) && (get(3,3,z)==get(2,2,z)) && (get(2,2,z)==get(1,1,z)) && (get(1,1,z)==get(0,0,z)) )
	    {
	       this->winnerCache = get(3, 3, z);
	       return this->winnerCache;
	    }    
	}    

	for(int z = 0; z <= 3; z++)
	{
	    if( (get(0,3,z)!=EMPTY) && (get(0,3,z)==get(1,2,z)) && (get(1,2,z)==get(2,1,z)) && (get(2,1,z)==get(3,0,z)) )
	    {
	       this->winnerCache = get(0,3,z);
	       return this->winnerCache;
	    }    
	}

	return this->winnerCache;
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
	this->winnerCache = -1;
}

// Sucht nach drei Kugeln in einer Reihe der angegeben Farbe, bei denen
// die Position der 4. Kugel setzbar ist.
bool Playground::hasLines3(int color, int* x, int* y)
{
	return false;
}

// Bewertung des aktuellen Spielfeldes aus der Sicht von Schwarz
int Playground::rating()
{
	// Erstmal im Cache nachgucken, ob da was drin ist
	//ratings[][]
	
	int rating = 0;
	int threefoldWhite = 0;
	int threefoldBlack = 0;
	int countBlack = 0;
	int countWhite = 0;
	int countEmpty = 0;
	int count = 0;
	// #############################################################
	// auf siegbrett prüfen
	// testen ob weiss oder schwarz gewonnen hat & entsprechend bewerten

	if(isGameOver() == WHITE)
	{
		//rating -= 500;
		return -MAX_RATING;
	} 
	else if(isGameOver() == BLACK)
	{
		//rating += 500;
		return MAX_RATING;
	}
	

	// #############################################################
	// auf offene 3er lines prüfen
	

	// threefold on vertical staves
	for(int x = 0; x < 4; x++)
	{
		for(int y = 0 ; y < 4; y++)
		{                   
			if((get(x, y, 0)!=EMPTY) 
			&& (get(x, y, 0)==get(x, y, 1)) && (get(x, y, 1)==get(x, y, 2))
			&& (get(x, y, 3)==EMPTY) )
			{
				// testen ob schwarz oder weiss
				if((get(x, y, 0)==BLACK))
				{
					threefoldBlack++;
				}
				else
				{	
					threefoldWhite++;
				}
				// entsprechend bewerten
			}
		}
	}

	// threefold on horizontal lines direction: [x] ------------------------------------------------------------
	for(int y = 0; y < 4; y++)
	{
		for(int z = 0; z < 4; z++)
		{                   

			for(int x = 0; x < 4; x++)
			{
				int actualColor = get(x, y, z);
				if( actualColor == EMPTY )
				{ 	
					countEmpty++;
					if(countEmpty > 1)
					{
						break;
					}
				}
				else if(actualColor == BLACK)
				{ 
					countBlack++;
				}
				else
				{ 
					countWhite++;
				}
				
				if(countBlack == 3)
				{
					rating++;
				}
				else if (countWhite == 3)
				{
					rating--;
				}
			}
			countBlack=0;
			countWhite=0;
			countEmpty=0;
		}
	}
	countBlack=0;
	countWhite=0;
	countEmpty=0;
	// threefold on horizontal lines direction: [y]
	for(int x = 0; x <4 ; x++)
	{
		for(int z = 0; z < 4; z++)
		{                   
			for(int y = 0; y < 4; y++)
			{
				int actualColor = get(x, y, z);
				if( actualColor == EMPTY )
				{ 	
					countEmpty++;
					if(countEmpty > 1)
					{
						break;
					}
				}
				else if(actualColor == BLACK)
				{ 
					countBlack++;
				}
				else
				{ 
					countWhite++;
				}
				
				if(countBlack == 3 && countEmpty == 1)
				{
					rating++;
				}
				else if (countWhite == 3 && countEmpty == 1)
				{
					rating--;
				}
			}
			countBlack=0;
			countWhite=0;
			countEmpty=0;
		}
	}

	// wenn 3er line gefunden, checkn ob schwarz oder weiss

	// entsprechend (ob schwarz oder weiss) bewertung vornehmen
	
	rating += threefoldBlack;
	rating -= threefoldWhite;
	
	return rating;
	// #############################################################
	// wenn mehrere 3er lines gefunden, prüfen ob die fehlende kugel bei bei den beiden lines die selbe ist (ob beide offenen lines sich mit der selben kugel "schliessen lassen"
	
	
	/*int ratingVal=0;

	// clone playground 

	// on cloned playground:
	Playground* tP = this->clone();
	// fill als empty places with current color
	for(int x=0;x<=3;x++)
	{
		for(int y=0;y<=3;y++)
		{
			while(tP->move(x, y));
		}     
	}

	// now check how many winning combinations are left 
	
	// Vertical staves
	for(int x=0;x<=3;x++)
	{
		for(int y=0;y<=3;y++)
		{                   
			if( (get(x, y, 0)!=EMPTY) && (get(x, y, 0)==get(x, y, 1)) && (get(x, y, 1)==get(x, y, 2)) && (get(x, y, 2)==get(x, y, 3)) )
			{
				ratingVal++;
			}
		}
	}

	// horizontal lines direction: [x]
	for(int y=0;y<=3;y++)
		{
		for(int z=0;z<=3;z++)
		{                   
			if( (get(0, y, z)!=EMPTY) && (get(1, y, z)==get(2, y, z)) && (get(2, y, z)==get(3, y, z)) && (get(3, y, z)==get(4, y, z)) )
			{
				ratingVal++;
			}
		}
	}

	// horizontal lines direction: [y]
	for(int x=0;x<=3;x++)
	{
		for(int z=0;z<=3;z++)
		{                   
			if( (get(x, 0, z)!=EMPTY) && (get(x, 0, z)==get(x, 1, z)) && (get(x, 1, z)==get(x, 2, z)) && (get(x, 2, z)==get(x, 3, z)) )
			{
				ratingVal++;
			}
		}
	}

	// diagonal bars (low to high)
	// direction: [x]
	for(int y=0;y<=3;y++)
	{
		if( (get(0,y,0)!=EMPTY) && (get(0,y,0)==get(1,y,1)) && (get(1,y,1)==get(2,y,2)) && (get(2,y,2)==get(3,y,3)) )
		{ 
			ratingVal++;
		}

		if( (get(3,y,0)!=EMPTY) && (get(3,y,0)==get(2,y,1)) && (get(2,y,1)==get(1,y,2)) && (get(1,y,2)==get(0,y,3)) )
		{
			ratingVal++;
		}
	}

	// direction: [y] (low to high)
	for(int x=0;x<=3;x++)
	{
		if( (get(x,0,0)!=EMPTY) && (get(x,0,0)==get(x,1,1)) && (get(x,1,1)==get(x,2,2)) && (get(x,2,2)==get(x,3,3)) )
		{ 
			ratingVal++;
		}

		if( (get(x,3,0)!=EMPTY) && (get(x,3,0)==get(x,2,1)) && (get(x,2,1)==get(x,1,2)) && (get(x,1,2)==get(x,0,3)) )
		{
			ratingVal++;
		}
	}

	// inner diagonal cross (low to high)
	if( (get(0,0,0)!=EMPTY) && (get(0,0,0)==get(1,1,1)) && (get(1,1,1)==get(2,2,2)) && (get(2,2,2)==get(3,3,3)) )
	{ 
		ratingVal++;
	}
	if( (get(3,3,0)!=EMPTY) && (get(3,3,0)==get(2,2,1)) && (get(2,2,1)==get(1,1,2)) && (get(1,1,2)==get(0,0,3)) )
	{
		ratingVal++;
	}
	    
	    
	if( (get(3,0,0)!=EMPTY) && (get(3,0,0)==get(2,1,1)) && (get(2,1,1)==get(1,2,2)) && (get(1,2,2)==get(0,3,3)) )
	{
		ratingVal++;
	}
	if( (get(0,3,0)!=EMPTY) && (get(0,3,0)==get(1,2,1)) && (get(1,2,1)==get(2,1,2)) && (get(2,1,2)==get(3,0,3)) )
	{
		ratingVal++;
	}
	// inner diagonal cross (horizontal bars)
	for(int z=0;z<=3;z++)
	{
	    if( (get(3,3,z)!=EMPTY) && (get(3,3,z)==get(2,2,z)) && (get(2,2,z)==get(1,1,z)) && (get(1,1,z)==get(0,0,z)) )
	    {
	       ratingVal++;
	    }    
	}    

	for(int z=0;z<=3;z++)
	{
	    if( (get(0,3,z)!=EMPTY) && (get(0,3,z)==get(1,2,z)) && (get(1,2,z)==get(2,1,z)) && (get(2,1,z)==get(3,0,z)) )
	    {
	       ratingVal++;
	    }    
	} 
*/
}

Playground* Playground::clone()
{
	//Playground* clone = new Playground(*this);
	/*for(int x = 0; x < 4; x++) 
	{
		for(int y = 0; y < 4; y++) 
		{
			clone->cols[x][y] = this->cols[x][y];
		}
	}
	clone->turnColor = this->turnColor;
	clone->winnerCache = this->winnerCache;*/
	//memcpy(clone, this, sizeof(Playground));
	return new Playground(*this);
}

bool Playground::move(int x, int y)
{
	for(int z = 0; z < 4; z++) 
	{
		if(get(x, y, z) == EMPTY) 
		{
			set(x, y, z, this->turnColor);
			this->turnColor = switchColor(this->turnColor);
			return true;
		}
	}
	return false;
}
