/*
 *   SOGO
 *   see AUTHORS for the list of contributors
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "playground.h"
#include "types.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>

Playground::Playground()
{	
	for(int x = 0; x < 4; x++) 
	{
		for(int y = 0; y < 4; y++) 
		{
#ifdef SCHROTTI
			for(int z = 0; z < 4; z++)
			{
				this->cols[x][y][z] = 0;
			}
#else
			this->cols[x][y] = 0;
#endif
		}
	}
	
	this->isRated	= false;
	this->turnColor = WHITE;
	this->winnerCache = -1;
}

int Playground::getTurnColor()
{
	return this->turnColor;
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

	// horizontal lines direction: [x]
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
	for(int x = 0; x < 4 ; x++)
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

	// diagonal bars (low to high) 
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


	// inner diagonal cross (low to high)
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
	for(int z = 0; z < 4; z++)
	{
	    if( (get(3,3,z)!=EMPTY) && (get(3,3,z)==get(2,2,z)) && (get(2,2,z)==get(1,1,z)) && (get(1,1,z)==get(0,0,z)) )
	    {
	       this->winnerCache = get(3, 3, z);
	       return this->winnerCache;
	    }    
	}    

	for(int z = 0; z < 4; z++)
	{
	    if( (get(0,3,z)!=EMPTY) && (get(0,3,z)==get(1,2,z)) && (get(1,2,z)==get(2,1,z)) && (get(2,1,z)==get(3,0,z)) )
	    {
	       this->winnerCache = get(0,3,z);
	       return this->winnerCache;
	    }    
	}

	return this->winnerCache;
}


void Playground::markWinLine() 
{

	// Vertical staves
	for(int x = 0; x < 4; x++)
	{
		for(int y = 0 ; y < 4; y++)
		{                   
			if((get(x, y, 0)!=EMPTY) 
			&& (get(x, y, 0)==get(x, y, 1)) && (get(x, y, 1)==get(x, y, 2)) && (get(x, y, 2)==get(x, y, 3)) )
			{
				set(x, y, 0, WINLINE);
				set(x, y, 1, WINLINE);
				set(x, y, 2, WINLINE);
				set(x, y, 3, WINLINE);
				return;
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
				set(0, y, z, WINLINE);
				set(1, y, z, WINLINE);
				set(2, y, z, WINLINE);
				set(3, y, z, WINLINE);
				return;
			}
		}
	}

	// horizontal lines direction: [y]
	for(int x = 0; x < 4 ; x++)
	{
		for(int z = 0; z < 4; z++)
		{                   
			if( (get(x, 0, z)!=EMPTY) && (get(x, 0, z)==get(x, 1, z)) && (get(x, 1, z)==get(x, 2, z)) && (get(x, 2, z)==get(x, 3, z)) )
			{
				set(x, 0, z, WINLINE);
				set(x, 1, z, WINLINE);
				set(x, 2, z, WINLINE);
				set(x, 3, z, WINLINE);
				return;
			}
		}
	}

	// diagonal bars (low to high) ------------------------------------------------------------------------
	// direction: [x]
	for(int y = 0; y < 4; y++)
	{
		if( (get(0,y,0)!=EMPTY) && (get(0,y,0)==get(1,y,1)) && (get(1,y,1)==get(2,y,2)) && (get(2,y,2)==get(3,y,3)) )
		{ 
			set(0,y,0, WINLINE);
			set(1,y,1, WINLINE);
			set(2,y,2, WINLINE);
			set(3,y,3, WINLINE);
			return;
		}
		if( (get(3,y,0)!=EMPTY) && (get(3,y,0)==get(2,y,1)) && (get(2,y,1)==get(1,y,2)) && (get(1,y,2)==get(0,y,3)) )
		{
			set(0,y,3, WINLINE);
			set(1,y,2, WINLINE);
			set(2,y,1, WINLINE);
			set(3,y,0, WINLINE);
			return;
		}
	}

	// direction: [y] (low to high)
	for(int x = 0; x < 4; x++)
	{
		if( (get(x,0,0)!=EMPTY) && (get(x,0,0)==get(x,1,1)) && (get(x,1,1)==get(x,2,2)) && (get(x,2,2)==get(x,3,3)) )
		{ 
			set(x,0,0, WINLINE);
			set(x,1,1, WINLINE);
			set(x,2,2, WINLINE);
			set(x,3,3, WINLINE);
			return;
		}

		if( (get(x,3,0)!=EMPTY) && (get(x,3,0)==get(x,2,1)) && (get(x,2,1)==get(x,1,2)) && (get(x,1,2)==get(x,0,3)) )
		{
			set(x,3,0, WINLINE);
			set(x,2,1, WINLINE);
			set(x,1,2, WINLINE);
			set(x,0,3, WINLINE);
			return;
		}
	}

	// inner diagonal cross (low to high) --------------------------------------------------------------
	if( (get(0,0,0)!=EMPTY) && (get(0,0,0)==get(1,1,1)) &&(get(1,1,1)==get(2,2,2)) && (get(2,2,2)==get(3,3,3)) )
	{ 
		set(0,0,0, WINLINE);
		set(1,1,1, WINLINE);
		set(2,2,2, WINLINE);
		set(3,3,3, WINLINE);
		return;
	}
	if( (get(3,3,0)!=EMPTY) && (get(3,3,0)==get(2,2,1)) && (get(2,2,1)==get(1,1,2)) && (get(1,1,2)==get(0,0,3)) )
	{
		set(3,3,0, WINLINE);
		set(2,2,1, WINLINE);
		set(1,1,2, WINLINE);
		set(0,0,3, WINLINE);
		return;
	}
	if( (get(3,0,0)!=EMPTY) && (get(3,0,0)==get(2,1,1)) && (get(2,1,1)==get(1,2,2)) && (get(1,2,2)==get(0,3,3)) )
	{
		set(3,0,0, WINLINE);
		set(2,1,1, WINLINE);
		set(1,2,2, WINLINE);
		set(0,3,3, WINLINE);
		return;
	}
	if( (get(0,3,0)!=EMPTY) && (get(0,3,0)==get(1,2,1)) && (get(1,2,1)==get(2,1,2)) && (get(2,1,2)==get(3,0,3)) )
	{
		set(0,3,0, WINLINE);
		set(1,2,1, WINLINE);
		set(2,1,2, WINLINE);
		set(3,0,3, WINLINE);
		return;
	}
	// inner diagonal cross (horizontal bars)
	for(int z = 0; z < 4; z++)
	{
	    if( (get(3,3,z)!=EMPTY) && (get(3,3,z)==get(2,2,z)) && (get(2,2,z)==get(1,1,z)) && (get(1,1,z)==get(0,0,z)) )
	    {
	    	set(3,3,z, WINLINE);	
	    	set(2,2,z, WINLINE);	
	    	set(1,1,z, WINLINE);	
	    	set(0,0,z, WINLINE);	
	       return;
	    }    
	}    

	for(int z = 0; z < 4; z++)
	{
	    if( (get(0,3,z)!=EMPTY) && (get(0,3,z)==get(1,2,z)) && (get(1,2,z)==get(2,1,z)) && (get(2,1,z)==get(3,0,z)) )
	    {
		    set(0,3,z, WINLINE);
		    set(1,2,z, WINLINE);
		    set(2,1,z, WINLINE);
		    set(3,0,z, WINLINE);
	       return;
	    }    
	}

	return;
}

// Diese Methode kann nur Bits setzen, jedoch nicht löschen
// (was für das Spiel im Grunde auch nicht benötigt wird)
void Playground::set (uint8_t x, uint8_t y, uint8_t z, uint8_t value)
{
#ifdef SCHROTTI
	this->cols[x][y][z] = value;
#else
	this->cols[x][y]	|= value << (z * 2);
#endif
	this->winnerCache	= -1;
	this->isRated		= false;
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
	int rating = 0;
	int threefoldWhite = 0;
	int threefoldBlack = 0;
	int countBlack = 0;
	int countWhite = 0;
	int countEmpty = 0;

	// #############################################################
	// auf siegbrett prüfen
	// testen ob weiss oder schwarz gewonnen hat & entsprechend bewerten

	if(isGameOver() == BLACK)
	{
		rating += MAX_RATING;
		//return rating;
	} 
	else if(isGameOver() == WHITE)
	{
		rating += -MAX_RATING;
		//return rating;
	}
	

	// #############################################################
	// auf offene 3er lines prüfen
	

	// threefold on vertical staves
	for(int x = 0; x < 4; x++)
	{
		for(int y = 0 ; y < 4; y++)
		{                   
			if((get(x, y, 0)!=EMPTY ) 
			&& ( get(x, y, 0)==get(x, y, 1)) 
			&& ( get(x, y, 3)==EMPTY ))
			{

				if( (get(x, y, 1) == get(x, y, 2)) )
				{
					if((get(x, y, 0)==BLACK))
					{
						threefoldBlack += 2;
					}
					else
					{	
						threefoldWhite += 2;
					}
				}
				else 
				{
					if((get(x, y, 0)==BLACK))
					{
						threefoldBlack++;
					}
					else
					{	
						threefoldWhite++;
					}
				}

				// testen ob schwarz oder weiss

				// entsprechend bewerten

			}
		}
	}
	rating += threefoldBlack;
	rating -= threefoldWhite;

	// threefold on horizontal lines direction: [x] ------------------------------------------------------------
	for(int y = 0; y < 4; y++)
	{
		for(int z = 0; z < 4; z++)
		{
			countBlack=0;
			countWhite=0;
			countEmpty=0;

			for(int x = 0; x < 4; x++)
			{

				int actualColor = get(x, y, z);
				if( actualColor == EMPTY )
				{ 	
					countEmpty++;
					if(countEmpty > 2)
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
			}
		
			if(countBlack == 3 && countEmpty == 1)
			{
				rating = rating+30;
			}
			else if (countWhite == 3 && countEmpty == 1)
			{
				rating = rating-30;					
			}
			else if(countBlack == 2 && countEmpty == 2)
			{
				rating++;
			}	
			else if(countWhite == 2 && countEmpty == 2)
			{
				rating--;
			}
			
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
		countBlack=0;
		countWhite=0;
		countEmpty=0;
                   
			for(int y = 0; y < 4; y++)
			{
				int actualColor = get(x, y, z);
				if( actualColor == EMPTY )
				{ 	
					countEmpty++;
					if(countEmpty > 2)
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
			}
		
			if(countBlack == 3 && countEmpty == 1)
			{
				rating = rating+30;
			}
			else if (countWhite == 3 && countEmpty == 1)
			{
				rating = rating-30;					
			}
			else if(countBlack == 2 && countEmpty == 2)
			{	
				rating++;
			}	
			else if(countWhite == 2 && countEmpty == 2)
			{
				rating--;				

			}
			
		}
	}
	
	countBlack=0;
	countWhite=0;
	countEmpty=0;

 
	// diagonal bars (low to high)
	// direction: [x]
	
	for(int y = 0; y < 4 ; y++)
	{
		countBlack=0;
		countWhite=0;
		countEmpty=0;
		for(int x = 0, z = 0; x < 4; x++, z=x)
		{
			int actualColor = get(x, y, z);
			if( actualColor == EMPTY )
			{ 	
				countEmpty++;
				if(countEmpty > 2)
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
				rating = rating+30;
			}
			else if (countWhite == 3 && countEmpty == 1)
			{
				rating = rating-30;					
			}
			else if(countBlack == 2 && countEmpty == 2)
			{	
				rating++;
			}	
			else if(countWhite == 2 && countEmpty == 2)
			{
				rating--;
			}
		}
		countBlack=0;
		countWhite=0;
		countEmpty=0;

		for(int x = 0, z = 3; x < 4; x++, z=3-x)
		{
			int actualColor = get(x, y, z);
			if( actualColor == EMPTY )
			{ 	
				countEmpty++;
				if(countEmpty > 2)
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
				rating = rating+30;
			}
			else if (countWhite == 3 && countEmpty == 1)
			{
				rating = rating-30;					
			}
			else if(countBlack == 2 && countEmpty == 2)
			{	
				rating++;
			}	
			else if(countWhite == 2 && countEmpty == 2)
			{
				rating--;
			}
		}
		countBlack=0;
		countWhite=0;
		countEmpty=0;		
	}



	// diagonal bars (low to high)
	// direction: [x]
	
	for(int x = 0; x < 4 ; x++)
	{
		countBlack=0;
		countWhite=0;
		countEmpty=0;		

		for(int y = 0, z = 0; y < 4; y++, z=y)
		{
			int actualColor = get(x, y, z);
			if( actualColor == EMPTY )
			{ 	
				countEmpty++;
				if(countEmpty > 2)
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
				rating = rating+30;
			}
			else if (countWhite == 3 && countEmpty == 1)
			{
				rating = rating-30;					
			}
			else if(countBlack == 2 && countEmpty == 2)
			{	
				rating++;
			}	
			else if(countWhite == 2 && countEmpty == 2)
			{
				rating--;
			}
		}
		countBlack=0;
		countWhite=0;
		countEmpty=0;
		for(int y = 0, z = 3; y < 4; y++, z=3-y)
		{
			int actualColor = get(x, y, z);

			if( actualColor == EMPTY )
			{ 	
				countEmpty++;
				if(countEmpty > 2)
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
				rating = rating+30;
			}
			else if (countWhite == 3 && countEmpty == 1)
			{
				rating = rating-30;					
			}
			else if(countBlack == 2 && countEmpty == 2)
			{					
				rating++;
			}	
			else if(countWhite == 2 && countEmpty == 2)
			{
				rating--;
			}
		}
		countBlack=0;
		countWhite=0;
		countEmpty=0;		
	}



	countBlack=0;
	countWhite=0;
	countEmpty=0;
	// diagonals
	// inner diagonal cross (hoizontal bars)
	int actualColor = 0;
	//int z=0;
	for(int z=0; z<=3; z++)
	{
		for(int xy = 0; xy < 4; xy++)
		{
			actualColor = get(xy,xy,z);
			if( actualColor!=EMPTY) 
			{
				if(actualColor==BLACK)
				{
					countBlack++;
				}
				else
				{
					countWhite++;
				}
			}
			else
			{	
				countEmpty++;
			}
			
		}
		if(countBlack == 3 && countEmpty == 1)
		{
			rating = rating+30;
		}
		else if (countWhite == 3 && countEmpty == 1)
		{
			rating = rating-30;					
		}
		else if(countBlack == 2 && countEmpty == 2)
		{	
			rating++;
		}	
		else if(countWhite == 2 && countEmpty == 2)
		{
			rating--;
		}

		countBlack=0;
		countWhite=0;
		countEmpty=0;

		for(int x = 0, y = 3; x < 4; x++,y--)
		{
			actualColor = get(x,y,z);
			if( actualColor!=EMPTY) 
			{
				if(actualColor==BLACK)
				{
					countBlack++;
				}
				else
				{
					countWhite++;
				}
			}
			else
			{	
				countEmpty++;
			}
			
		}

		if(countBlack == 3 && countEmpty == 1)
		{
			rating = rating+30;
		}
		else if (countWhite == 3 && countEmpty == 1)
		{
			rating = rating-30;					
		}
		else if(countBlack == 2 && countEmpty == 2)
		{	
			rating++;
		}	
		else if(countWhite == 2 && countEmpty == 2)
		{
			rating--;
		}
		countBlack=0;
		countWhite=0;
		countEmpty=0;

	}


	countBlack=0;
	countWhite=0;
	countEmpty=0;

	for (int i=0;i<4;i++) 
	{
			actualColor = get(i,i,i);
			if( actualColor!=EMPTY) 
			{
				if(actualColor==BLACK)
				{
					countBlack++;
				}
				else
				{
					countWhite++;
				}
			}
			else
			{	
				countEmpty++;
			}

	}
	if(countBlack == 3 && countEmpty == 1)
	{
		rating = rating+30;
	}
	else if (countWhite == 3 && countEmpty == 1)
	{
		rating = rating-30;					
	}
	else if(countBlack == 2 && countEmpty == 2)
	{	
		rating++;
	}	
	else if(countWhite == 2 && countEmpty == 2)
	{
		rating--;
	}


	countBlack=0;
	countWhite=0;
	countEmpty=0;
	
	for (int i=0;i<4;i++) 
	{
			actualColor = get(3-i,i,i);
			if( actualColor!=EMPTY) 
			{
				if(actualColor==BLACK)
				{
					countBlack++;
				}
				else
				{
					countWhite++;
				}
			}
			else
			{	
				countEmpty++;
			}

	}
	if(countBlack == 3 && countEmpty == 1)
	{
		rating = rating+30;
	}
	else if (countWhite == 3 && countEmpty == 1)
	{
		rating = rating-30;					
	}
	else if(countBlack == 2 && countEmpty == 2)
	{	
		rating++;
	}	
	else if(countWhite == 2 && countEmpty == 2)
	{
		rating--;
	}

	countBlack=0;
	countWhite=0;
	countEmpty=0;
	
	for (int i=0;i<4;i++) 
	{
			actualColor = get(i,3-i,i);
			if( actualColor!=EMPTY) 
			{
				if(actualColor==BLACK)
				{
					countBlack++;
				}
				else
				{
					countWhite++;
				}
			}
			else
			{	
				countEmpty++;
			}

	}
	if(countBlack == 3 && countEmpty == 1)
	{
		rating = rating+30;
	}
	else if (countWhite == 3 && countEmpty == 1)
	{
		rating = rating-30;					
	}
	else if(countBlack == 2 && countEmpty == 2)
	{	
		rating++;
	}	
	else if(countWhite == 2 && countEmpty == 2)
	{
		rating--;
	}

	countBlack=0;
	countWhite=0;
	countEmpty=0;
	
	for (int i=0;i<4;i++) 
	{
			actualColor = get(3-i,3-i,i);
			if( actualColor!=EMPTY) 
			{
				if(actualColor==BLACK)
				{
					countBlack++;
				}
				else
				{
					countWhite++;
				}
			}
			else
			{	
				countEmpty++;
			}

	}
	if(countBlack == 3 && countEmpty == 1)
	{
		rating = rating+30;
	}
	else if (countWhite == 3 && countEmpty == 1)
	{
		rating = rating-30;					
	}
	else if(countBlack == 2 && countEmpty == 2)
	{	
		rating++;
	}	
	else if(countWhite == 2 && countEmpty == 2)
	{
		rating--;
	}
	return rating;
}

void Playground::copyFrom(Playground* pg) 
{
	memcpy(this, pg, sizeof(Playground));
	/*
	for(int x = 0; x < 4; x++) 
	{
		for(int y = 0; y < 4; y++) 
		{
			this->cols[x][y] =  pg->cols[x][y];
		}
	}
	
	this->turnColor = pg->turnColor;
	this->winnerCache = pg->winnerCache;
	*/
}


Playground* Playground::clone()
{
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

void Playground::setTurnColor(int color)
{
	this->turnColor = color;
}
