# Makefile with the command to compile the main program
all: main.cpp rational.cpp row.cpp matrix.cpp
	g++ main.cpp rational.cpp row.cpp matrix.cpp console.cpp -o program -Wall -std=c++11

clean: 
	$(RM) program
