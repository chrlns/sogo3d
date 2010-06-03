#ifndef __GAME_H_
#define __GAME_H_

#include "playground.h"

int minimax(Playground* root, int color, int horizon);

struct thread_args
{
	Playground* playground;
	int number;
	uint8_t horizon;
	int alpha; 
	int beta; 
	uint8_t color;
};

typedef struct thread_args thread_args_t;

#endif
