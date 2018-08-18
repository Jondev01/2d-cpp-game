#include "SDL2/SDL_image.h"
class Tile{
public:
    void draw();
private:
    int x, y;
    int row, column;
    int type;
    SDL_Rect srcRect, destRect;
}
