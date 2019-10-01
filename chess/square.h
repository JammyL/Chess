#include "piece.h"
#pragma once

class square{

	bool occupied;
	piece* piece_occupying;
	int square_length;
	int square_height;
	public:
		void set_piece_occupying(piece* x);
		piece* get_piece_occupying();

		void set_occupied(bool x);
		bool get_occupied();

		void set_square_length(int x);
		int get_square_length();

		void set_square_height(int x);
		int get_square_height();

};


