#include "square.h"
#pragma once

#define length 8
#define height 8

enum square_length {
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
};


class board {
	square board_array[length][height];

	public:
		
		int get_length();
		int get_height();

		square* get_square(int, int);


	board();
};

