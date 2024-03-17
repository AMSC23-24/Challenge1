main: main.o gradientMethod.o
	g++ -o main main.o gradientMethod.o -g -std=c++20 

main.o: main.cpp
	g++ -c main.cpp -I../include -std=c++20

gradientMethod.o: gradientMethod.cpp gradientMethod.hpp
	g++ -c gradientMethod.cpp

clean:
	$(RM) *.o