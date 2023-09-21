#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "usefullFunctions.h"

#define SCREEN_W 1000
#define SCREEN_H 1000
#define TERRAIN_SIZE 32

#define ZOOM_SPEED 0.02f
#define CAMERA_SPEED 20.0f

float zoomValue = 20;
float cameraPos[2] = {0,0};
float lightSourcePos[3] = {TERRAIN_SIZE/2,TERRAIN_SIZE/2,TERRAIN_SIZE/2};

unsigned short terrain3DMap[TERRAIN_SIZE][TERRAIN_SIZE][TERRAIN_SIZE];

#include "terrainGenerator.h"

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(SCREEN_W, SCREEN_H), "isometric game");

    sf::Clock clock;
    float lastTime = 0;

    sf::Font font;
    if (!font.loadFromFile("Seven Segment.ttf"))
    {
        // error...
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    #include "initDrawingFunctions.h"

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
            cameraPos[0] += CAMERA_SPEED/zoomValue;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            cameraPos[0] -= CAMERA_SPEED/zoomValue;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            cameraPos[1] += CAMERA_SPEED/zoomValue;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            cameraPos[1] -= CAMERA_SPEED/zoomValue;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            if(zoomValue < 400)
            zoomValue += ZOOM_SPEED*zoomValue;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
            if(zoomValue > 2)
            zoomValue -= ZOOM_SPEED*zoomValue;
        }

        //render
        app.clear();

        #include "drawingFunctions.h"

        float currentTime = clock.restart().asSeconds();
        int fps = 1.f / currentTime;
        lastTime = currentTime;

        text.setString(std::to_string(fps));
        app.draw(text);

        app.display();
    }
    return EXIT_SUCCESS;
}