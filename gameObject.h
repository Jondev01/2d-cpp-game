#ifndef gameObject_h
#define gameObject_h

class GameObject{
public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();

    void update(bool updatex, bool updatey);
    void render();
    void setXvel(int x);
    int getXvel();
    int getYvel(){return this->yvel;};
    void setYvel(int y);
    void setPos(int x, int y){this->xpos = x; this->ypos=y;};
    int getxPos(){return this->xpos;};
    int getyPos(){return this->ypos;};
    int getW(){return destRect.w;};
    int getH(){return destRect.h;};
    bool isFalling(){return fall;};
    void jump(){if(!this->fall){this->fall = true; this->yvel -= this->jumpSpeed;}};
    void startFall(){this->fall = true;};
    void stopFall();
    void adjustToLevel(int h,int startX, int startY);
    void yAdjust(int offset);
    void xAdjust(int offset);
    void yAlign(bool up);
    void xAlign(bool left);

    SDL_Rect srcRect, destRect;
    static constexpr double gravity = 0.59, jumpSpeed = 10;
    static const int speed = 3;

private:
    int xpos,ypos, xvel;
    double yvel;
    bool fall;
    SDL_Texture* objTexture;

};
#endif
