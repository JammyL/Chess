#include "game.h"

game::game() {
	b = new board();
	dummy_piece = new piece();
	dummy_square = new square();
	dummy_piece->set_type(Bishop);
	dummy_piece->set_color(White);
	dummy_square->set_square_length(-1);
	dummy_square->set_square_height(-1);
	turn = 100;
	for(int k = 0; k < 16; k ++) {
		piece_list[k] = new piece();
		piece_list[k]->set_color(White);
		piece_list[k]->set_moved(0);
		piece_list[k]->set_en_passant_turn(0);
		piece_list[16 + k] = new piece();
		piece_list[16 + k]->set_color(Black);
		piece_list[16 + k]->set_moved(0);
		piece_list[16 + k]->set_en_passant_turn(0);
	}
	for(int k = 0; k < 8; k ++) {
		piece_list[k]->set_type(Pawn);
		piece_list[16 + k]->set_type(Pawn);
		b->get_square(k,1)->set_piece_occupying(piece_list[k]);
		piece_list[k]->set_square_occupying(b->get_square(k,1));
		b->get_square(k,6)->set_piece_occupying(piece_list[16 + k]);
		piece_list[16 + k]->set_square_occupying(b->get_square(k,6));
	}

	for(int k = 0; k < 2; k ++) {
		piece_list[8 + k]->set_type(Bishop);
		piece_list[24 + k]->set_type(Bishop);


		piece_list[10 + k]->set_type(Knight);
		piece_list[26 + k]->set_type(Knight);

		piece_list[12 + k]->set_type(Rook);
		piece_list[28 + k]->set_type(Rook);
	}

	piece_list[14]->set_type(Queen);
	piece_list[30]->set_type(Queen);
	piece_list[15]->set_type(King);
	piece_list[31]->set_type(King);

	b->get_square(3,0)->set_piece_occupying(piece_list[14]);
	piece_list[14]->set_square_occupying(b->get_square(3,0));
	b->get_square(4,0)->set_piece_occupying(piece_list[15]);
	piece_list[15]->set_square_occupying(b->get_square(4,0));
	b->get_square(3,7)->set_piece_occupying(piece_list[30]);
	piece_list[30]->set_square_occupying(b->get_square(3,7));
	b->get_square(4,7)->set_piece_occupying(piece_list[31]);
	piece_list[31]->set_square_occupying(b->get_square(4,7));

	b->get_square(2,0)->set_piece_occupying(piece_list[8]);
	piece_list[8]->set_square_occupying(b->get_square(2,0));
	b->get_square(5,0)->set_piece_occupying(piece_list[9]);	
	piece_list[9]->set_square_occupying(b->get_square(5,0));
	b->get_square(2,7)->set_piece_occupying(piece_list[24]);
	piece_list[24]->set_square_occupying(b->get_square(2,7));
	b->get_square(5,7)->set_piece_occupying(piece_list[25]);
	piece_list[25]->set_square_occupying(b->get_square(5,7));
	b->get_square(1,0)->set_piece_occupying(piece_list[10]);
	piece_list[10]->set_square_occupying(b->get_square(1,0));
	b->get_square(6,0)->set_piece_occupying(piece_list[11]);
	piece_list[11]->set_square_occupying(b->get_square(6,0));
	b->get_square(1,7)->set_piece_occupying(piece_list[26]);
	piece_list[26]->set_square_occupying(b->get_square(1,7));
	b->get_square(6,7)->set_piece_occupying(piece_list[27]);
	piece_list[27]->set_square_occupying(b->get_square(6,7));
	b->get_square(0,0)->set_piece_occupying(piece_list[12]);
	piece_list[12]->set_square_occupying(b->get_square(0,0));
	b->get_square(7,0)->set_piece_occupying(piece_list[13]);
	piece_list[13]->set_square_occupying(b->get_square(7,0));
	b->get_square(0,7)->set_piece_occupying(piece_list[28]);
	piece_list[28]->set_square_occupying(b->get_square(0,7));
	b->get_square(7,7)->set_piece_occupying(piece_list[29]);
	piece_list[29]->set_square_occupying(b->get_square(7,7));


	for(int k = 0; k < 8; k ++ ) {
		b->get_square(k,0)->set_occupied(true);
		b->get_square(k,1)->set_occupied(true);
		b->get_square(k,6)->set_occupied(true);
		b->get_square(k,7)->set_occupied(true);		
			for(int l = 2; l < 6; l ++){
				b->get_square(k,l)->set_occupied(false);
			}
	}
	king_square[0] = piece_list[15]->get_square_occupying();
	king_square[1] = piece_list[31]->get_square_occupying();
}

