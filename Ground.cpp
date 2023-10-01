#include "Ground.h"

Ground::Ground()
{
    xPos = -668.f;
    yPos = 0.f;
    GroundRect = {
        (int)xPos,
        (int)yPos,
        2131,
        600
    };
}

Main_menu::Main_menu()
{
    xPos = 0.f;
    yPos = 0.f;
    GroundRect = {
        (int)xPos,
        (int)yPos,
        800,
        600
    };
}
Splash::Splash()
{
    xPos = 0.f;
    yPos = 0.f;
    splshRect = {
        (int)xPos,
        (int)yPos,
        800,
        600
    };
}
/*
Ground::~Ground()
{
    //dtor
}
*/
