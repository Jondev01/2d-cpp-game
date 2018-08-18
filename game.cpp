#include "Game.hpp"


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
    case SDL_KEYDOWN:
       // cout << "A key was pressed " << SDL_GetKeyName(event.key.keysym.sym)<<endl;
        switch(event.key.keysym.sym){
            case SDLK_RIGHT:
            case SDLK_d:
                player->setXvel(GameObject::speed);
                break;
            case SDLK_LEFT:
            case SDLK_a:
                player->setXvel(-GameObject::speed);
                break;
            case SDLK_SPACE:
                player->jump();
        }
        break;
    case SDL_KEYUP:
        //cout << "A key was released " << SDL_GetKeyName(event.key.keysym.sym)<<endl;
        if((event.key.keysym.sym == SDLK_RIGHT ||  event.key.keysym.sym == SDLK_d)&& player->getXvel()>0)
            player->setXvel(0);
        else if((event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) && player->getXvel()<0)
            player->setXvel(0);
        break;
    default:
        break;
    }
}
void Game::update(){
    //collisions
    //hit ground
    if(player->getYvel()>0 && (gameMap->collision(player->getxPos()+2, player->getyPos()+32, 1) || gameMap->collision(player->getxPos()+30, player->getyPos()+32, 1)))
        player->stopFall();
    //no ground, start fall
    if(!player->isFalling() && gameMap->collision(player->getxPos()+3, player->getyPos()+32, 0)&& gameMap->collision(player->getxPos()+29, player->getyPos()+32, 0))
        player->startFall();
    // jump into something above
    if(player->getYvel()<0 && (-player->getYvel()>=(((player->getyPos()+32)/32)*32)-player->getyPos()) && (gameMap->collision(player->getxPos(), player->getyPos(), 1) || gameMap->collision(player->getxPos()+32, player->getyPos(), 1))){
    player->setYvel(0);
    player->setPos(player->getxPos(),(((player->getyPos()+32)/32)*32));
    }
    //run into something left
    else if(player->getXvel()<0 && (gameMap->collision(player->getxPos(), player->getyPos(), 1)|| gameMap->collision(player->getxPos(), player->getyPos()+31, 1))){
    player->setXvel(0);
    player->setPos(((player->getxPos()+32)/32)*32,player->getyPos());
    }
    //run into something right
    else if(player->getXvel()>0 && (gameMap->collision(player->getxPos()+32, player->getyPos(), 1) || gameMap->collision(player->getxPos()+32, player->getyPos()+31, 1))){
    player->setXvel(0);
    player->setPos(((player->getxPos())/32)*32,player->getyPos());
    }
    player->update();
   /* if(gameMap->collision(player->getxPos(), player->getyPos(), 1))
        cout << "Grass detected!\t";*/
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
