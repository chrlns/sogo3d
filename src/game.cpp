#include "playground.h"

// alpha: untere Grenze
// beta: obere Grenze
// Methodname ist falsch, nicht wirklich Negamax
int negamax(Playground* root, int horizon, int alpha, int beta, int color/*, int* ox, int* oy*/)
{
	if(horizon <= 0 || root->isGameOver() != 0) 
	{
	/*	int rating = color == BLACK ? root->rating() : -root->rating();
		if(rating != 0)
		{
			dbgmsg("Negamax returns root->rating() = " << rating);
		}
		return rating;
		* */
		return root->rating();
	} 
	else 
	{
		int rating = 0;
		// Für jeden möglichen Zug muss ein Unterbaum erzeugt werden
		for(int x = 0; x < 4; x++)
		{
			for(int y = 0; y < 4; y++)
			{
				Playground* pg = root->clone();
				if(pg->move(x, y))
				{
					int value;
					if(color == BLACK)
					{
						// Wir suchen das Maximum
						value = negamax(pg, horizon - 1, alpha, rating, switchColor(color));
						if(value <= alpha)
						{
							//dbgmsg("Gekürzt Maximum!");
							delete pg;
							return value;
						}
						rating = max(rating, value);
					}
					else if(color == WHITE)
					{
						// Wir suchen das Minimum
						value = negamax(pg, horizon - 1, rating, beta, switchColor(color));
						if(value >= beta)
						{
							//dbgmsg("Gekürzt Minimum!");
							delete pg;
							return value;
						}
						rating = min(rating, value);
					}
					//int optX = x;
					//int optY = y;
					// Das neue Spielfeld ist gültig und sollte weiter untersucht
					//alpha = max(alpha, -negamax(pg, horizon - 1, -beta, -alpha, switchColor(color)/*, &optX, &optY*/));
					//if(alpha >= beta)
					//	return beta;
				}
				delete pg;
			}
		}
		return rating;
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

	// Wir führen den ersten Schritt manuell aus, da wir wissen wollen, in
	// welche Richtung wir weiterlaufen sollen.
	for(int x = 0; x < 4; x++)
	{
		for(int y = 0; y < 4; y++)
		{
			Playground* pg = root->clone();
			if(pg->move(x, y))
			{
				int v = negamax(pg, horizon, -MAX_RATING, MAX_RATING, switchColor(color));
				dbgmsg("Zug " << x << " " << y << " ergebnis " << v);
				if((v > minmax && color == BLACK) || (v < minmax && color == WHITE))
				{
					optX = x;
					optY = y;
					minmax = v;
				}
			}
			delete pg;
		}
	}
	dbgmsg("Minimax: " << minmax);
	dbgmsg("Idealer Zug: " << optX << " " << optY);
	root->move(optX, optY);
	if(root->isGameOver() != EMPTY) 
	{
		dbgmsg("Spiel ist zu Ende!");		
	}
	else
	{
		dbgmsg("Am Zug ist " << root->turnColor);
	}
}
