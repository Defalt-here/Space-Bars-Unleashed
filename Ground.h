#ifndef GROUND_H
#define GROUND_H
#include<SDL.h>
class Ground
{
public:
    Ground();
    float xPos,yPos;
    SDL_Rect GroundRect;
protected:

private:
};

class Main_menu
{
public:
    Main_menu();
    float xPos,yPos;
    SDL_Rect GroundRect;
protected:

private:
};
class Splash
{
public:
    Splash();
    float xPos,yPos;
    SDL_Rect splshRect;
protected:

private:
};
#endif // GROUND_H
