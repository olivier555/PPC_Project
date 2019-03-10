solverGraph: mainGraph.o
	g++ -o solverGraph mainGraph.o

constraint_solver: main.o
	g++ -o constraint_solver main.o

mainGraph.o : mainGraph.cpp
	g++ -Wall -c mainGraph.cpp

main.o : main.cpp
	g++ -Wall -c main.cpp

clean:
	rm -rf *.o constraint_solver
	rm -rf *.o solverGraph
