#include "game.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool game::attack_check(square* x, piece_color c) {

	int attacking_side, total;
	bool move, attacked;
	int k;

	attacked = 0;

	if(c == White) {
		attacking_side = 0;
	}
	else {
		attacking_side = 16;
	}

	total = attacking_side + 16;

	for(int i = attacking_side; i < total; i++) {

		switch(piece_list[i]->get_type()) {
			case Pawn: {
					pawn_moves moves = pawn_move_search(piece_list[i]->get_square_occupying()); 
					for(int j = 0; j < 4; j ++) {
						if(moves.moves[j] == 1){
							if(moves.squares[j] == x) {
								attacked = 1;
							}
						}
					}
					break;
			}

			case Bishop:	{
					bishop_moves moves = bishop_move_search(piece_list[i]->get_square_occupying()); 
					for(int j = 0; j < 4; j++) {
						move = 1;
						k = 0; 
						while(move == 1) {
							move = moves.moves[j][k];
							if(moves.squares[j][k] == x) {
								attacked = 1;
							}
							k++;
						}
					}
					break;
			}

			case Knight:	{
					knight_moves moves = knight_move_search(piece_list[i]->get_square_occupying());
					for(int j = 0; j < 4; j++) {
						for(int m = 0; m < 2; m++) {
							if(moves.moves[j][m] == 1) {
								if(moves.squares[j][m] == x) {
									attacked = 1;
								}
							}
						}
					}
					break;
			}

			case Rook:	{
					rook_moves moves = rook_move_search(piece_list[i]->get_square_occupying()); 
					for(int j = 0; j < 4; j++) {
						move = 1;
						k = 0; 
						while(move == 1) {
							move =  moves.moves[j][k];
							if(moves.squares[j][k] == x) {
								attacked = 1;
							}
							k++;
						}
					}
					break;
			}

			case Queen: {
					queen_moves moves = queen_move_search(piece_list[i]->get_square_occupying()); 
					for(int j = 0; j < 8; j++) {
						move = 1;
						k = 0; 
						while(move == 1) {
							move =  moves.moves[j][k];
							if(moves.squares[j][k] == x) {
								attacked = 1;
							}
							k++;
						}
					}
					break;
			}

			case King: {
					king_moves moves = king_move_search(piece_list[i]->get_square_occupying());
					for(int j = 0; j < 8; j++) {
						if(moves.moves[j] == 1) {
							if(moves.squares[j] == x) {
								attacked = 1;
							}
						}
					}
					break;
			}
		}
	}
	return attacked;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool game::check_move_check(square* x, square* y) {

	piece* moving_piece;
	piece* captured_piece;
	bool y_occupied, check;
	piece_color c, attacking_color;
	int king_color;

	y_occupied = y->get_occupied();

	moving_piece = x->get_piece_occupying();

	c = moving_piece->get_color();

	if(c==White) {
		attacking_color = Black;
		king_color = 0;
	}
	else {
		attacking_color = White;
		king_color = 1;
	}

	if(y_occupied == 1) {
		captured_piece = y->get_piece_occupying();
		captured_piece->set_square_occupying(dummy_square);
	}

	x->set_occupied(0);
	x->set_piece_occupying(dummy_piece);

	y->set_occupied(1);

	moving_piece->set_square_occupying(y);
	y->set_piece_occupying(moving_piece);

	if(moving_piece->get_type() == 5) {
		king_square[king_color] = y;
	}

	check = attack_check(king_square[king_color], attacking_color);

	x->set_occupied(1);
	x->set_piece_occupying(moving_piece);
	moving_piece->set_square_occupying(x);
	y->set_occupied(y_occupied);

	if(y_occupied == 1) {
		y->set_piece_occupying(captured_piece);
		captured_piece->set_square_occupying(y);
	}
	else {
		y->set_piece_occupying(dummy_piece);
	}

	if(moving_piece->get_type() == 5) {
		king_square[king_color] = x;
	}

	return check;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool game::en_passant_move_check(square* x, square* y, square* z) {

	piece* moving_piece;
	piece* captured_piece;
	bool y_occupied;
	piece_color c, attacking_color;
	int king_color;
	bool check;

	y_occupied = y->get_occupied();

	moving_piece = x->get_piece_occupying();

	c = moving_piece->get_color();

	if(c==White) {
		attacking_color = Black;
		king_color = 0;
	}
	else {
		attacking_color = White;
		king_color = 1;
	}

	captured_piece = y->get_piece_occupying();

	x->set_occupied(0);
	x->set_piece_occupying(dummy_piece);

	y->set_occupied(0);
	y->set_piece_occupying(dummy_piece);

	z->set_occupied(1);
	z->set_piece_occupying(moving_piece);


	check = attack_check(king_square[king_color], attacking_color);

	x->set_occupied(1);
	x->set_piece_occupying(moving_piece);
	
	y->set_occupied(1);
	y->set_piece_occupying(captured_piece);

	z->set_occupied(0);
	z->set_piece_occupying(dummy_piece);


	return check;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pawn_moves game::moves_check(square* x, pawn_moves moves){
	bool check;

	for(int i = 0; i < 4; i++){
		if(moves.moves[i] == 1){
			check = check_move_check(x, moves.squares[i]);
			if(check == 1){
				moves.moves[i] = 0;
			}
		}
	}
	for(int i = 4; i < 6; i++){
		if(moves.moves[i] == 1){
			check = en_passant_move_check(x, moves.en_passant_squares[i - 4], moves.squares[i]);
			if(check == 1){
				moves.moves[i] = 0;
			}
		}
	}
	return moves;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bishop_moves game::moves_check(square* x, bishop_moves moves){
	bool check, stop;
	int j;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 7; j++){
			if(moves.moves[i][j] == 1){
				check = check_move_check(x, moves.squares[i][j]);
				if(check == 1){
					moves.moves[i][j] = 0; 
				}
			}
		}
	}
	return moves;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

knight_moves game::moves_check(square* x, knight_moves moves){
	bool check;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 2; j++){
			if(moves.moves[i][j] == 1){
				check = check_move_check(x, moves.squares[i][j]);
				if(check == 1){
					moves.moves[i][j] = 0;
				}
			}
		}
	}
	return moves;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rook_moves game::moves_check(square* x, rook_moves moves){
	bool check, stop;
	int j;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 7; j++){
			if(moves.moves[i][j] == 1){
				check = check_move_check(x, moves.squares[i][j]);
				if(check == 1){
					moves.moves[i][j] = 0; 
				}
			}
		}
	}
	return moves;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

