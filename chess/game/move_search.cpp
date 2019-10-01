#include "game.h"


pawn_moves game::pawn_move_search(square* x) {
	pawn_moves moves;
	int search_length, search_height;
	piece* p;
	int direction;

	p = x->get_piece_occupying();


	switch(x->get_piece_occupying()->get_color()) {
		case 0: 
			direction = 1; 
			break;
		case 1: 
			direction = -1; 
			break;
	}

	search_length = x->get_square_length();
	search_height = x->get_square_height();

	moves.squares[0] = b->get_square(search_length, search_height + direction);
	moves.moves[0] = p->pawn_move_check(moves.squares[0]);

	if(p->get_moved() == 0 and moves.moves[0] == 1) {
	moves.squares[1] = b->get_square(search_length, search_height + (2*direction));
	moves.moves[1] = p->pawn_move_two_check(moves.squares[1]);	
	}
	else {
		moves.moves[1] = 0;
	}

	if(search_length > 0){
		moves.squares[2] = b->get_square(search_length - 1, search_height + (direction));
		moves.moves[2] = p->pawn_take_check(moves.squares[2]);
	}
	else{
		moves.moves[2] = 0;
	}

	if(search_length < 7){
		moves.squares[3] = b->get_square(search_length + 1, search_height + (direction));
		moves.moves[3] = p->pawn_take_check(moves.squares[3]);
	}
	else{
		moves.moves[3] = 0;
	}

	if(search_length > 0){
		moves.squares[4] = b->get_square(search_length - 1, search_height + (direction));
		moves.en_passant_squares[0] = b->get_square(search_length - 1, search_height);
		moves.moves[4] = p->en_passant_check(moves.en_passant_squares[0], turn);
	}
	else{
		moves.moves[4] = 0;
	}

	if(search_length < 7){
		moves.squares[5] = b->get_square(search_length + 1, search_height + (direction));
		moves.en_passant_squares[1] = b->get_square(search_length + 1, search_height);
		moves.moves[5] = p->en_passant_check(moves.en_passant_squares[1], turn);
	}
	else{
		moves.moves[5] = 0;
	}

	return moves;

}

bishop_moves game::bishop_move_search(square* x) {
	bishop_moves moves;
	int search_length, search_height;
	int new_square_length, new_square_height;
	piece* p;
	int x_direction, y_direction;
	bool move;
	piece_color c, attacking_color;
	square* temporary_move;
	piece* temporary_piece;

	p = x->get_piece_occupying();
	c = p->get_color();

	if(c == 0) {
		search_height = 0;
		attacking_color = Black;
	}
	else {
		search_height = 1;
		attacking_color = White;
	}

	search_length = x->get_square_length();
	search_height = x->get_square_height();

	for(int i = 0; i < 4; i++) {
		switch(i) {
			case 0:
				x_direction = 1;
				y_direction = 1;
				break;
			case 1: 
				x_direction = 1; 
				y_direction = -1; 
				break;
			case 2: 
				x_direction = -1; 
				y_direction = -1; 
				break;
			case 3: 
				x_direction = -1; 
				y_direction = 1; 
				break;
		}

		move = 1;

		for(int j = 0; j < 7; j++) {
			new_square_length = search_length + ( (j+1) * x_direction);
			new_square_height = search_height + ( (j+1) * y_direction);
			if(new_square_length <= 7 and new_square_length >= 0 and move == 1) {
				if(new_square_height <= 7 and new_square_height >= 0) {
					moves.squares[i][j] = b->get_square(new_square_length, new_square_height);
					moves.moves[i][j] =  p->standard_move_check(moves.squares[i][j]);

					if(moves.squares[i][j]->get_occupied() == 1){
						move = 0;
					}
				}
				else {
					move = 0;
					moves.moves[i][j] = 0;
				}
			}
			
			else {
				move = 0;
				moves.moves[i][j] = 0;
			}


		}
	}

	return moves;
}


