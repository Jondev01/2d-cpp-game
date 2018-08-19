#ifndef Game_hpp
#define Game_hpp
#include "SDL2/SDL.h"
#include <iostream>
#include <string>
#include <math.h>
#include "SDL2/SDL_image.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include "map.h"
#include "gameObject.h"
const size_t WIDTH = 800;
const size_t HEIGHT = 640;

using namespace std;

class Game {
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void menu();
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running();
        static SDL_Renderer *renderer;
    private:
        int levelW, levelH;
        bool isRunning;
        SDL_Window *window;
};
#endif /* Game_hpp */
