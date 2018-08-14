#include "game.hpp"

class GameObject{
public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();

    void update();
    void render();
private:
    int xpos,ypos;
    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};