knight_moves game::knight_move_search(square* x) {
	knight_moves moves;
	int search_length, search_height;
	int x_direction, y_direction;
	int new_square_length, new_square_height;
	piece* p;

	search_length = x->get_square_length();
	search_height = x->get_square_height();

	p = x->get_piece_occupying();

	for(int i = 0; i < 4; i++) {
		switch(i) {
			case 0: 
				x_direction = 1; 
				y_direction = 1; 
				break;
			case 1: 
				x_direction = 1; 
				y_direction = -1; 
				break;
			case 2: 
				x_direction = -1; 
				y_direction = -1; 
				break;
			case 3: 
				x_direction = -1;
				y_direction = 1; 
				break;
		}
		new_square_length = search_length + x_direction;
		new_square_height = search_height + (2*y_direction);

		moves.moves[i][0] = 0;

		if(new_square_length <= 7 and new_square_length >= 0) {
			if(new_square_height <= 7 and new_square_height >=0) {
				moves.squares[i][0] = b->get_square(new_square_length, new_square_height);
				moves.moves[i][0] = p->standard_move_check(moves.squares[i][0]);
			}
		}

		new_square_length = search_length + (2*x_direction);
		new_square_height = search_height + y_direction;

		moves.moves[i][1] = 0;

		if(new_square_length <= 7 and new_square_length >= 0) {
			if(new_square_height <= 7 and new_square_height >=0) {
				moves.squares[i][1] = b->get_square(new_square_length, new_square_height);
				moves.moves[i][1] = p->standard_move_check(moves.squares[i][1]);
			}
		}
	}

	return moves;

}

rook_moves game::rook_move_search(square* x) {
	rook_moves moves;
	int search_length, search_height;
	int new_square_length, new_square_height;
	piece* p;
	int x_direction, y_direction;
	bool move;

	p = x->get_piece_occupying();

	search_length = x->get_square_length();
	search_height = x->get_square_height();

	for(int i = 0; i < 4; i++) {
		switch(i) {
			case 0: 
				x_direction = 0; 
				y_direction = 1; 
			break;
			case 1: 
				x_direction = 1; 
				y_direction = 0; 
				break;
			case 2: 
				x_direction = 0; 
				y_direction = -1; 
				break;
			case 3: 
				x_direction = -1; 
				y_direction = 0; 
				break;
		}
		move = 1;

		for(int j = 0; j < 7; j++) {
			new_square_length = search_length + ((j+1)*x_direction);
			new_square_height = search_height + ((j+1)*y_direction);
			if(new_square_length <= 7 and new_square_length >= 0 and move == 1) {
				if(new_square_height <= 7 and new_square_height >= 0) {
					moves.squares[i][j] = b->get_square(new_square_length, new_square_height);
					moves.moves[i][j] =  p->standard_move_check(moves.squares[i][j]);
					
					if(moves.squares[i][j]->get_occupied() == 1){
						move = 0;
					}
				
				}
				else {
				move = 0;
				moves.moves[i][j] = 0;
				}
			
			}
			else {
				move = 0;
				moves.moves[i][j] = 0;
			}
		}
	}

	return moves;

}

queen_moves game::queen_move_search(square* x) {

	queen_moves moves;
	int search_length, search_height;
	int new_square_length, new_square_height;
	piece* p;
	int x_direction, y_direction;
	bool move;
	char a, c;

	p = x->get_piece_occupying();

	search_length = x->get_square_length();
	search_height = x->get_square_height();

	for(int i = 0; i < 8; i++) {
		switch(i) {
			case 0: 
				x_direction = 0; 
				y_direction = 1; 
				break;
			case 1: 
				x_direction = 1; 
				y_direction = 1; 
				break;
			case 2: 
				x_direction = 1; 
				y_direction = 0; 
				break;
			case 3: 
				x_direction = 1; 
				y_direction = -1; 
				break;
			case 4: 
				x_direction = 0; 
				y_direction = -1; 
				break;
			case 5: 
				x_direction = -1; 
				y_direction = -1; 
				break;
			case 6: 
				x_direction = -1; 
				y_direction = 0; 
				break;
			case 7: 
				x_direction = -1;
				y_direction = 1; 
				break;
		}

		move = 1;

		for(int j = 0; j < 7; j++) {
			new_square_length = search_length + ((j+1)*x_direction);
			new_square_height = search_height + ((j+1)*y_direction);
			if(new_square_length <= 7 and new_square_length >= 0 and move == 1) {
				if(new_square_height <= 7 and new_square_height >= 0) {
					moves.squares[i][j] = b->get_square(new_square_length, new_square_height);
					moves.moves[i][j] =  p->standard_move_check(moves.squares[i][j]);
					
					if(moves.squares[i][j]->get_occupied() == 1){
						move = 0;
					}
				
				}
				else {
					move = 0;
					moves.moves[i][j] = 0;
				}
			}
			else {
				move = 0;
				moves.moves[i][j] = 0;
			}
		}
	}

	return moves;
}

