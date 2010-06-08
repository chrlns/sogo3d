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

int main(int argc, char* argv[])
{
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
		if(arg == "-h" || arg == "--help")
		{
			std::cout << "Parameter" << std::endl;
			std::cout << "-z|--no-zbuffer\tDisables depth buffering" << std::endl;
			std::cout << "-r|--horizon <num>\tNumber of recursions (horizon)" << std::endl;
		}
	}
	
 	// Start GUI
	init_gamewindow(&argc, argv);
 
	// Create empty playground
	currentPlayground = new Playground();

	// Start GLUT Event loop. Method returns when the game window is closed.
	glutMainLoop();

 	delete currentPlayground;
	return 0;
}
