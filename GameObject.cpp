#include "gameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y){
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
    destRect.h = srcRect.h;;
    objTexture = TextureManager::LoadTexture(textureSheet);
}

void GameObject::update(){
    xpos += xvel;
    ypos += yvel;
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
