#include "square.h"

piece_color piece::get_color() {
	return color;
}

void piece::set_color(piece_color x) {
	color = x;
}

piece_type piece::get_type() {
	return type;
}

void piece::set_type(piece_type x) {
	type = x;
}

bool piece::get_moved() {
	return moved;
}

void piece::set_moved(bool x) {
	moved = x;
}

bool piece::get_captured() {
	return captured;
}

void piece::set_captured(bool x) {
	captured = x;
}

square* piece::get_square_occupying() {
	return square_occupying;
}

void piece::set_square_occupying(square* x) {
	square_occupying = x;
}

int piece::get_en_passant_turn(){
	return en_passant_turn;
}

void piece::set_en_passant_turn(int x){
	en_passant_turn = x;
}


bool piece::standard_move_check(square* x) {
		bool x_occupied;

		x_occupied = x->get_occupied();
		if(x_occupied == 1) {
			
			piece_color x_color;
			x_color = x->get_piece_occupying()->get_color();
			
			if(x_color == color) {
				return 0;
			}

			else {return 1;};
		}
		else {return 1;}
}

bool piece::pawn_take_check(square* x) {
		bool x_occupied;

		x_occupied = x->get_occupied();
		if(x_occupied == 1) {

			piece_color x_color;
			x_color = x->get_piece_occupying()->get_color();

			if(x_color == color) {
				return 0;
			}

			else {
				return 1;
			}
		}
		else {
			return 0;
		}

}

bool piece::pawn_move_check(square* x) {
		if(x->get_occupied() == 0) {
			return 1;
		}
		else {
			return 0;
		}
}	

bool piece::pawn_move_two_check(square* x) {
		if(moved == 0 and x->get_occupied() == 0) {
			return 1;
		}
		else {return 0;}
}

bool piece::castle_move_check(square* x){

		if(moved == 0 and x->get_occupied() == 1 and x->get_piece_occupying()->get_moved() == 0) {
			return 1;	
		}
		else {return 0;};
		
}

bool piece::en_passant_check(square* x, int turn){

	if(x->get_occupied() == 1 and (turn - x->get_piece_occupying()->get_en_passant_turn()) == 1){
		return 1;
	}
	else{
		return 0;
	}
}
