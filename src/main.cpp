#include "types.h"
#include "playground.h"
#include <stdint.h>
#include <iostream>

void printPlaygroundPositions()
{
	std::cout << "Von oben gesehen:" << std::endl;
	std::cout << "|13 14 15 16|" << std::endl;
	std::cout << "| 9 10 11 12|" << std::endl;
	std::cout << "| 5  6  7  8|" << std::endl;
	std::cout << "| 1  2  3  4|" << std::endl;
}

int main(int argc, char* argv[])
{
	printPlaygroundPositions();
	Playground* pg = new Playground();
	pg->set(2,3,1, BLACK);

	if(pg->get(2,3,1) == BLACK)
	{
		std::cout << "Geht:" << pg->playground.layer[3] << std::endl;
	}
	else
	{
		std::cout << "Geht NICHT" << std::endl;
	}

	return 0;
}
