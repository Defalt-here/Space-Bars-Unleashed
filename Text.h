#ifndef TEXT_H
#define TEXT_H
#include<SDL.h>

class Text
{
    public:
        Text();

        SDL_Rect Message_rect; //create a rect
    protected:

    private:
};
class points_text
{
    public:
    float xPos,yPos;
    Points_Text();
    SDL_Rect Points_rect;
    protected:

    private:
};
#endif // TEXT_H
