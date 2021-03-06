#include "game.hpp"
Game *game;

int main(int argc, char* argv[]){
    bool play = true;
    const int FPS = 60;
    const int frameDelay = 1000/ FPS;
    int frameStart=0;
    int frameTime, temp;

    game = new Game();
    game->init("simpleGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

    while(play){
         play = game->menu();
         while(game->running() && play){
            temp = frameStart;
            frameStart = SDL_GetTicks() - temp;
            game->handleEvents();
            game->update();
            game->render();

            frameTime = SDL_GetTicks() - temp - frameStart;
            if(frameDelay>frameTime){
                SDL_Delay(frameDelay-frameTime);
            }
        }
    }
    game->clean();
    delete game;
}
