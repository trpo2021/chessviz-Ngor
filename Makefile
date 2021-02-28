output: main.o
	g++ LAB1trpo.o -o output

main.o: LAB1trpo.cpp
	g++ -Wall -Werror -c LAB1trpo.cpp
