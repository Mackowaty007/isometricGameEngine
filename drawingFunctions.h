//shading type can be set to:
//0-no shading at all
//1-based on orientation
//2-based on distance
//3-based on distance and orientation to the light source (if a side faces the light it should be lit)
//4-based on distance from the camera
#define SHADING_TYPE 1

#define DISABLE_BLOCK_COLORS

//this disables an optimization that doesn't draw the block that are obstructed by others in a straight line to the camera
//#define DISABLE_PERSPECTIVE_OPTIMIZATIONS
//TODO: make this option work
//#define DISABLE_NEXT_TO_OBJ_OPTIMIZATIONS

for(int x = TERRAIN_SIZE;x>=0;x--){
    for(int y = 0;y<TERRAIN_SIZE;y++){
        for(int z = 0;z<TERRAIN_SIZE;z++){
            if(terrain3DMap[x][y][z]!=0){
//COLOR SELECTION
                /*set color based on material
                0-air
                1-grass
                2-wood
                3-concrete
                4-brick
                5-iron
                6-copper
                7-aluminium
                8-plastic
                9-glass
                10-water
                11-lava
                */
                std::vector<int> baseColor;
                baseColor = {255,255,255};
                
                #ifndef DISABLE_BLOCK_COLORS
                    switch(terrain3DMap[x][y][z]){
                        case 1:
                            //grass
                            baseColor = {64, 113, 34};
                            break;
                        case 2:
                            //wood
                            baseColor = {157, 108, 60};
                            break;
                        case 3:
                            //concrete
                            baseColor = {127, 128, 118};
                            break;
                        case 4:
                            //brick
                            baseColor = {133, 79, 70};
                            break;
                        case 5:
                            //iron
                            baseColor = {97, 102, 106};
                            break;
                        case 6:
                            //copper
                            baseColor = {184, 115, 51};
                            break;
                        case 7:
                            //aluminium
                            baseColor = {134, 133, 129};
                            break;
                        case 8:
                            //plastic
                            baseColor = {253, 244, 220};
                            break;
                        case 9:
                            //glass
                            baseColor = {222, 226, 223};
                            break;
                        case 10:
                            //water
                            baseColor = {3, 71, 112};
                            break;
                        case 11:
                            //lava  
                            baseColor = {251, 77, 19};
                            break;
                        default:
                            baseColor = {255, 0, 255};
                    }
                #endif
                
//POSITION
                //cubePos is where the game draws the voxels on the 2D screen
                float additionalDistanceBetweenBlocks = 10.0f;
                float cubePos[2] = {((float)x*(zoomValue+additionalDistanceBetweenBlocks)+(float)y*(zoomValue+additionalDistanceBetweenBlocks))+cameraPos[0]*zoomValue+SCREEN_W/2,((float)y*(zoomValue/2+additionalDistanceBetweenBlocks)-(float)x*(zoomValue/2+1)-(float)z*(zoomValue+additionalDistanceBetweenBlocks))+cameraPos[1]*zoomValue+SCREEN_H/2};
//SHADING          
                //fixed shading
                #if SHADING_TYPE==1
                    voxelRside.setFillColor(sf::Color(baseColor[0],baseColor[1],baseColor[2]));
                    voxelLside.setFillColor(sf::Color(baseColor[0],baseColor[1],baseColor[2]));
                    voxelTop.setFillColor  (sf::Color(baseColor[0],baseColor[1],baseColor[2]));
                #endif
                #if SHADING_TYPE==1
                    voxelRside.setFillColor(sf::Color(baseColor[0]*0.3,baseColor[1]*0.3,baseColor[2]*0.3));
                    voxelLside.setFillColor(sf::Color(baseColor[0]*0.7,baseColor[1]*0.7,baseColor[2]*0.7));
                    voxelTop.setFillColor  (sf::Color(baseColor[0],baseColor[1],baseColor[2]));
                #endif
                //shading based on distance
                #if SHADING_TYPE==2
                    //distanceFromThePlayer is here to make a cool fog effect (from 0 to 1)
                    float distanceFromThePlayer = 1-sqrt(pow(sqrt(pow(lightSourcePos[0]-x,2)+pow(lightSourcePos[1]-y,2)),2) + pow(lightSourcePos[2]-z,2))/(TERRAIN_SIZE);
                    distanceFromThePlayer = fitBetweenMinMax(distanceFromThePlayer,0,1);

                    voxelRside.setFillColor(sf::Color(baseColor[0]*distanceFromThePlayer, baseColor[1]*distanceFromThePlayer, baseColor[2]*distanceFromThePlayer));
                    voxelLside.setFillColor(sf::Color(baseColor[0]*distanceFromThePlayer, baseColor[1]*distanceFromThePlayer, baseColor[2]*distanceFromThePlayer));
                    voxelTop.setFillColor  (sf::Color(baseColor[0]*distanceFromThePlayer, baseColor[1]*distanceFromThePlayer, baseColor[2]*distanceFromThePlayer));
                #endif
                //shading based on distance and orientation to the light source
                #if SHADING_TYPE==3
                    //distanceFromThePlayer is here to make a cool fog effect (from 0 to 1)
                    float distanceFromThePlayer = 1-sqrt(pow(sqrt(pow(lightSourcePos[0]-x,2)+pow(lightSourcePos[1]-y,2)),2) + pow(lightSourcePos[2]-z,2))/(TERRAIN_SIZE);
                    distanceFromThePlayer = fitBetweenMinMax(distanceFromThePlayer,0,1);

                    float isLitUpMultiplyer[3];

                    if (x>lightSourcePos[0]){
                        isLitUpMultiplyer[0] = 1;
                    }
                    else isLitUpMultiplyer[0] = 0.3;

                    if (y<lightSourcePos[1]){
                        isLitUpMultiplyer[1] = 1;
                    }
                    else isLitUpMultiplyer[1] = 0.3;

                    if (z<lightSourcePos[2]){
                        isLitUpMultiplyer[2] = 1;
                    }
                    else isLitUpMultiplyer[2] = 0.3;

                    voxelRside.setFillColor(sf::Color(baseColor[0]*distanceFromThePlayer*isLitUpMultiplyer[1], baseColor[1]*distanceFromThePlayer*isLitUpMultiplyer[1], baseColor[2]*distanceFromThePlayer*isLitUpMultiplyer[1]));
                    voxelLside.setFillColor(sf::Color(baseColor[0]*distanceFromThePlayer*isLitUpMultiplyer[0], baseColor[1]*distanceFromThePlayer*isLitUpMultiplyer[0], baseColor[2]*distanceFromThePlayer*isLitUpMultiplyer[0]));
                    voxelTop.setFillColor  (sf::Color(baseColor[0]*distanceFromThePlayer*isLitUpMultiplyer[2], baseColor[1]*distanceFromThePlayer*isLitUpMultiplyer[2], baseColor[2]*distanceFromThePlayer*isLitUpMultiplyer[2]));
                #endif
                
//DRAWING AND OPTIMIZATIONS
                //check if the right side of the voxel is obstructed, if no then draw it
                //1. checks if there is a block to the right
                //2. checks if that block is next to the chunk boundry
                if(terrain3DMap[x][y+1][z] == 0 || y == TERRAIN_SIZE-1){
                    //check if there is a voxel obscuring on a diagonal line to the camera

                    bool drawOrNot = true;

                    #ifndef DISABLE_PERSPECTIVE_OPTIMIZATIONS
                    for (int i=1; i<TERRAIN_SIZE;i++){
                        if(x-i >= TERRAIN_SIZE || x-i < 0 || y+i >= TERRAIN_SIZE || y+i < 0 || z+i >= TERRAIN_SIZE || z+i < 0){
                            break;
                        }
                        if(terrain3DMap[x-i][y+i][z+i] != 0){
                            drawOrNot = false;
                            break;
                        }
                    }
                    #endif

                    if (drawOrNot==true){
                        //draw the right side of a voxel
                        voxelRside.setPoint(0, sf::Vector2f(cubePos[0], cubePos[1]));
                        voxelRside.setPoint(1, sf::Vector2f(cubePos[0]+zoomValue, cubePos[1]-0.5*zoomValue));
                        voxelRside.setPoint(2, sf::Vector2f(cubePos[0]+zoomValue, cubePos[1]+0.5*zoomValue));
                        voxelRside.setPoint(3, sf::Vector2f(cubePos[0], cubePos[1]+zoomValue));
                        app.draw(voxelRside);
                    }
                }

                //check if the left side of the voxel is obstructed, if no then draw it
                //1. checks if there is a block to the left
                //2. checks if that block is next to the chunk boundry
                if(terrain3DMap[x-1][y][z] == 0 || x == 0){
                    //check if there is a voxel obscuring on a diagonal line to the camera

                    bool drawOrNot = true;

                    #ifndef DISABLE_PERSPECTIVE_OPTIMIZATIONS
                    for (int i=1; i<TERRAIN_SIZE;i++){
                        if(x-i >= TERRAIN_SIZE || x-i < 0 || y+i >= TERRAIN_SIZE || y+i < 0 || z+i >= TERRAIN_SIZE || z+i < 0){
                            break;
                        }
                        if(terrain3DMap[x-i][y+i][z+i] != 0){
                            drawOrNot = false;
                            break;
                        }
                    }
                    #endif

                    if (drawOrNot==true){
                        //draw the left side of a voxel
                            voxelLside.setPoint(0, sf::Vector2f(cubePos[0], cubePos[1]));
                            voxelLside.setPoint(1, sf::Vector2f(cubePos[0], cubePos[1]+zoomValue));
                            voxelLside.setPoint(2, sf::Vector2f(cubePos[0]-zoomValue, cubePos[1]+0.5*zoomValue));
                            voxelLside.setPoint(3, sf::Vector2f(cubePos[0]-zoomValue, cubePos[1]-0.5*zoomValue));
                            app.draw(voxelLside);
                    }
                }

                //check if the top side of the voxel is obstructed, if no then draw it
                //1. checks if there is a block to the top
                //2. checks if that block is next to the chunk boundry
                if(terrain3DMap[x][y][z+1] == 0 || z == TERRAIN_SIZE-1){
                    //check if there is a voxel obscuring on a diagonal line to the camera

                    bool drawOrNot = true;

                    #ifndef DISABLE_PERSPECTIVE_OPTIMIZATIONS
                    for (int i=1; i<TERRAIN_SIZE;i++){
                        if(x-i >= TERRAIN_SIZE || x-i < 0 || y+i >= TERRAIN_SIZE || y+i < 0 || z+i >= TERRAIN_SIZE || z+i < 0){
                            break;
                        }
                        if(terrain3DMap[x-i][y+i][z+i] != 0){
                            drawOrNot = false;
                            break;
                        }
                    }
                    #endif

                    if (drawOrNot==true){
                        //draw the top of a voxel
                            voxelTop.setPoint(0, sf::Vector2f(cubePos[0], cubePos[1]));
                            voxelTop.setPoint(1, sf::Vector2f(cubePos[0]-zoomValue, cubePos[1]-0.5*zoomValue));
                            voxelTop.setPoint(2, sf::Vector2f(cubePos[0], cubePos[1]-zoomValue));
                            voxelTop.setPoint(3, sf::Vector2f(cubePos[0]+zoomValue, cubePos[1]-0.5*zoomValue));
                            app.draw(voxelTop);
                    }
                }
            }
        }
    }
}
