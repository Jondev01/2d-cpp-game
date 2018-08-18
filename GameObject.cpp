#include "map.h"
#include "gameObject.h"
#include "TextureManager.h"



GameObject::GameObject(const char* textureSheet, int x, int y){
    fall = false;
    fallTime = 0;
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
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
    objTexture = TextureManager::LoadTexture(textureSheet);
}

void GameObject::update(){
    if(fall){
        fallTime++;
        yvel += gravity;
    }
    xpos += xvel;
    ypos += (int)yvel;
    if(xpos<0)
        xpos = 0;
    if(ypos<0)
        ypos = 0;
        //collisions
    /*if(yvel>0 && (gameMap->collision(xpos, ypos+32, 1) || gameMap->collision(xpos+32, ypos+32, 1)))
        this->stopFall();
    if(!fall && gameMap->collision(xpos, ypos+32, 0)&& gameMap->collision((xpos)+32, ypos+32, 0))
        this->startFall();
    if(yvel<0 && gameMap->collision(xpos, ypos, 1)){
        yvel = 0;
        ypos = ((ypos+32)/32)*32;
    }
    else if(xvel<0 && gameMap->collision(xpos, ypos, 1)){
        xvel = 0;
        xpos = ((xpos+32)/32)*32;
    }
    else if(xvel>0 && gameMap->collision(xpos+32, ypos, 1)){
        xvel = 0;
        xpos =((xpos)/32)*32;
    }*/


    destRect.x = xpos;
    destRect.y = ypos;
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
    if(yvel < ypos - (ypos/32)*32)
        return;
    fall = false;
    fallTime=0;
    yvel = 0;
    ypos = (ypos/32)*32;
}

