#include "Game.hpp"
class Level;
GameObject* player = nullptr;
SDL_Renderer* Game::renderer = nullptr;
Map *gameMap = nullptr;
int addSpeed = 0;

Level newlevel1("newLevel1.txt",50,30,2,2);
Level newlevel2("newLevel2.txt",50,30,2,2);
Level level1("Level1.txt",50,30,2,2);
Level level2("Level2.txt",100,30,2,2);
std::vector<Level> levels;
Game::Game(){
    isRunning = false;
    start_time = SDL_GetTicks()/10;
    level = 1;
}
Game::~Game(){}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    levels.push_back(newlevel1);
    levels.push_back(newlevel2);
    levels.push_back(level1);
    levels.push_back(level2);
    int flags = 0;
    if(fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout <<"Game initialized\n";
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            std::cout << "window created\n";
        }
        Game::renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
                SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 0);
            std::cout << "renderer created\n";
        }
        isRunning = true;
    } else{
        isRunning = false;
    }
    getHighscore();
    player = new GameObject("box.png", 10*32, height-6*32);
    gameMap = new Map(levels[level-1]);
    player->adjustToLevel(levels[level-1].height, levels[level-1].startX, levels[level-1].startY);
}

bool Game::menu(){
    isRunning = true;
    const char* msg = "Select Level by pressing '1', '2','3' etc.";
    bool play = false;
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("Sans.ttf", 24);
    if(font == NULL)
        std::cout << "Font could not be created";
    SDL_Color textColor = {0, 0, 0};
    SDL_Surface* tempSurface = TTF_RenderText_Solid(font, msg, textColor);
    if(tempSurface == NULL)
        std::cout << "Surface could not be created\n";
    SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if(tempTexture == NULL)
        std::cout << "texture could not be created";
    SDL_Rect msgRect;
    msgRect.x = 100;
    msgRect.y = 100;
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
            std::cout << "QUIT";
            loop = false;
            break;
        }
        if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
            case SDLK_1:
               // cout << "Load level 1:\t";
               level = 1;
                delete gameMap;
                gameMap = new Map(levels[level-1]);
                break;
            case SDLK_2:
               // cout << "Load level 2";
               level = 2;
                delete gameMap;
                gameMap = new Map(levels[level-1]);
                break;
            case SDLK_3:
               // cout << "Load level 2";
               level = 3;
                delete gameMap;
                gameMap = new Map(levels[level-1]);
                break;
            case SDLK_4:
               // cout << "Load level 2";
               level = 4;
                delete gameMap;
                gameMap = new Map(levels[level-1]);
                break;
            case SDLK_SPACE:
            case SDLK_a:
            case SDLK_d:
            case SDLK_RIGHT:
            case SDLK_LEFT:
            case SDLK_RETURN:
                    loop = false;
                    play = true;
                    start_time = SDL_GetTicks()/10;
                break;
            case SDLK_ESCAPE:
                std::cout << "Quit";
                play = false;
                loop =false;
                break;
            }
        }
        levelW = gameMap->level.width*32;
        levelH = gameMap->level.height*32;
        player->adjustToLevel(gameMap->level.height, gameMap->level.startX, gameMap->level.startY);
    }
    SDL_FreeSurface(tempSurface);
    SDL_DestroyTexture(tempTexture);
    TTF_CloseFont(font);
    return play;
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch(event.key.keysym.sym){
            case SDLK_RIGHT:
            case SDLK_d:
                //player->setXvel(GameObject::speed);
                addSpeed = GameObject::speed;
                break;
            case SDLK_LEFT:
            case SDLK_a:
               // player->setXvel(-GameObject::speed);
               addSpeed = -GameObject::speed;
                break;
            case SDLK_SPACE:
                player->jump();
                break;
            case SDLK_ESCAPE:
                isRunning = false;

        }
        break;
    case SDL_KEYUP:
        if((event.key.keysym.sym == SDLK_RIGHT ||  event.key.keysym.sym == SDLK_d)&& player->getXvel()>=0){
            player->setXvel(0);
            addSpeed = 0;
        }

        if((event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) && player->getXvel()<=0){
            player->setXvel(0);
            addSpeed = 0;
        }
        break;
    default:
        break;
    }
    player->setXvel(addSpeed);
}
void Game::update(){
//collisions
    int w = player->getW();
    int h = player->getH();
    //check if scrolling map or not
    bool updatex = true, updatey = true;
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
            if(player->destRect.y >= HEIGHT-7*32)
                updatey = true;
            else updatey = false;
        }
        else if(HEIGHT - player->destRect.y >= levelH - player->getyPos()){
            player->destRect.y += (gameMap->yAlign(false));
            if(player->destRect.y <= 7*32){
                updatey = true;
            }
            else updatey = false;
        }
    //hit ground
    if((player->getYvel()>0 && player->getYvel() > player->getyPos() - ((player->getyPos()/32)*32+32-h) && (gameMap->collision(player->getxPos(), player->getyPos()+h, 1)
                               || gameMap->collision(player->getxPos()+w-1, player->getyPos()+h, 1))) || player->destRect.h>HEIGHT){
        int newy = (player->getyPos()/32)*32+32-h;
        int offset = newy - player->getyPos();
        if(updatey)
            gameMap->yAdjust(offset);
        else player->yAdjust(offset);
        player->stopFall();
    }
    //no ground, start fall
    else if(!player->isFalling() && gameMap->collision(player->getxPos()+1, player->getyPos()+h, 0)&& gameMap->collision(player->getxPos()+w-1, player->getyPos()+h, 0))
        player->startFall();
    // jump into something above
    else if(player->getYvel()<0 && (-player->getYvel()>=(((player->getyPos()+31)/32)*32)-player->getyPos())
       && (gameMap->collision(player->getxPos()+1, player->getyPos()-1, 1) || gameMap->collision(player->getxPos()+w-1, player->getyPos()-1, 1))){
        player->setYvel(0);
        int newy = ((player->getyPos()+31)/32)*32;
        int offset = newy-player->getyPos();
        if(updatey)
            gameMap->yAdjust(offset);
        else player->yAdjust(offset);
        player->setPos(player->getxPos(),newy);
    }
    //run into something left
    if(player->getXvel()<0 && (-player->getXvel()>=(player->getxPos()+31)/32)*32-player->getxPos()+1 && (gameMap->collision(player->getxPos()-1, player->getyPos()+1, 1)
            || gameMap->collision(player->getxPos()-1, player->getyPos()+h-1, 1))){
        player->setXvel(0);
        int newx = ((player->getxPos()+31)/32)*32;
        int offset = newx - player->getxPos();
        if(updatex)
            gameMap->xAdjust(offset);
        else player->xAdjust(offset);
        player->setPos(newx,player->getyPos());
    }
    //run into something right
    else if(player->getXvel()>0 && (player->getXvel()>=player->getxPos()-((player->getxPos())/32)*32-32+w) && (gameMap->collision(player->getxPos()+w, player->getyPos()+1, 1)
            || gameMap->collision(player->getxPos()+w, player->getyPos()+h-1, 1))){
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
    //Run into lava block
    if(gameMap->collision(player->getxPos()+w-1, player->getyPos(),2) || gameMap->collision(player->getxPos(), player->getyPos(),2) ||
        gameMap->collision(player->getxPos()+w-1, player->getyPos()+h-1,2) || gameMap->collision(player->getxPos(), player->getyPos()+h-1,2)){
       isRunning = false;
       player->setXvel(0); player->setYvel(0);
       player->stopFall();
       addSpeed = 0;
       delete gameMap;
       gameMap = new Map(levels[level-1]);
    }

    //Run into Finish
    else if(gameMap->collision(player->getxPos()+w, player->getyPos(),3) || gameMap->collision(player->getxPos(), player->getyPos(),3) ||
        gameMap->collision(player->getxPos()+w, player->getyPos()+h,3) || gameMap->collision(player->getxPos(), player->getyPos()+h,3)){
            isRunning = false;
            newHighscore();
            addSpeed = 0;
            player->setXvel(0); player->setYvel(0);
            player->stopFall();
            delete gameMap;
            if(level<levels.size()){
                level++;
            }
            gameMap = new Map(levels[level-1]);
    }
}

