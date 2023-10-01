#include "Player.h"

Player::Player()
{
    xPos = 165.f; //410.f = 410.0
    yPos = 258.f;
    posRect = {
        (int)xPos,
        (int)yPos,
        40,
        40
    };
}
Enemy::Enemy()
{
    xPos = 900.f;
    yPos = 85.f;
    posRect = {
        (int)xPos,
        (int)yPos,
        40,
        40
    };
}
Enemy2::Enemy2()
{
    xPos = 2000.f;
    yPos = 185.f;
    enemyRect = {
        (int)xPos,
        (int)yPos,
        40,
        40
    };
}
Enemy3::Enemy3()
{
    xPos = 1000.f;
    yPos = 285.f;
    enemyRect = {
        (int)xPos,
        (int)yPos,
        40,
        40
    };
}
Enemy4::Enemy4()
{
    xPos = 900.f;
    yPos = 385.f;
    enemyRect = {
        (int)xPos,
        (int)yPos,
        40,
        40
    };
}
Enemy5::Enemy5()
{
    xPos = 6000.f;
    yPos = 485.f;
    enemyRect = {
        (int)xPos,
        (int)yPos,
        40,
        40
    };
}
/*Player::~Player()
{
    //dtor
}
*/
