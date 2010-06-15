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

Playground* currentPlayground = NULL;
bool enableZBuffer = true;
int horizon = 4;

void* playCPUagainsCPU(void* args)
{
	while(currentPlayground->isGameOver() == EMPTY)
	{
		sleep(1);
		minimax(currentPlayground, currentPlayground->getTurnColor(), horizon);
	}
	return NULL;
}

int main(int argc, char* argv[])
{
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
