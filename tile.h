#ifndef tile_h
#define tile_h
#include "game.hpp"
class TextureManager;
class Tile{
public:
    Tile(int row, int column, int x, int y, int type);
    void draw(SDL_Texture* sky, SDL_Texture* grass, SDL_Texture* lava);
    SDL_Rect srcRect, destRect;
private:
    int x, y;
    int row, column;
    int type;
    char const* fileName;

};
#endif // tile_h
