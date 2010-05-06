#ifndef __TYPES_H_
#define __TYPES_H_

#define EMPTY 0
#define BLACK 1
#define WHITE 2

#include <stdint.h>

struct playground_t
{
	uint32_t level3 : 32;
	uint32_t level2 : 32;
	uint32_t level1 : 32;
	uint32_t level0 : 32;
};

#endif
