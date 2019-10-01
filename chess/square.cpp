#include "square.h"

void square::set_piece_occupying(piece* x) {
	piece_occupying = x;
}

piece* square::get_piece_occupying() {
	if(occupied == 0){
		throw string("This square is unoccupied!\n");
	}
	if(occupied == 1){
		return piece_occupying;
	}
}

void square::set_occupied(bool x) {
	occupied = x;
}

bool square::get_occupied() {
	return occupied;
}

void square::set_square_length(int x) {
	square_length = x;
}

int square::get_square_length() {
	return square_length;
}

void square::set_square_height(int x) {
	square_height = x;
}

int square::get_square_height() {
	return square_height;
}