#include "../board.h"
#include "move_structures.h"
using namespace std; 

class game {
public:
	board* b;
	piece* piece_list[32];
	square* king_square[2];
	piece* dummy_piece;
	square* dummy_square;

	bool white_check;
	bool black_check;

	bool timer;
	int timer_white, timer_black;
	int turn;

	board* get_board();
	void set_board(board* x);

	void set_turn(int x);
	void increment_turn();

	bool attack_check(square* x, piece_color c);
	bool check_move_check(square* x, square* y);
	bool checkmate_check(piece_color c);
	bool en_passant_move_check(square* x, square* y, square* z);
	bool move(square* x, square* y);
	bool en_passant(square* x, square* y);
	bool castle(square* x, square* y);

	pawn_moves moves_check(square* x, pawn_moves moves);
	bishop_moves moves_check(square* x, bishop_moves moves);
	knight_moves moves_check(square* x, knight_moves moves);
	rook_moves moves_check(square* x, rook_moves moves);
	queen_moves moves_check(square* x, queen_moves moves);
	king_moves moves_check(square* x, king_moves moves);

	pawn_moves pawn_move_search(square* x);
	bishop_moves bishop_move_search(square* x);
	knight_moves knight_move_search(square* x);
	rook_moves rook_move_search(square* x);
	queen_moves queen_move_search(square* x);
	king_moves king_move_search(square* x);
	castle_moves castle_move_search(square* x, bool check);

	game();

};

