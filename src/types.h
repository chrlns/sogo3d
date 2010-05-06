#ifndef __TYPES_H_
#define __TYPES_H_

#define EMPTY 0
#define BLACK 1
#define WHITE 2

#include <stdint.h>

union playground_t
{
	uint32_t  layer[4];
};

#endif