board* game::get_board() {
	return b;
}

void game::set_board(board* x) {
	b = x;
}

void game::set_turn(int x) {
	turn = x;
}

void game::increment_turn(){
	turn ++;
}

bool game::move(square* x, square* y) {

	piece* p;
	bool moved;
	if(x->get_occupied() == 0){
		cout << "This square is unoccupied\n";
		return 0;
	}
	p = x->get_piece_occupying();
	cout << "Moving Piece Pre:" << p->get_type() << "\n";

	moved = 0;

	switch(p->get_type()) {
			case Pawn: {
					pawn_moves moves_unchecked = pawn_move_search(x);
					pawn_moves moves = moves_check(x, moves_unchecked);

					for(int j = 0; j < 4; j ++) {
						if(moves.moves[j] == 1) {
							if(moves.squares[j] == y) {
								x->set_occupied(0);
								x->set_piece_occupying(dummy_piece);
								cout << "Moving Piece Post:" << p->get_type() << "\n";

								if(y->get_occupied() == 1) {
									y->get_piece_occupying()->set_captured(1);
									y->get_piece_occupying()->set_square_occupying(dummy_square);
								}

								y->set_occupied(1);
								y->set_piece_occupying(p);
								p->set_square_occupying(y);
								p->set_moved(1);
								
								if(j == 1){
									p->set_en_passant_turn(turn);
								}

								moved = 1;
							}
						}
					}
					break;
	}

			case Bishop:	{
					bishop_moves moves_unchecked = bishop_move_search(x); 
					bishop_moves moves = moves_check(x, moves_unchecked);
					cout << moves.squares[3][0]->get_square_length();
					cout << moves.squares[3][0]->get_square_height();
					cout << y->get_square_length();
					cout << y->get_square_height();

					for(int j = 0; j < 4; j++) {
						for(int k = 0; k < 7; k++) {
							if(moves.moves[j][k] == 1) {
								if(moves.squares[j][k] == y) {
									x->set_occupied(0);
									x->set_piece_occupying(dummy_piece);
									cout << "Moving Piece Post:" << p->get_type() << "\n";

									if(y->get_occupied() == 1) {
										y->get_piece_occupying()->set_captured(1);
										y->get_piece_occupying()->set_square_occupying(dummy_square);
									}

									y->set_occupied(1);
									y->set_piece_occupying(p);
									p->set_square_occupying(y);
									p->set_moved(1);
									moved = 1;
								}
							}
						}
					}
					break;}

			case Knight:	{
					knight_moves moves_unchecked = knight_move_search(x);
					knight_moves moves = moves_check(x, moves_unchecked);
					for(int j = 0; j < 4; j++) {
						for(int k = 0; k < 2; k++) {
							if(moves.moves[j][k] == 1) {
								if(moves.squares[j][k] == y) {
									x->set_occupied(0);
									x->set_piece_occupying(dummy_piece);
									cout << "Moving Piece Post:" << p->get_type() << "\n";

									if(y->get_occupied() == 1) {
										y->get_piece_occupying()->set_captured(1);
										y->get_piece_occupying()->set_square_occupying(dummy_square);
									}

									y->set_occupied(1);
									y->set_piece_occupying(p);
									p->set_square_occupying(y);
									p->set_moved(1);
									moved = 1;
								}
							}
						}
					}
					break;
			}

			case Rook:	{
					rook_moves moves_unchecked = rook_move_search(x); 
					rook_moves moves = moves_check(x, moves_unchecked);
					for(int j = 0; j < 4; j++) {
						for(int k = 0; k < 7; k++) {
							if(moves.moves[j][k] == 1) {
								if(moves.squares[j][k] == y) {
									x->set_occupied(0);
									x->set_piece_occupying(dummy_piece);

									if(y->get_occupied() == 1) {
										y->get_piece_occupying()->set_captured(1);
										y->get_piece_occupying()->set_square_occupying(dummy_square);
									}

									y->set_occupied(1);
									y->set_piece_occupying(p);
									p->set_square_occupying(y);
									p->set_moved(1);
									moved = 1;
								}
							}
						}
					}
					break;}

			case Queen: {
					queen_moves moves_unchecked = queen_move_search(x); 
					queen_moves moves = moves_check(x, moves_unchecked);
					for(int j = 0; j < 8; j++) {
						for(int k = 0; k < 7; k++) {
							if(moves.moves[j][k] == 1) {
								if(moves.squares[j][k] == y) {
									x->set_occupied(0);
									x->set_piece_occupying(dummy_piece);

									if(y->get_occupied() == 1) {
										y->get_piece_occupying()->set_captured(1);
										y->get_piece_occupying()->set_square_occupying(dummy_square);
									}

									y->set_occupied(1);
									y->set_piece_occupying(p);
									p->set_square_occupying(y);
									p->set_moved(1);
									moved = 1;
								}
							}
						}
					}
					break;}

			case King: {
					king_moves moves_unchecked = king_move_search(x);
					king_moves moves = moves_check(x, moves_unchecked);
					for(int j = 0; j < 8; j++) {
						if(moves.moves[j] == 1) {
							if(moves.squares[j] == y) {
								x->set_occupied(0);
								x->set_piece_occupying(dummy_piece);

								if(y->get_occupied() == 1) {
									y->get_piece_occupying()->set_captured(1);
									y->get_piece_occupying()->set_square_occupying(dummy_square);
								}

								y->set_occupied(1);
								y->set_piece_occupying(p);
								p->set_square_occupying(y);
								p->set_moved(1);
								moved = 1;
							}
						}
					}
					break;

			}
}
return moved;
}

