#include "game.hpp"
#include "map.h"
#include "TextureManager.h"
#include <fstream>
#include <math.h>

Map::Map(Level& curLevel):level(curLevel){
    sky = TextureManager::LoadTexture("sky.png");
    grass = TextureManager::LoadTexture("grass.png");
    lava = TextureManager::LoadTexture("lava.png");
    finish = TextureManager::LoadTexture("finish.png");
    LoadMap();
    src.x=src.y=0;
    src.w=dest.w=32;
    src.h=dest.h=32;
    dest.x=dest.y=0;
}
Map::~Map(){
    SDL_DestroyTexture(sky);
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(lava);
}

void Map::LoadMap(){
    theMap.resize(level.width*level.height,0);
    std::fstream readFile;
    char type;
    readFile.open(level.fileName);
    for(int j = 0; j<level.height;j++){
           // cout << j <<"\t";
        for(int i=0; i<level.width;i++){
            readFile.get(type);
            //cout << type;
            theMap[j*level.width+i]=(int)type-'0';
            addTile(j,i, i*32, (j-(level.height))*32+HEIGHT,(int)type-'0');
            readFile.ignore();
        }
        readFile.ignore();
       // cout<<endl;
    }
    readFile.close();
   /* for(int j = 0; j<level.height;j++){
            cout << j<<"\t";
        for(int i=0; i<level.width;i++){
            cout << theMap[j*level.width+i];
        }
        cout << endl;
    }*/
}

void Map:: DrawMap(){
    //cout << tiles.size();
    for(int i=0;i<tiles.size();i++){
        tiles[i].draw(sky, grass, lava, finish);
    }
}

bool Map::collision(int xpos, int ypos, int type){
    if(theMap[(ypos/32)*level.width+xpos/32] == type)
        return true;
    return false;
}

void Map::addTile(int row, int column, int x, int y, int type){
    this->tiles.push_back(Tile(row, column, x, y, type));
}

void Map::update(int xvel, int yvel, bool updatex, bool updatey){

    for(auto &t : tiles){
        if(updatex)
            t.destRect.x -= xvel;
        if(updatey)
            t.destRect.y -= yvel;
    }
}

void Map::yAdjust(int offset){
    for(int i=0;i<tiles.size();i++){
        tiles[i].destRect.y -= offset;
    }
}

int Map::yAlign(bool up){
    int offset=0;
    if(up){
        if(tiles[0].destRect.y>-32)
            offset = tiles[0].destRect.y  - tiles[0].destRect.y/32*32;
        else
            offset = tiles[0].destRect.y-((tiles[0].destRect.y)/32)*32+32;
            for(int i=0;i<tiles.size();i++){
                tiles[i].destRect.y  = tiles[i].destRect.y/32*32;
            }
        return fabs(offset);
    }
    else{
        if(tiles[0].destRect.y> -32)
            offset = tiles[0].destRect.y-((tiles[0].destRect.y+31)/32)*32;
        else
            offset = tiles[0].destRect.y-((tiles[0].destRect.y+31)/32)*32+32;
        for(int i=0;i<tiles.size();i++){
            if(tiles[i].destRect.y>-32)
                tiles[i].destRect.y  = ((tiles[i].destRect.y+31)/32)*32;
            else tiles[i].destRect.y  = ((tiles[i].destRect.y+31)/32)*32-32;
        }
        return fabs(offset);
    }
}

void Map::xAdjust(int offset){
    for(int i=0;i<tiles.size();i++){
        tiles[i].destRect.x -= offset;
    }
}

int Map::xAlign(bool left){
    int offset=0;
    if(left){
        if(tiles[0].destRect.x>-32)
            offset = tiles[0].destRect.x  - tiles[0].destRect.x/32*32;
        else
            offset = tiles[0].destRect.x-((tiles[0].destRect.x)/32)*32+32;
        for(int i=0;i<tiles.size();i++){
            tiles[i].destRect.x  = tiles[i].destRect.x/32*32;
        }
    }
    else {
        if(tiles[0].destRect.x> -32)
            offset = tiles[0].destRect.x-((tiles[0].destRect.x+31)/32)*32;
        else
            offset = tiles[0].destRect.x-((tiles[0].destRect.x+31)/32)*32+32;
        for(int i=0;i<tiles.size();i++){
            if(tiles[i].destRect.x>-32)
                tiles[i].destRect.x  = ((tiles[i].destRect.x+31)/32)*32;
            else tiles[i].destRect.x  = ((tiles[i].destRect.x+31)/32)*32-32;
        }
    }
    return fabs(offset);
}
