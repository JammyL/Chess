#include "board.h"
using namespace std;

board::board() {
	cout << "Creating Board\n";
	for (int i = 0; i < length; i ++) {
		for (int j = 0; j < height; j ++) {
			square board_array[i][j];
			get_square(i,j)->set_square_length(i);
			get_square(i,j)->set_square_height(j);
		}
	}
}

int board::get_length() {
	return length;
}

int board::get_height() {
	return height;
}

square* board::get_square(int x, int y) {
	return &board_array[x][y];
}