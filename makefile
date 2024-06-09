all:
	clear
	flex scanner.lex
	g++ -std=c++17 lex.yy.c hw1.cpp -o hw1.out
	
	./hw1.out < t1.in >& T1.out
	diff T1.out t1.out
	
	./hw1.out < t2.in >& T2.out
	diff T2.out t2.out

	cp hw1.out ./GT/hw1_tests
	chmod +x ./GT/hw1_tests/run_tests.sh
	
	