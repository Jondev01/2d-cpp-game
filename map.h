#include "game.hpp"

class Map{
public:
    Map();
    ~Map();

    void LoadMap(int arr[25][25]);
    void DrawMap();

private:
    SDL_Rect src, dest;
    SDL_Texture* sky;
    SDL_Texture* grass;
    SDL_Texture* spike;
    int theMap[25][25];
};
