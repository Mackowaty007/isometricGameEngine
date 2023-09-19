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