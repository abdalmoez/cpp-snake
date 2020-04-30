all:main.cpp
	g++ -c main.cpp
	g++ main.o -o snake-game -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -f *.o snake-game
install:
	sudo apt-get install libsfml-dev
