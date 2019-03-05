constraint_solver: main.o
	g++ -o constraint_solver main.o

main.o : main.cpp
	g++ -Wall -c main.cpp

clean:
	rm -rf *.o constraint_solver
