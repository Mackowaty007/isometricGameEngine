//0-every block is grass
//1-either grass or air 50-50
//2-random, but more block at the bottom and less at the top

#define TYPE_OF_TERRAIN_GENERATION 1

#if TYPE_OF_TERRAIN_GENERATION == 0
void generatreTerrain(){
    for(int x = 0;x<TERRAIN_SIZE;x++){
        for(int y = 0;y<TERRAIN_SIZE;y++){
            for(int z = 0;z<TERRAIN_SIZE;z++){
                terrain3DMap[x][y][z] = 1;
            }
        }
    }
}
#endif

#if TYPE_OF_TERRAIN_GENERATION == 1
void generatreTerrain(){
    for(int x = 0;x<TERRAIN_SIZE;x++){
        for(int y = 0;y<TERRAIN_SIZE;y++){
            for(int z = 0;z<TERRAIN_SIZE;z++){
                terrain3DMap[x][y][z] = rand() % 2;
            }
        }
    }
}
#endif

#if TYPE_OF_TERRAIN_GENERATION == 2
void generatreTerrain(){
    for(int x = 0;x<TERRAIN_SIZE;x++){
        for(int y = 0;y<TERRAIN_SIZE;y++){
            for(int z = 0;z<TERRAIN_SIZE;z++){
                if(rand()%(z+1)-1 < 1){
                    terrain3DMap[x][y][z] = rand() % 12;
                }
                else{
                    terrain3DMap[x][y][z] = 0;
                }
            }
        }
    }
}
#endif

#if TYPE_OF_TERRAIN_GENERATION == 3

#endif

#if TYPE_OF_TERRAIN_GENERATION == 4

#endif
