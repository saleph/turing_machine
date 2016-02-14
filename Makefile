compile:
	g++ -std=c++14 -o tm.out main.cpp src/*.cpp -Iinclude -Wall -w -g -Wextra -Weffc++ -pedantic
run:
	./tm.out
