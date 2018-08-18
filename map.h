#ifndef map_h
#define map_h
#include "game.hpp"

class Map{
public:
    Map();
    ~Map();

    void LoadMap(int arr[25][25]);
    void DrawMap();
    bool collision(int xpos, int ypos, int type);

private:
    SDL_Rect src, dest;
    SDL_Texture* sky;
    SDL_Texture* grass;
    SDL_Texture* spike;
    int theMap[25][25];
    int testMap[50*30];
    int cam_x, cam_y, cam_vx, camvy;
};
#endif