queen_moves game::moves_check(square* x, queen_moves moves){
	bool check;
	int j;

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 7; j++){
			if(moves.moves[i][j] == 1){
				check = check_move_check(x, moves.squares[i][j]);
				if(check == 1){
					moves.moves[i][j] = 0; 
				}
			}
		}
	}
	return moves;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

king_moves game::moves_check(square* x, king_moves moves){
	bool check;

	for(int i = 0; i < 8; i++){
		if(moves.moves[i] == 1){
			check = check_move_check(x, moves.squares[i]);
			if(check == 1){
				moves.moves[i] = 0;
			}
		}
	}
	return moves;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool game::checkmate_check(piece_color c) {
	int defending_side;
	bool move;
	int k;
	piece* p;

	if(c == 0) {
		defending_side = 0;
	}
	else {
		defending_side = 16;
	}

	for(int i = defending_side; i < (defending_side + 16); i++) {
		switch(piece_list[i]->get_type()) {
			case Pawn: {
					pawn_moves moves_unchecked = pawn_move_search(piece_list[i]->get_square_occupying()); 
					pawn_moves moves = moves_check(piece_list[i]->get_square_occupying(), moves_unchecked);
					for(int j = 0; j < 4; j ++) {
						if(moves.moves[j] == 1) {
							return 0;
						}
					}
					break;}

			case Bishop:	{
					bishop_moves moves_unchecked = bishop_move_search(piece_list[i]->get_square_occupying()); 
					bishop_moves moves = moves_check(piece_list[i]->get_square_occupying(), moves_unchecked);
					for(int j = 0; j < 4; j++) {
						for(int k = 0; k < 7; k++) {
							if(moves.moves[j][k] == 1) {
								return 0;
							}
						}
					}
					break;}

			case Knight:	{
					knight_moves moves_unchecked = knight_move_search(piece_list[i]->get_square_occupying());
					knight_moves moves = moves_check(piece_list[i]->get_square_occupying(), moves_unchecked);
					for(int j = 0; j < 4; j++) {
						for(int m = 0; m < 2; m++) {
							if(moves.moves[j][m] == 1) {
								return 0;	
							}
						}
					}
					break;}

			case Rook:	{
					rook_moves moves_unchecked = rook_move_search(piece_list[i]->get_square_occupying()); 
					rook_moves moves = moves_check(piece_list[i]->get_square_occupying(), moves_unchecked);
					for(int j = 0; j < 4; j++) {
						for(int k = 0; k < 7; k++) {
							if(moves.moves[j][k] == 1) {
								return 0;
							}
						}
					}
					break;}
			case Queen: {
					queen_moves moves_unchecked = queen_move_search(piece_list[i]->get_square_occupying()); 
					queen_moves moves = moves_check(piece_list[i]->get_square_occupying(), moves_unchecked);
					for(int j = 0; j < 8; j++) {
						for(int k = 0; k < 7; k++) {
							if(moves.moves[j][k] == 1) {
								return 0;
							}
						}
					}
					break;}

			case King: {
					king_moves moves_unchecked = king_move_search(piece_list[i]->get_square_occupying());
					king_moves moves = moves_check(piece_list[i]->get_square_occupying(), moves_unchecked);
					for(int j = 0; j < 8; j++) {
						if(moves.moves[j] == 1) {
							return 0;
						}
					}
					break;}
		}
	}
	return 1;
}