void Game::displayTime(){
    TTF_Init();
    time = SDL_GetTicks()/10-start_time;
    const char* msg;
    std::string tempMsg="";
    if(time/100>60)
        tempMsg = std::to_string(time/100/60) + ":";
    tempMsg += std::to_string((time/100)%60) +":"+ std::to_string(time%100);
    msg = tempMsg.c_str();
    TTF_Font* font = TTF_OpenFont("Sans.ttf", 20);
    if(font == NULL)
        std::cout << "Font could not be created";
    SDL_Color textColor = {0, 0, 0};
    SDL_Surface* tempSurface = TTF_RenderText_Solid(font, msg, textColor);
    if(tempSurface == NULL)
        std::cout << "Surface could not be created\n";
    SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if(tempTexture == NULL)
        std::cout << "texture could not be created";
    SDL_Rect msgRect;
    msgRect.x = WIDTH-tempSurface->w;
    msgRect.y = 0;
    msgRect.w = tempSurface->w;
    msgRect.h = tempSurface->h;
    SDL_RenderCopy(Game::renderer, tempTexture, NULL, &msgRect);
    SDL_FreeSurface(tempSurface);
    SDL_DestroyTexture(tempTexture);
    TTF_CloseFont(font);
    delete font;
}
void Game::render(){
    SDL_RenderClear(renderer);
    gameMap->DrawMap();
    player->render();
    displayTime();
    displayHighscore();
    SDL_RenderPresent(renderer);

}
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "game cleaned\n";
}
bool Game::running(){
    return isRunning;
}

