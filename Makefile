output: main.o Path.o
	g++ main.o Path.o

main.o: main.cpp
	g++ -c main.cpp

Path.o: Path.cpp
	g++ -c Path.cpp
	
clean:
	rm *.o output