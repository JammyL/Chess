#include <stdio.h>
#include <iostream>
#include "../board.h"
using namespace std;

struct pawn_moves{
	square* squares[6];
	bool moves[6];
	square* en_passant_squares[2];
};

struct bishop_moves{
	square* squares[4][7];
	bool moves[4][7];
};

struct knight_moves{
	square* squares[4][2];
	bool moves[4][2];
};

struct rook_moves{
	square* squares[4][7];
	bool moves[4][7];
};

struct queen_moves{
	square* squares[8][7];
	bool moves[8][7];
};

struct king_moves{
	square* squares[8];
	bool moves[8];
};

struct castle_moves{
	square* rook_squares[2];
	square* new_rook_squares[2];
	square* new_king_squares[2];
	bool moves[2];
};



