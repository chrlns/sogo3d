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
#include "game.h"
#include <pthread.h>
#include <assert.h>
#include <stdio.h>

extern int horizon;

int threadResults[16];
pthread_t       sysThreadHandle[16];
pthread_attr_t  sysThreadAttrib[16];
uint64_t		children = 0;
int				overallCPUTime = 0;
int				t0 = 5;
int				t1 = 40;
bool			dynamicHorizon = false;

void setLastBall(int x, int y, int z);
int min(Playground* root, int horizon, int alpha, int beta, int color/*, int* ox, int* oy*/);

// alpha: untere Grenze
// beta: obere Grenze
int max(Playground* root, int horizon, int alpha, int beta, int color/*, int* ox, int* oy*/)
{
#ifdef DEBUG
	children++;
#endif
	if(horizon <= 0 || root->isGameOver() != 0) 
	{
		return root->rating();
	} 
	else 
	{
		//int rating = root->rating();
		// Für jeden möglichen Zug muss ein Unterbaum erzeugt werden
		for(int x = 0; x < 4; x++)
		{
			for(int y = 0; y < 4; y++)
			{
				Playground* pg = root + 1;	// Lustige pointerarithmetik
				pg->copyFrom(root);
				if(pg->move(x, y))
				{
					int value = min(pg, horizon - 1, alpha, beta, switchColor(color));
					if(value >= beta)
						{
//							delete pg;
             				return beta;
             			}
         			if(value > alpha)
             			alpha = value;
					//rating = MAX(rating, value);
				}
//				delete pg;
			}
		}
		return alpha;
	}
}

// alpha: untere Grenze
// beta: obere Grenze
int min(Playground* root, int horizon, int alpha, int beta, int color/*, int* ox, int* oy*/)
{
#ifdef DEBUG
	children++;
#endif
	if(horizon <= 0 || root->isGameOver() != 0) 
	{
		return root->rating();
	} 
	else 
	{
		//int rating = root->rating();
		// Für jeden möglichen Zug muss ein Unterbaum erzeugt werden
		for(int x = 0; x < 4; x++)
		{
			for(int y = 0; y < 4; y++)
			{
				Playground* pg = root + 1;	// Lustige pointerarithmetik
				pg->copyFrom(root);
				if(pg->move(x, y))
				{
					int value = max(pg, horizon - 1, alpha, beta, switchColor(color));
					if(value <= alpha)
					{
//						delete pg;
						return alpha;
					}
				 	if(value < beta)
						beta = value;
						//rating = MIN(rating, value);

				}
//				delete pg;
			}
		}
		return beta;
	}
}

void* enterThread(void* args)
{
	thread_args* targs = (thread_args*)args;
	if(targs->color == BLACK)
		threadResults[targs->number] = max(targs->playground, targs->horizon, targs->alpha, targs->beta, targs->color);
	else
		threadResults[targs->number] = min(targs->playground, targs->horizon, targs->alpha, targs->beta, targs->color);

	std::cout << "Thread " << targs->number << " fertig mit ergebnis " << threadResults[targs->number] << std::endl;
	delete targs->playground;
	delete targs;
	return NULL;
}

/*
 * Führt den Minimax-Algorithmus aus.
 * root: aktuelles Spielfeld
 * color: die Farbe, die am Zug ist
 * horizon: wieviel Ebenen sollen im Baum untersucht werden.
 */
int minimax(Playground* root, int color, int argHorizon)
{
#ifdef DEBUG
	children = 0;
#endif
	int optX 	= -1;
	int optY 	= -1;
	int minmax	= color == BLACK ? -(100000) : (100000); // Mit den jeweiligen Worstcase-Werten initialisieren
	long starttime = time(NULL);

	// Wir führen den ersten Schritt manuell aus, da wir wissen wollen, in
	// welche Richtung wir weiterlaufen sollen.
	std::cout << "Grösse von Playground ist " << sizeof(Playground) << std::endl;
	for(int x = 0; x < 4; x++)
	{
		for(int y = 0; y < 4; y++)
		{
			Playground* playgrounds = new Playground[32]; // Sollte in 4K passen
			//printf("%p\n", playgrounds);
			playgrounds[0].copyFrom(root);
			//Playground* pg = root->clone();
			int n = x * 4 + y;
			if(playgrounds[0].move(x, y))
			{
				thread_args_t* args = new thread_args();
				args->playground	= playgrounds;
				args->horizon		= argHorizon;
				args->alpha			= -100000;
				args->beta			= 100000;
				args->color			= switchColor(color);
				args->number		= n;

				// Run thread
				assert(pthread_create(&(sysThreadHandle[n]), NULL, enterThread, args) == 0);
			}
			else
			{
				sysThreadHandle[n] = 0;
			}
			// delete pg; // Hier nicht möglich, da pg noch innerhalb des Threads
			// verwendet wird. Thread löscht Instanz selbst.
		}
	}

	for(int x = 0; x < 4; x++)
	{
		for(int y = 0; y < 4; y++)
		{
			int n = x * 4 + y;
			if(sysThreadHandle[n] != 0)
			{
				dbgmsg("Waiting for Thread #" << n);
			
				pthread_join(sysThreadHandle[n], NULL);
				int v = threadResults[n];
				dbgmsg("Zug " << x << " " << y << " ergebnis " << v);
				if((v > minmax && color == BLACK) || (v < minmax && color == WHITE))
				{
					optX = x;
					optY = y;
					minmax = v;
				}
			}
		}
	}

	int calcTime = time(NULL) - starttime;
	overallCPUTime += calcTime;

	// Anhand der Berechnungszeit den Horizont erhöhen und reduzieren
	std::cout << "Zugberechnung dauerte " << calcTime << " sec" << std::endl;
	std::cout << "Gesamt-CPU-Zeit: " << overallCPUTime << " sec" << std::endl;
	if(dynamicHorizon)
	{
		if(calcTime < t0 && horizon < 30)
		{
			horizon++;
			std::cout << "Berechnungshorizont erhöht auf " << horizon << std::endl;
		}
		else if(calcTime > t1 && horizon > 4)
		{
			horizon--;
			std::cout << "Berechungshorizont reduziert auf " << horizon << std::endl;
		}
	}

	// Ein paar Debugausgaben
	dbgmsg("Minimax: " << minmax);
	dbgmsg("Idealer Zug: " << optX << " " << optY);
	dbgmsg("Kinder: " << children);

	for(int z = 0; z < 4; z++) 
	{
		if(root->get(optX, optY, z) == EMPTY)
		{
			setLastBall(optX, optY, z);
			z = 4;
		}
	}

	// Performe AI move
	root->move(optX, optY);
	
	if(root->isGameOver() != EMPTY) 
	{
		dbgmsg("Spiel ist zu Ende!");		
	}
	else
	{
		dbgmsg("Am Zug ist " << root->getTurnColor());
	}

	return 0;
}
