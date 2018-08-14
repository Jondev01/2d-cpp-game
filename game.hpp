#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include <iostream>
#include <string>
#include "SDL2/SDL_image.h"
using namespace std;

class Game {
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running();

        static SDL_Renderer *renderer;
    private:
        bool isRunning;
        SDL_Window *window;
};
#endif /* Game_hpp */
