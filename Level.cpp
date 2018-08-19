#include "Level.h"
#include <fstream>
Level::Level(char* path, int w, int h, int X, int Y){
    this->fileName = path;
    this->width = w;
    this->height = h;
    this->levelMap.resize(w*h,0);
    this->startX = X;
    this->startY = Y;
}

void Level::ReadMap(){
    fstream readFile;
    readFile.open(this->fileName);
    char type;
    for(int j = 0; j<this->height;j++){
        for(int i=0; i<this->width;i++){
            readFile.get(type);
            this->levelMap[j*this->width+i]=(int)type-'0';
            readFile.ignore();
        }
        readFile.ignore();
    }
    readFile.close();
}
