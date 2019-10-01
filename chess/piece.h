#include <stdio.h> 
#include <iostream>
using namespace std;

#pragma once

enum piece_color{
	White = 0,
	Black = 1,
};

enum piece_type{
	Pawn = 0,
	Bishop = 1,
	Knight = 2,
	Rook = 3,
	Queen = 4,
	King = 5,
};

class square;

class piece{
	piece_color color;
	piece_type type;
	bool moved, captured;
	square* square_occupying;
	int en_passant_turn; 

public:

	piece_color get_color();

	void set_color(piece_color x);

	piece_type get_type();

	void set_type(piece_type x);

	bool get_moved();

	void set_moved(bool x);

	bool get_captured();

	void set_captured(bool x);

	square* get_square_occupying();

	void set_square_occupying(square* x);

	int get_en_passant_turn();

	void set_en_passant_turn(int x);



	bool standard_move_check(square* x);

	bool pawn_take_check(square* x);

	bool pawn_move_check(square* x);

	bool pawn_move_two_check(square* x);

	bool castle_move_check(square* x);

	bool en_passant_check(square* x, int turn);

};