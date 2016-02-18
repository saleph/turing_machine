compile:
	g++ -std=c++14 -o tm main.cpp src/*.cpp -Iinclude -Wall -w -O3 -Wextra -Weffc++ -pedantic
run:
	./tm
