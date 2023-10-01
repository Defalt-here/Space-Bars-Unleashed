#ifndef BULLET_H
#define BULLET_H
#include<SDL.h>
class Bullet
{
    public:
        Bullet();
        float xPos,yPos;
        SDL_Rect posRect;
    protected:

    private:
};

class laser : public Bullet{
public:
int offset_width;
   laser();
};

class laser_pick : public Bullet{
public:
   laser_pick();
};
#endif // BULLET_H
