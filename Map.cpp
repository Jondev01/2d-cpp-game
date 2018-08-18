#include "game.hpp"
#include "map.h"
#include "TextureManager.h"
#include <fstream>
int lvl1[25][25] ={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};
Map::Map(){
    sky = TextureManager::LoadTexture("sky.png");
    grass = TextureManager::LoadTexture("grass.png");
    spike = TextureManager::LoadTexture("spike.png");
    LoadMap(lvl1);
    src.x=src.y=0;
    src.w=dest.w=32;
    src.h=dest.h=32;
    dest.x=dest.y=0;
}
Map::~Map(){
    SDL_DestroyTexture(sky);
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(spike);
}

void Map::LoadMap(int arr[25][25]){
    for(int i=0; i<25; i++){
        for(int j=0; j<25; j++)
            theMap[i][j] = arr[i][j];
    }
    fstream readFile;
    char type;
    readFile.open("test.txt");
    for(int j = 0; j<30;j++){
            cout << j <<"\t";
        for(int i=0; i<50;i++){
            readFile.get(type);
            //cout << type;
            testMap[j*50+i]=(int)type-'0';
            cout << testMap[j*50+i];
            readFile.ignore();
        }
        readFile.ignore();
        cout<<endl;
    }
    readFile.close();
    for(int j = 0; j<30;j++){
            cout << j<<"\t";
        for(int i=0; i<50;i++){
            cout << testMap[j*50+i];
        }
        cout << endl;
    }
}

void Map:: DrawMap(){
    int type = 0;
    for(int i=0; i<20; i++){
        for(int j=0; j<25; j++){
            type = theMap[i][j];
            //type = testMap[(i+10)*50+j];
            dest.x = j*32;
            dest.y = i*32;
            switch(type){
            case 0:
                TextureManager::Draw(sky, src, dest);
                break;
            case 1:
                TextureManager::Draw(grass, src, dest);
                break;
            case 2:
                TextureManager::Draw(spike, src, dest);
                break;
            }
        }
    }
}

bool Map::collision(int xpos, int ypos, int type){
    //cout << "(" << xpos/32 << "," << ypos/32 << ")\t;\n";
    if(xpos <0 || xpos/32 >=25 || ypos<0 || ypos/32>= 25)
        return false;
   // cout << theMap[ypos/32][xpos/32] << endl;
    if(theMap[ypos/32][xpos/32] == type){
     //       cout << "TRUE\n";
        return true;
    }
    return false;
}