void Game::getHighscore(){
    std::fstream file;
    uint32_t number;
    file.open("highscore.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    if(!file){
        file.open("highscore.txt",  std::fstream::in | std::fstream::out | std::fstream::trunc);
        for(int i =0; i<levels.size();i++){
            file << 0 << " " << std::endl;
            best_times.push_back(0);
        }
        file.close();
    }
    else {
        while(file.good()){
            file >> number;
            best_times.push_back(number);
        }
        file.close();
    }
}
void Game::newHighscore(){
    if(this-> best_times[level-1] == 0 || this->time < this->best_times[level-1]){
        this->best_times[level-1] = this->time;
        std::ofstream file;
        file.open("highscore.txt");
        for(auto output : this->best_times){
            file << output << " ";
        }
        file.close();
    }
}

void Game::displayHighscore(){
    const char* msg;
    std::string tempMsg;
    tempMsg = "Best: ";
    if(best_times[level-1]/100>60){
        tempMsg+=  std::to_string(best_times[level-1]/100/60) +":";
        if((best_times[level-1]/100)%60<10)
            tempMsg+="0";
        if((best_times[level-1]/100)%60<10 == 0)
            tempMsg+="0";
    }
    tempMsg += std::to_string((best_times[level-1]/100)%60) + ":";
    if(best_times[level-1]%100<10)
        tempMsg += "0" + std::to_string(best_times[level-1]%100);
    else tempMsg += std::to_string(best_times[level-1]%100);
    if(best_times[level-1] == 0)
        tempMsg = " ";
    msg = tempMsg.c_str();
    TTF_Font* font = TTF_OpenFont("Sans.ttf", 20);
    if(font == NULL)
        std::cout << "Font could not be created";
    SDL_Color textColor = {0, 0, 0};
    SDL_Surface* tempSurface = TTF_RenderText_Solid(font, msg, textColor);
    if(tempSurface == NULL)
        std::cout << "Surface could not be created\n";
    SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if(tempTexture == NULL)
        std::cout << "texture could not be created";
    SDL_Rect msgRect;
    msgRect.x = WIDTH-tempSurface->w;
    msgRect.y = 40;
    msgRect.w = tempSurface->w;
    msgRect.h = tempSurface->h;
    SDL_RenderCopy(Game::renderer, tempTexture, NULL, &msgRect);
    SDL_FreeSurface(tempSurface);
    SDL_DestroyTexture(tempTexture);
    TTF_CloseFont(font);
    delete font;
}
