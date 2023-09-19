all:
	g++ main.cpp usefullFunctions.cpp -g -o isometricGame -lsfml-graphics -lsfml-window -lsfml-system
	./isometricGame
