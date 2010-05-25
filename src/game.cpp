#include "playground.h"
#include <queue>

int max(Playground* root, int horizon, int color);

int min(Playground* root, int horizon, int color)
{
	// Maximale Tiefe noch nicht erreicht?
	if(horizon > 0 || !root->isGameOver())
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
					// Das neue Spielfeld ist gültig und sollte weiter untersucht
					int maxv = max(pg, horizon - 1, switchColor(color));
					minmax = maxv < minmax ? maxv : minmax;
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

int max(Playground* root, int horizon, int color)
{
	// Maximale Tiefe noch nicht erreicht?
	if(horizon > 0 || !root->isGameOver())
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
					// Das neue Spielfeld ist gültig und sollte weiter untersucht
					int minv = min(pg, horizon - 1, switchColor(color));
					minmax = minv > minmax ? minv : minmax;
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

/*
 * Führt den Minimax-Algorithmus aus.
 * root: aktuelles Spielfeld
 * color: die Farbe, die am Zug ist
 * horizon: wieviel Ebenen sollen im Baum untersucht werden.
 */
int minimax(Playground* root, int color, int horizon)
{
	int minmax = max(root, horizon, color);
}
