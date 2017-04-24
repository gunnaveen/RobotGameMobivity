CC = g++

test: BoardTester.o Board.o
 	$(CC) BoardTester.o Board.o -o test -g
BoardTester.o: BoardTester.cpp Board.h
 	$(CC) BoardTester.cpp -c -g
Board.o: Board.cpp Board.h
 	$(CC) Board.cpp -c -g
