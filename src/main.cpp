#include "types.h"
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
	return 0;
}
