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

#include "game.h"
#include "gui.h"
#include "types.h"
#include "playground.h"
#include <stdint.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Playground* currentPlayground = NULL;
bool enableZBuffer = true;
int horizon = 4;
bool noCPU = false;

extern bool dynamicHorizon;
extern int t0, t1;

void* playCPUagainsCPU(void* args)
{
	// gerade rekursionstiefe -> weiss gewinnt, ungerade -> schwarz gewinnt ?
	while(currentPlayground->isGameOver() == EMPTY)
	{
		sleep(1);
		minimax(currentPlayground, currentPlayground->getTurnColor(), horizon);
	}
	
	if (currentPlayground->isGameOver() == WHITE) 
		std::cout << "Weiss hat gewonnen" << std::endl;
	else if (currentPlayground->isGameOver() == BLACK)
		std::cout << "Schwarz hat gewonnen" << std::endl;
		
	currentPlayground->markWinLine();
	return NULL;
}

int main(int argc, char* argv[])
{
#ifdef SCHROTTI
	std::cout << "Schrotti's version" << std::endl;
#endif
	bool cpuOnly = false;

 	// Start GUI
	init_gamewindow(&argc, argv);

	// Create empty playground
	currentPlayground = new Playground();

	// Parse command line arguments
	for(int n = 1; n < argc; n++)
	{
		std::string arg = std::string(argv[n]);
		if(arg == "-z" || arg == "--no-zbuffer")
		{
			enableZBuffer = false;
			continue;
		}
		if(arg == "-r" || arg == "--horizon")
		{
			horizon = atoi(argv[++n]);
			continue;
		}
		if(arg == "-rd")
		{
			dynamicHorizon = true;
			continue;
		}
		if(arg == "-b" || arg == "--play-black")
		{
			currentPlayground->setTurnColor(BLACK);
			minimax(currentPlayground, BLACK, horizon);
			continue;
		}
		if(arg == "-c" || arg == "--cpu-only")
		{
			cpuOnly = true;
			continue;
		}
		if(arg == "-nc")
		{
			noCPU = true;
			continue;
		}
		if(arg == "-t0")
		{
			t0 = atoi(argv[++n]);
			continue;
		}
		if(arg == "-t1")
		{
			t1 = atoi(argv[++n]);
			continue;
		}
		if(arg == "-h" || arg == "--help")
		{
			std::cout << "Parameter" << std::endl;
			std::cout << "-b|--play-black\tPlayer plays black" << std::endl;
			std::cout << "-c|--cpu-only\tComputer plays agains computer" << std::endl;
			std::cout << "-r|--horizon <num>\tNumber of recursions (horizon)" << std::endl;
			std::cout << "-z|--no-zbuffer\tDisables depth buffering" << std::endl;
		}
	}

	if(cpuOnly)
	{
		pthread_t cpuOnlyThread;
		pthread_create(&cpuOnlyThread, NULL, playCPUagainsCPU, NULL);
		glutMainLoop();
	}
	else
	{
		// Start GLUT Event loop. Method returns when the game window is closed.
		glutMainLoop();
	}
 	delete currentPlayground;
	return 0;
}
