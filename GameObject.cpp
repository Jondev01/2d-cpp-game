#include "gameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y){
    xpos = x;
    ypos = y;
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
    xpos++;
    ypos++;
    destRect.x = xpos;
    destRect.y = ypos;
}

void GameObject::render(){
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
