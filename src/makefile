main: main.o gradientMethod.o
	g++ -o main main.o gradientMethod.o -L../lib -lmuparserx -g -std=c++20 

main.o: main.cpp
	g++ -c main.cpp -I../include -std=c++20

gradientMethod.o: gradientMethod.cpp ../include/gradientMethod.hpp
	g++ -c -I../include gradientMethod.cpp

clean:
	$(RM) *.o