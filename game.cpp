#include "Game.hpp"
#include "TextureManager.h"
#include "gameObject.h"
#include "map.h"

GameObject* player;
SDL_Renderer* Game::renderer=NULL;
Map *gameMap;

Game::Game(){
    isRunning = false;
}
Game::~Game(){}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout <<"Game initialized\n";
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            cout << "window created\n";
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            cout << "renderer created\n";
        }
        isRunning = true;
    } else{
        isRunning = false;
    }
    player = new GameObject("box.png", 100, 100);
    gameMap = new Map();

}
void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_MOUSEMOTION:
        cout << "mouse moved!\n";
        break;
    case SDL_KEYDOWN:
        cout << "A key was pressed " << SDL_GetKeyName(event.key.keysym.sym)<<endl;
        if(event.key.keysym.sym == SDLK_RIGHT)
            player->setXvel(2);
        else if(event.key.keysym.sym == SDLK_LEFT)
            player->setXvel(-2);
        break;
    case SDL_KEYUP:
        cout << "A key was released " << SDL_GetKeyName(event.key.keysym.sym)<<endl;
        if(event.key.keysym.sym == SDLK_RIGHT && player->getXvel()>0)
            player->setXvel(0);
        else if(event.key.keysym.sym == SDLK_LEFT && player->getXvel()<0)
            player->setXvel(0);
        break;
    default:
        break;
    }
}
void Game::update(){
    player->update();
}
void Game::render(){
    SDL_RenderClear(renderer);
    gameMap->DrawMap();
    player->render();
    SDL_RenderPresent(renderer);

}
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "game cleaned\n";
}
bool Game::running(){
    return isRunning;
}
