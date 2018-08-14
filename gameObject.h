#include "game.hpp"

class GameObject{
public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();

    void update();
    void render();
    void setXvel(int x);
    int getXvel();
    void setYvel(int y);
private:
    int xpos,ypos, xvel, yvel;
    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};
