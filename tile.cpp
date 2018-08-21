#include "tile.h"
#include "TextureManager.h"
//SDL_Texture* skysky = TextureManager::LoadTexture("sky.png");
//SDL_Texture* grassgrass = TextureManager::LoadTexture("grass.png");

Tile::Tile(int row, int column, int x, int y, int type){
    this->destRect.x = x;
    this->destRect.y = y;
    this->row = row;
    this->column = column;
    this->x = x;
    this->y = y;
    this-> type = type;
    if(type == 0)
        this->fileName = "sky.png";
    else if(type == 1)
        this->fileName = "grass.png";
    else this->fileName="sky.png";

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w=32;
    srcRect.h=32;
   // this->destRect.x = x;
    //this->destRect.y = y;
    destRect.w = 32;
    destRect.h = 32;
}

void Tile::draw(SDL_Texture* sky, SDL_Texture* grass, SDL_Texture* lava, SDL_Texture* finish){
    if(!( (destRect.x+32>=0 && abs(destRect.x)<=WIDTH) && (destRect.y+32>=0 && abs(destRect.y)<=HEIGHT)))
        return;
   //  cout << destRect.x << " " << destRect.y << endl;
    // cout << srcRect.x << " " << srcRect.y << endl;
    if(type == 0)
        TextureManager::Draw(sky, this-> srcRect, this->destRect);
    else if(type ==1)
        TextureManager::Draw(grass, this-> srcRect, this->destRect);
    else if(type ==2)
        TextureManager::Draw(lava, this-> srcRect, this->destRect);
    else if(type ==3)
        TextureManager::Draw(finish, this-> srcRect, this->destRect);
    else
        TextureManager::Draw(sky, this-> srcRect, this->destRect);
}
