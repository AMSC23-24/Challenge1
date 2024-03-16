main: main.o gradientMethod.o
	g++ -o main main.o gradientMethod.o -std=c++20

main.o: main.cpp
	g++ -c main.cpp -std=c++20

gradientMethod.o: gradientMethod.cpp gradientMethod.hpp
	g++ -c gradientMethod.cpp