#ifndef __TYPES_H_
#define __TYPES_H_

#define EMPTY 0
#define BLACK 1
#define WHITE 2

#include <stdint.h>

union playground_t
{
	struct layers
	{
		uint32_t level3;
		uint32_t level2;
		uint32_t level1;
		uint32_t level0;
	};

	struct direct
	{
		uint8_t[16] data : 2;
	};
};

#endif
