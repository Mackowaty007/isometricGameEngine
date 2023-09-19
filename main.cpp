#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "usefullFunctions.hpp"

#define SCREEN_W 1000
#define SCREEN_H 1000
#define TERRAIN_SIZE 16

#define ZOOM_SPEED 1.0f
#define CAMERA_SPEED 1.0f

float zoomValue = 20;
float cameraPos[2] = {0,0};
float lightSourcePos[3] = {TERRAIN_SIZE/2,TERRAIN_SIZE/2,TERRAIN_SIZE/2};

unsigned short terrain3DMap[TERRAIN_SIZE][TERRAIN_SIZE][TERRAIN_SIZE];

#include "terrainGenerator.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(SCREEN_W, SCREEN_H), "isometric game");

    #include "initDrawingFunctions.hpp"

    generatreTerrain();

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }


        //input
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            cameraPos[0] += CAMERA_SPEED;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            cameraPos[0] -= CAMERA_SPEED;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            cameraPos[1] += CAMERA_SPEED;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            cameraPos[1] -= CAMERA_SPEED;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            if(zoomValue < 150)
            zoomValue += ZOOM_SPEED;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
            if(zoomValue > 2)
            zoomValue -= ZOOM_SPEED;
        }

        //render
        app.clear();

        #include "drawingFunctions.hpp"

        app.display();
    }
    return EXIT_SUCCESS;
}