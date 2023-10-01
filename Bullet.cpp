#include "Bullet.h"
#include "Player.h"
Player player1;
Bullet::Bullet()
{
    xPos = player1.xPos; //410.f = 410.0
    yPos = player1.yPos;
   posRect = {
        (int)xPos,
        (int)yPos,
        15,
        5
    };
}
laser::laser()
{
    xPos = 410.f; //410.f = 410.0
    yPos = 100.f;
   posRect = {
        (int)xPos,
        (int)yPos,
        800,
        10
    };
}

laser_pick::laser_pick()
{
    xPos = 410.f; //410.f = 410.0
    yPos = 100.f;
   posRect = {
        (int)xPos,
        (int)yPos,
        20,
        20
    };
}
