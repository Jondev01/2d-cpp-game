#ifndef Game_hpp
#define Game_hpp
#include "SDL2/SDL.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include "SDL2/SDL_image.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include "map.h"
#include "gameObject.h"
const size_t WIDTH = 800;
const size_t HEIGHT = 640;

class Game {
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        bool menu();
        void handleEvents();
        void update();
        void displayTime();
        void render();
        void clean();
        void getHighscore();
        void newHighscore();
        void displayHighscore();
        bool running();
        static SDL_Renderer *renderer;
    private:
        int levelW, levelH, level;
        uint32_t start_time, time;
        std::vector<uint32_t> best_times;
        bool isRunning;
        SDL_Window *window;
};
#endif /* Game_hpp */
