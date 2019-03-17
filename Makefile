
all: solverQueens solverGraph

solverQueens: main.o
	g++ -o solverQueens main.o

solverGraph: mainGraph.o
	g++ -o solverGraph mainGraph.o

mainGraph.o : mainGraph.cpp
	g++ -Wall -c mainGraph.cpp

main.o : main.cpp
	g++ -Wall -c main.cpp

clean:
	rm -rf *.o solverQueens
	rm -rf *.o solverGraph
