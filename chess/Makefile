all: main

main: main.o game.o checks.o move_search.o board.o square.o piece.o
	g++ main.o game.o checks.o move_search.o board.o square.o piece.o -o main

main.o: 
	g++ -c main.cpp

game.o:
	g++ -c game/game.cpp

checks.o:
	g++ -c game/checks.cpp

move_search.o:
	g++ -c game/move_search.cpp

board.o:
	g++ -c board.cpp

square.o:
	g++ -c square.cpp

piece.o:
	g++ -c piece.cpp



clean:
	rm -rf *.o
	rm -rf main



