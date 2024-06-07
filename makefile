all:
	clear
	flex scanner.lex
	g++ -std=c++17 lex.yy.c hw1.cpp -o hw1.out
	./hw1.out < t1.in >& t1.out
	cat t1.out