bool game::castle(square* x, square* y){
	bool moved;
	castle_moves moves;
	piece* k;
	piece* r;
	moved = 0;
	bool check;

	if(x->get_piece_occupying()->get_color() == 0){
		check = white_check;
	}
	else{
		check = black_check;
	}

	moves = castle_move_search(x, check);
	for(int i = 0; i < 2; i++){
		if(moves.moves[i] == 1){
			if(moves.rook_squares[i] == y){
				x->set_occupied(0);
				x->set_piece_occupying(dummy_piece);

				y->set_occupied(0);
				y->set_piece_occupying(dummy_piece);

				moves.new_rook_squares[i]->set_occupied(1);
				moves.new_rook_squares[i]->set_piece_occupying(r);
				r->set_square_occupying(moves.new_rook_squares[i]);

				moves.new_king_squares[i]->set_occupied(1);
				moves.new_king_squares[i]->set_piece_occupying(k);
				r->set_square_occupying(moves.new_king_squares[i]);

				moved = 1;
			}
		}
	}
	return moved;

}

bool game::en_passant(square* x, square* y){
	bool moved;
	pawn_moves moves_unchecked;
	pawn_moves moves;
	piece* p;

	p = x->get_piece_occupying();

	if(p->get_type() != 0){
		throw string("This square does not contain a pawn!");
	}

	moves_unchecked = pawn_move_search(x);
	moves = moves_check(x, moves_unchecked);

	for(int i = 4; i < 6; i++){
		if(moves.moves[i] == 1){
			if(moves.squares[i] == y){
				x->set_occupied(0);
				x->set_piece_occupying(dummy_piece);

				y->set_piece_occupying(p);
				y->set_occupied(1);

				moves.en_passant_squares[i - 4]->get_piece_occupying()->set_square_occupying(dummy_square);
				moves.en_passant_squares[i - 4]->set_piece_occupying(dummy_piece);
				moves.en_passant_squares[i - 4]->set_occupied(0);

				moved = 1;

			}
		}
	}
	return moved;

}
