#ifndef __TYPES_H_
#define __TYPES_H_

#include <iostream>

#define EMPTY 0
#define BLACK 1
#define WHITE 2

#define switchColor(color) \
	color == BLACK ? WHITE : BLACK

#define max(a, b) \
	a >= b ? a : b
	
#ifndef DEBUG
#define dbgmsg(msg)
#else
#define dbgmsg(msg) \
	std::cout << "DEBUG: " << msg << std::endl;
#endif

#include <stdint.h>

#endif