king_moves game::king_move_search(square* x) {
	king_moves moves;
	int search_length, search_height;
	int new_square_length, new_square_height;
	piece* p;
	piece_color c;

	int x_direction, y_direction;

	p = x->get_piece_occupying();
	c = p->get_color();

	search_length = x->get_square_length();
	search_height = x->get_square_height();

	for(int i = 0; i < 8; i++) {
		switch(i) {
			case 0: 
				x_direction = 0; 
				y_direction = 1; 
				break;
			case 1: 
				x_direction = 1; 
				y_direction = 1; 
				break;
			case 2: 
				x_direction = 1; 
				y_direction = 0; 
				break;
			case 3: 
				x_direction = 1; 
				y_direction = -1; 
				break;
			case 4: 
				x_direction = 0; 
				y_direction = -1; 
				break;
			case 5: 
				x_direction = -1; 
				y_direction = -1; 
				break;
			case 6: 
				x_direction = -1; 
				y_direction = 0; 
				break;
			case 7: 
				x_direction = -1;
				y_direction = 1; 
				break;
		}
		new_square_length = search_length + x_direction;
		new_square_height = search_height + y_direction;
		if(new_square_length <= 7 and new_square_length >= 0) {
			if(new_square_height <= 7 and new_square_height >= 0) {
				moves.squares[i] = b->get_square(new_square_length, new_square_height);
				moves.moves[i]=  p->standard_move_check(moves.squares[i]);
			}
		}
		else {
			moves.moves[i] = 0;
		}
	}	
	
	return moves;
}

castle_moves game::castle_move_search(square* x, bool check) {
	castle_moves moves;
	piece* p;
	piece_color c, attacking_color;
	int search_height;

	c = x->get_piece_occupying()->get_color();

	if(c == 0) {
		search_height = 0;
		attacking_color = Black;
	}
	else {
		search_height = 1;
		attacking_color = White;
	}

	moves.rook_squares[0] = b->get_square(0,search_height);
	moves.rook_squares[1] = b->get_square(7,search_height);

	moves.new_rook_squares[0] = b->get_square(3, search_height);
	moves.new_rook_squares[1] = b->get_square(5, search_height);

	moves.new_king_squares[0] = b->get_square(2, search_height);
	moves.new_king_squares[1] = b->get_square(6, search_height);
		
	moves.moves[0] = 1;
	moves.moves[1] = 1;

	p = x->get_piece_occupying();

	for(int i = 0; i < 2; i++) {
		
		if(check == 1) {
			moves.moves[i] = 0;
		}

		if(p->castle_move_check(moves.rook_squares[i]) == 0) {
			moves.moves[i] = 0;
		}
	}

	if(moves.moves[0] == 0 and moves.moves[1] == 0) {
		return moves;
	}

	for(int j = 1; j < 4; j++) {
		if(b->get_square(j, search_height)->get_occupied() == 1) {
			moves.moves[0] = 0;
		}
	}
	for(int j = 2; j < 4; j++) {
		if(attack_check(b->get_square(j, search_height), attacking_color) == 1) {
			moves.moves[0] = 0;
		}
	}

	for(int j = 5; j < 7; j++) {
		if(b->get_square(j, search_height)->get_occupied() == 1) {
			moves.moves[1] = 0;
		}
	}
	for(int j = 5; j < 7; j++) {
		if(attack_check(b->get_square(j, search_height), attacking_color) == 1) {
			moves.moves[1] = 0;
		}
	}
	return moves;
}
