all:
	g++ main.c usefullFunctions.c -g -o isometricGame -lsfml-graphics -lsfml-window -lsfml-system
	./isometricGame
