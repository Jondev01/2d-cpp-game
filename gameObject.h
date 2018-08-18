#ifndef gameObject_h
#define gameObject_h

class GameObject{
public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();

    void update();
    void render();
    void setXvel(int x);
    int getXvel();
    int getYvel(){return this->yvel;};
    void setYvel(int y);
    void setPos(int x, int y){this->xpos = x; this->ypos=y;};
    int getxPos(){return this->xpos;};
    int getyPos(){return this->ypos;};
    bool isFalling(){return fall;};
    void jump(){if(!this->fall){this->fall = true; this->yvel -= this->jumpSpeed;}};
    void startFall(){this->fall = true;};
    void stopFall();
    int getFallTime() {return this->fallTime;};
    static const double gravity = 0.8, jumpSpeed = 12;
    static const int speed = 3;

private:
    int xpos,ypos, xvel, fallTime;
    double yvel;
    bool fall;
    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};
#endif
