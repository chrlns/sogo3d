#include "playground.h"
//#include <queue>

/*int max(Playground* root, int horizon, int color, int* x, int* y);

int min(Playground* root, int horizon, int color, int* ox, int* oy)
{
	// Maximale Tiefe noch nicht erreicht?
	if(horizon > 0 && (root->isGameOver() == 0))
	{
		int minmax = MAX_RATING;

		// Für jeden möglichen Zug muss ein Unterbaum erzeugt werden
		for(int x = 0; x < 4; x++)
		{
			for(int y = 0; y < 4; y++)
			{
				Playground* pg = root->clone();
				if(pg->move(x, y))
				{
					int optX = x;
					int optY = y;
					// Das neue Spielfeld ist gültig und sollte weiter untersucht
					int maxv = max(pg, horizon - 1, switchColor(color), &optX, &optY);
					minmax = maxv < minmax ? maxv : minmax;
					if(maxv < minmax) {
						minmax = maxv;
						*ox = optX;
						*oy = optY;
					}
				}
				delete pg;
			}
		}
		return minmax;
	}
	else
	{
		return root->rating(color);
	}
}

int max(Playground* root, int horizon, int color, int* ox, int* oy)
{
	// Maximale Tiefe noch nicht erreicht?
	if(horizon > 0 && (root->isGameOver() == 0))
	{
		int minmax = -MAX_RATING;

		// Für jeden möglichen Zug muss ein Unterbaum erzeugt werden
		for(int x = 0; x < 4; x++)
		{
			for(int y = 0; y < 4; y++)
			{
				Playground* pg = root->clone();
				if(pg->move(x, y))
				{
					int optX = x;
					int optY = y;
					// Das neue Spielfeld ist gültig und sollte weiter untersucht
					int minv = min(pg, horizon - 1, switchColor(color), &optX, &optY);
					if(minv > minmax) {
						minmax = minv;
						*ox = optX;
						*oy = optY;
					}
				}
				delete pg;
			}
		}
		return minmax;
	}
	else
	{
		return root->rating(color);
	}
}*/

// Nach: http://en.wikipedia.org/wiki/Negamax
int negamax(Playground* root, int horizon, int alpha, int beta, int color, int* ox, int* oy)
{
	if(horizon <= 0 || root->isGameOver() != EMPTY) 
	{
		return color == BLACK ? root->rating(color) : -root->rating(color);
	} 
	else 
	{
		// Für jeden möglichen Zug muss ein Unterbaum erzeugt werden
		for(int x = 0; x < 4; x++)
		{
			for(int y = 0; y < 4; y++)
			{
				Playground* pg = root->clone();
				if(pg->move(x, y))
				{
					int optX = x;
					int optY = y;
					// Das neue Spielfeld ist gültig und sollte weiter untersucht
					alpha = max(alpha, -negamax(pg, horizon - 1, -beta, -alpha, switchColor(color), &optX, &optY));
					if(alpha >= beta)
						return alpha;
				}
				delete pg;
			}
		}
		return alpha;
	}
}

/*
 * Führt den Minimax-Algorithmus aus.
 * root: aktuelles Spielfeld
 * color: die Farbe, die am Zug ist
 * horizon: wieviel Ebenen sollen im Baum untersucht werden.
 */
int minimax(Playground* root, int color, int horizon)
{
	int optX 	= -1;
	int optY 	= -1;
	int minmax	= color == BLACK ? -MAX_RATING : MAX_RATING; // Mit den jeweiligen Worstcase-Werten initialisieren

	for(int x = 0; x < 4; x++)
		for(int y = 0; y < 4; y++)
		{
			int v = negamax(root, horizon, -MAX_RATING, MAX_RATING, color, &optX, &optY);
			if((v > minmax && color == BLACK) || (v < minmax && color == WHITE))
			{
				optX = x;
				optY = y;
				minmax = v;
			}
		}
	dbgmsg("Minimax: " << minmax);
	dbgmsg("Idealer Zug: " << optX << " " << optY);
	root->move(optX, optY);
}
