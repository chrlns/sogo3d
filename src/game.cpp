#include "playground.h"
#include "game.h"
#include <pthread.h>
#include <assert.h>

extern int horizon;

int threadResults[16];
pthread_t       sysThreadHandle[16];
pthread_attr_t  sysThreadAttrib[16];
uint64_t		children = 0;

int min(Playground* root, int horizon, int alpha, int beta, int color/*, int* ox, int* oy*/);

// alpha: untere Grenze
// beta: obere Grenze
// Methodname ist falsch, nicht wirklich Negamax
int max(Playground* root, int horizon, int alpha, int beta, int color/*, int* ox, int* oy*/)
{
	children++;
	if(horizon <= 0 || root->isGameOver() != 0) 
	{
		return root->rating();
	} 
	else 
	{
		int rating = root->rating();
		// Für jeden möglichen Zug muss ein Unterbaum erzeugt werden
		for(int x = 0; x < 4; x++)
		{
			for(int y = 0; y < 4; y++)
			{
				Playground* pg = root->clone();
				if(pg->move(x, y))
				{
					int value;

						//dbgmsg("Bewertung " << pg->rating());
						// Wir suchen das Maximum
						value = min(pg, horizon - 1, alpha, rating, switchColor(color));
						/*if(value < alpha)
						{
							//dbgmsg("Gekürzt Maximum!");
							delete pg;
							return value;
						}*/
						rating = MAX(rating, value);

					
				}
				delete pg;
			}
		}
		return rating;
	}
}

// alpha: untere Grenze
// beta: obere Grenze
// Methodname ist falsch, nicht wirklich Negamax
int min(Playground* root, int horizon, int alpha, int beta, int color/*, int* ox, int* oy*/)
{
	children++;
	if(horizon <= 0 || root->isGameOver() != 0) 
	{
		return root->rating();
	} 
	else 
	{
		int rating = root->rating();
		// Für jeden möglichen Zug muss ein Unterbaum erzeugt werden
		for(int x = 0; x < 4; x++)
		{
			for(int y = 0; y < 4; y++)
			{
				Playground* pg = root->clone();
				if(pg->move(x, y))
				{
					int value;
						// Wir suchen das Minimum
						value = min(pg, horizon - 1, rating, beta, switchColor(color));
						/*if(value > beta)
						{
							//dbgmsg("Gekürzt Minimum!");
							delete pg;
							return value;
						}*/
						rating = MIN(rating, value);

				}
				delete pg;
			}
		}
		return rating;
	}
}

void* enterThread(void* args)
{
	thread_args* targs = (thread_args*)args;
	if(targs->color == BLACK)
		threadResults[targs->number] = max(targs->playground, targs->horizon, targs->alpha, targs->beta, targs->color);
	else
		threadResults[targs->number] = min(targs->playground, targs->horizon, targs->alpha, targs->beta, targs->color);
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
	children = 0;
	int optX 	= -1;
	int optY 	= -1;
	int minmax	= color == BLACK ? -(100000) : (100000); // Mit den jeweiligen Worstcase-Werten initialisieren
	long starttime = time(NULL);

	// Wir führen den ersten Schritt manuell aus, da wir wissen wollen, in
	// welche Richtung wir weiterlaufen sollen.
	for(int x = 0; x < 4; x++)
	{
		for(int y = 0; y < 4; y++)
		{
			Playground* pg = root->clone();
			int n = x * 4 + y;
			if(pg->move(x, y))
			{
				//int v = negamax(pg, horizon, -MAX_RATING, MAX_RATING, switchColor(color));
				thread_args_t* args = new thread_args();
				args->playground	= pg;
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
			//delete pg;
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

	long calcTime = time(NULL) - starttime;

	// Anhand der Berechnungszeit den Horizont erhöhen und reduzieren
	std::cout << "Zugberechnung dauerte " << calcTime << " sec" << std::endl;
	if(calcTime < 30)
	{
		horizon++;
		std::cout << "Berechnungshorizont erhöht auf " << horizon << std::endl;
	}
	else if(calcTime > 300 && horizon > 4)
	{
		horizon--;
		std::cout << "Berechungshorizont reduziert auf " << horizon << std::endl;
	}

	// Ein paar Debugausgaben
	dbgmsg("Minimax: " << minmax);
	dbgmsg("Idealer Zug: " << optX << " " << optY);
	dbgmsg("Kinder: " << children);
	root->move(optX, optY);
	if(root->isGameOver() != EMPTY) 
	{
		dbgmsg("Spiel ist zu Ende!");		
	}
	else
	{
		dbgmsg("Am Zug ist " << root->turnColor);
	}

	return 0;
}
