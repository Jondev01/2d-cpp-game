#include "map.h"
#include "gameObject.h"
#include "TextureManager.h"



GameObject::GameObject(const char* textureSheet, int x, int y){
    fall = false;
    xpos = x;
    ypos = y;
    xvel=0;
    yvel=0;
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 24;
    destRect.h = 24;
    objTexture = TextureManager::LoadTexture(textureSheet);
}

void GameObject::update(bool updatex, bool updatey){
    if(fall){
        yvel += gravity;
    }
    xpos += xvel;
    ypos += (int)yvel;

    if(!updatex)
        destRect.x += xvel;
    if(!updatey){
       destRect.y += (int)yvel;
    }
}

void GameObject::render(){
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

int GameObject::getXvel(){
    return xvel;
}

void GameObject::setXvel(int x){
    xvel = x;
}

void GameObject::setYvel(int y){
    yvel = y;
}

void GameObject::stopFall(){
    fall = false;
    yvel = 0;
    ypos = ((ypos)/32)*32+32-this->destRect.h;
}

void GameObject::adjustToLevel(int h, int startX, int startY){
    xpos = startX*32;
    ypos = (h-startY)*32+32-destRect.h;
    destRect.x = xpos;
    destRect.y = HEIGHT-(startY)*32+32-destRect.h;
}

void GameObject::yAdjust(int offset){
            destRect.y += offset;
}

void GameObject::xAdjust(int offset){
        destRect.x += offset;
}

void GameObject::yAlign(bool up){
    if(up)
            destRect.y  = (destRect.y)/32*32;
    else
            destRect.y  = (destRect.y+32)/32*32;

}

void GameObject::xAlign(bool left){
    if(left)
            destRect.x  = (destRect.x)/32*32;
    else
            destRect.x  = (destRect.x+32)/32*32;
}

