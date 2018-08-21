#ifndef map_h
#define map_h
#include "game.hpp"
#include <vector>
#include "tile.h"
#include "Level.h"
class Tile;

class Map{
public:
    Map(Level& level);
    ~Map();

    void LoadMap();
    void DrawMap();
    bool collision(int xpos, int ypos, int type);
    std::vector<Tile> tiles;
    void addTile(int row, int column, int x, int y, int type);
    void update(int xvel, int yvel, bool updatex, bool updatey);
    void yAdjust(int offset);
    void xAdjust(int offset);
    int yAlign(bool up);
    int xAlign(bool left);
    std::vector<int> theMap;
    Level level;
private:
    SDL_Rect src, dest;
    SDL_Texture* sky;
    SDL_Texture* grass;
    SDL_Texture* lava;
    SDL_Texture* finish;
};
#endif
