#include "Game.hpp"

GameObject* player;
SDL_Renderer* Game::renderer=NULL;
Map *gameMap;
Level level1("test.txt",50,30,2,2);
Level level2("level2.txt",100,30,2,2);
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
        Game::renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
                SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 0);
            cout << "renderer created\n";
        }
        isRunning = true;
    } else{
        isRunning = false;
    }
    player = new GameObject("box.png", 10*32, height-6*32);
    gameMap = new Map(level1);
    player->adjustToLevel(level1.height, level1.startX, level1.startY);
}

void Game::menu(){
    const char* msg = "Press '1', '2' or '3' to start Level 1,2, 3 and then the spacebar";
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("Sans.ttf", 14);
    if(font == NULL)
        cout << "Font could not be created";
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* tempSurface = TTF_RenderText_Solid(font, msg, textColor);
    if(tempSurface == NULL)
        cout << "Surface could not be created\n";
    SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if(tempTexture == NULL)
        cout << "texture could not be created";
    SDL_Rect msgRect;
    msgRect.x = 10;
    msgRect.y = 10;
    msgRect.w = tempSurface->w;
    msgRect.h = tempSurface->h;
    bool loop = true;
    while(loop){
        SDL_RenderClear(renderer);
        gameMap->DrawMap();
        player->render();
        SDL_RenderCopy(Game::renderer, tempTexture, NULL, &msgRect);
        SDL_RenderPresent(Game::renderer);
        SDL_Event event;
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT){
            cout << "QUIT";
            loop = false;
            break;
        }
        if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
            case SDLK_1:
                cout << "Load level 1:\t";
                delete gameMap;
                gameMap = new Map(level1);
                player->adjustToLevel(level1.height, level1.startX, level1.startY);
                levelW = level1.width*32;
                levelH = level1.height*32;
                cout << player->getxPos()/32 << ", " << player->getyPos()/32 << "\t" << gameMap->theMap[(player->getyPos()/32+1)*50+player->getxPos()/32]<<endl;
                //loop = false;
                break;
            case SDLK_2:
                cout << "Load level 2";
                delete gameMap;
                gameMap = new Map(level2);
                player->adjustToLevel(level2.height, level2.startX, level2.startY);
                levelW = level2.width*32;
                levelH = level2.height*32;
               // loop = false;
                break;
            case SDLK_SPACE:
                loop = false;
            case SDLK_ESCAPE:
                cout << "Quit";
                loop =false;
                break;
            }
        }
    }
    SDL_FreeSurface(tempSurface);
    SDL_DestroyTexture(tempTexture);
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
    int w = player->getW();
    int h = player->getH();
    //check if scrolling map or not
    bool updatex = true, updatey =true;
        if(player->destRect.x >= player->getxPos()){
            player->destRect.x -=(gameMap->xAlign(true));
            if(player->destRect.x >= WIDTH-7*32)
                updatex = true;
            else updatex = false;
        }
        else if (WIDTH-player->destRect.x >= levelW - player->getxPos()){
               player->destRect.x+=(gameMap->xAlign(false));
               if(player->destRect.x<=7*32)
                    updatex = true;
                else updatex = false;
        }
        if(player->destRect.y >= player->getyPos()){
            player->destRect.y -= gameMap->yAlign(true);
            if(player->destRect.y >= HEIGHT-5*32)
                updatey = true;
            else updatey = false;
        }
        else if(HEIGHT - player->destRect.y >= levelH - player->getyPos()){
            player->destRect.y += (gameMap->yAlign(false));
            if(player->destRect.y <= 10*32){
                updatey = true;
            }
            else updatey = false;
        }


    //hit ground
    if(player->getYvel()>0 && player->getYvel() > player->getyPos() - ((player->getyPos()/32)*32+32-h) && (gameMap->collision(player->getxPos()+2, player->getyPos()+h, 1)
                               || gameMap->collision(player->getxPos()+w-2, player->getyPos()+h, 1))){
        int newy = (player->getyPos()/32)*32+32-h;
        int offset = newy - player->getyPos();
        if(updatey)
            gameMap->yAdjust(offset);
        else player->yAdjust(offset);
        player->stopFall();
    }
    //no ground, start fall
    else if(!player->isFalling() && gameMap->collision(player->getxPos()+3, player->getyPos()+h, 0)&& gameMap->collision(player->getxPos()+w-3, player->getyPos()+h, 0))
        player->startFall();
    // jump into something above
    else if(player->getYvel()<0 && (-player->getYvel()>=(((player->getyPos()+32)/32)*32)-player->getyPos())
       && (gameMap->collision(player->getxPos()+3, player->getyPos(), 1) || gameMap->collision(player->getxPos()+w-3, player->getyPos(), 1))){
        player->setYvel(0);
        int offset = ((player->getyPos()+32)/32)*32-player->getyPos();
        if(updatey)
            gameMap->yAdjust(offset);
        else player->yAdjust(offset);
        player->setPos(player->getxPos(),player->getyPos()+offset);
    }
    //run into something left
    else if(player->getXvel()<0 && (-player->getXvel()>=(player->getxPos()+32)/32)*32-player->getxPos() && (gameMap->collision(player->getxPos(), player->getyPos()+2, 1)|| gameMap->collision(player->getxPos(), player->getyPos()+h-2, 1))){
        player->setXvel(0);
        int newx = ((player->getxPos()+32)/32)*32;
        int offset = newx - player->getxPos();
        if(updatex)
            gameMap->xAdjust(offset);
        else player->xAdjust(offset);
        player->setPos(newx,player->getyPos());
    }
    //run into something right
    else if(player->getXvel()>0 && (player->getXvel()>=player->getxPos()-((player->getxPos()+32)/32)*32-32+w) && (gameMap->collision(player->getxPos()+w, player->getyPos()+2, 1)
            || gameMap->collision(player->getxPos()+2, player->getyPos()+h-2, 1))){
        player->setXvel(0);
        int newx = ((player->getxPos())/32)*32+32-w;
        int offset = newx - player->getxPos();
        if(updatex)
            gameMap->xAdjust(offset);
        else player->xAdjust(offset);
        player->setPos(newx,player->getyPos());
    }
    //update pos and screen
    player->update(updatex, updatey);
    gameMap->update(player->getXvel(), player->getYvel(),updatex, updatey);
    /*if(gameMap->collision(player->getxPos(), player->getyPos(), 1))
        cout << "Grass detected!\t";*/
    if(gameMap->collision(player->getxPos()+w, player->getyPos(),2) || gameMap->collision(player->getxPos(), player->getyPos(),2) ||
        gameMap->collision(player->getxPos()+w, player->getyPos()+h,2) || gameMap->collision(player->getxPos(), player->getyPos()+h,2))
       isRunning = false;
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
