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
