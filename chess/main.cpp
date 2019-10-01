#include <stdio.h>
#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include "game/game.h"

bool turn(string s, game* g) {
	
	bool valid_input = 1;

	bool move_success = 0;

	square* x[2];

	string arr[3];

	int square_length[2];
	int square_height[2];
 
    regex word_regex("(\\S+)");
    auto words_begin = 
        sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();

    int j = 0;

 
    // std::cout << "Words longer than " << N << " characters:\n";
    for (sregex_iterator i = words_begin; i != words_end; ++i) {
    	if(j > 2){
    		cout << "Expression is too long\n";
    		break;
    	}
    	else{
        	smatch match = *i;
        	string match_str = match.str();
        	arr[j] = match_str;
        	j++;
    	}
 	}

 	for(int i = 0; i < 2; i ++){

 		square_length[i] = arr[i + 1][0] - 'A';
 		square_height[i] = arr[i + 1][1] - '1';

 		if(square_length[j] < 0 or square_length[i] > 7){
 			cout << "Invalid input. Square not on board.\n";
 			valid_input = 0;
 		}
 		if(square_height[j] < 0 or square_height[i] >7){
 			cout << "Invalid input. Square not on board.\n";
 			valid_input = 0;
 		}

 		if(valid_input == 1){
 			x[i] = g->get_board()->get_square(square_length[i], square_height[i]);
 		}

 	}

 
 	if(arr[0] == "Move"){
 		if(valid_input == 1){
 			move_success = g->move(x[0], x[1]);
 		}
 	}
 	return move_success;
}


int main() {

	game* g = new game();

	string s;
	piece_color c;
	c = Black;
	bool checkmate = 0;
	bool turn_success = 0;
	char col, row;

	while(checkmate == 0){
		cout << "\n";
		for(int j = 7; j > -1; j--){
			row = '1' + j;
			cout << row << " " << "|";

			for(int i = 0; i < 8; i++){
				if(g->get_board()->get_square(i,j)->get_occupied() == 1){
					if(g->get_board()->get_square(i,j)->get_piece_occupying()->get_color() == White){
						cout << "W:";
					}
					else{
						cout << "B:";
					}
					switch(g->get_board()->get_square(i,j)->get_piece_occupying()->get_type()){
						case Pawn: {
							cout << "P ";
							break;

						}
						case Bishop: { 
							cout << "B ";
							break;

						}
						case Knight: {
							cout << "H ";
							break;

						}
						case Rook: {
							cout << "R ";
							break;

						}
						case Queen: {
							cout << "Q ";
							break;

						}
						case King: {
							cout << "K ";
							break;

						}
					}
				}
				else{
					cout << " -- ";
				}

			}

			cout << "|\n\n";
		}

		cout << "  ";

		for(int i = 0; i < 8; i++){
			col = 'A' + i;
			cout << "  " << col << " ";
		}
		cout << "\n\n";

		getline(cin, s);
		turn_success = turn(s, g);

		cout << "Move successful: " << turn_success << "\n";

		try{
			cout << "B6 Type: " << g->get_board()->get_square(1,5)->get_piece_occupying()->get_type();
		}
		catch(string e){
			cout << "An exception occured: " << e << "\n";
		}

		//checkmate = g->checkmate_check(c);

	}
	
 	cout << "White victorious\n";
 	
 	return 0;

}