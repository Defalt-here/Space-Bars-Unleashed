#ifndef PLAYER_H
#define PLAYER_H
#include<SDL.h>

class Player
{
    public:
        Player();
        float xPos,yPos;
        SDL_Rect posRect;
    protected:

    private:
};
class Enemy : public Player{
    public:
        Enemy();
    protected:

    private:
};
class Enemy2 : public Player{
    public:
        Enemy2();
        SDL_Rect enemyRect;
    protected:

    private:
};
class Enemy3 : public Player{
    public:
        Enemy3();
        SDL_Rect enemyRect;
    protected:

    private:
};
class Enemy4 : public Player{
    public:
        Enemy4();
        SDL_Rect enemyRect;
    protected:

    private:
};
class Enemy5 : public Player{
    public:
        Enemy5();
        SDL_Rect enemyRect;
    protected:

    private:
};
#endif // PLAYER_H
