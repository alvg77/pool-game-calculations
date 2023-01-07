all: main.o Game.o Line.o Point.o Vector.o Triangle.o Ball.o Table.o
	g++ main.o Game.o Line.o Point.o Vector.o Triangle.o Ball.o Table.o

main.o: main.cpp
	g++ -c main.cpp

Game.o: Game.cpp
	g++ -c Game.cpp

Line.o: utils/Line.cpp
	g++ -c utils/Line.cpp

Point.o: utils/Point.cpp
	g++ -c utils/Point.cpp

Vector.o: utils/Vector.cpp
	g++ -c utils/Vector.cpp

Triangle.o: utils/Triangle.cpp
	g++ -c utils/Triangle.cpp

Ball.o: components/Ball.cpp
	g++ -c components/Ball.cpp

Table.o: components/Table.cpp
	g++ -c components/Table.cpp

clean:
	rm *.o

run:
	./a.out