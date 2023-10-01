#include <SDL.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Player.h"
#include "Bullet.h"
#include "Ground.h"
#include "Text.h"
#include <stdlib.h>
#include <cmath>
#include <SDL_ttf.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

//------------------------------------------------Declaration------------------------------------
SDL_DisplayMode dm;
int delay = 500;
int crashed = 0;
int appear = 2;
float move_en = 3.f,move_en2 = 3.f;
float cosx,siny;
bool isRunning = true;
bool sound = true;
bool test = true;
bool destroy,destroy2 = false;
bool mm = true;
bool laser_test = false;
bool rand_check = true;
bool splassFlag = false;
float xPos_in = 10.f;
float yPos_in = 10.f;
float rel_pos = 10.f;
int health = 3;
const Uint8* keystates = SDL_GetKeyboardState(NULL);
SDL_Renderer *renderer; //Declare a renderer to render on the screen
SDL_Window *window; //Declare a window
SDL_Surface* surface;
SDL_Texture* texture_bullet;
SDL_Surface* surface2;
SDL_Texture* texture2;
SDL_Surface* surface_hero;
SDL_Texture* texture_hero;
SDL_Surface* gScreenSurface;
SDL_Surface* pts_surface;
SDL_Surface* text;
SDL_Surface* menu_surface;
SDL_Texture* menu_texture;
SDL_Texture* Screen_texture;
SDL_Texture* enemy_2;
SDL_Texture* enemy_3;
SDL_Texture* enemy_4;
SDL_Texture* enemy_5;
SDL_Texture* score_pts;
SDL_Texture* text_texture;
SDL_Surface* laser_sur;
SDL_Texture* laser_tex;
SDL_Surface* laserpick_sur;
SDL_Texture* laserpick_tex;
SDL_Surface* splash_sur;
SDL_Texture* splash_tex;
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gLose = NULL;
Mix_Chunk *Blaster = NULL;
Mix_Chunk *Death = NULL;
Mix_Chunk *Laser_charge = NULL;
Mix_Chunk *Laser_down = NULL;
Mix_Music *gMusic = NULL;
TTF_Font* font;
SDL_Color Color = {255, 196, 0};
Uint32 startFrameTicks = 0;
Uint32 endFrameTicks = 0;
SDL_RendererFlip flip = SDL_FLIP_NONE;
float frameTicks = 0.f;
float rotater = 0.1;
void enemy_init();
int isColliding();
void bullet_init();
void hero_init();
void enemy_movement();
void score();
bool game_over();
void clear_space();
void retry();
void mainmenu();
void splash_screen();
int laser_init();
int x_angle = 50;
int y_angle = 00;
int points = 0;
string update;

//Objects
Player player;
Bullet bullet;
laser laser;
Enemy enemy;
Enemy2 enemy2;
Enemy3 enemy3;
Enemy4 enemy4;
Enemy5 enemy5;
Ground ground;
Text score_text;
points_text pt_txt;
Main_menu Main_menu;
laser_pick laser_pick;
Splash Splash;
int main(int argc, char**argv)
{
//------------------------------------------------Initialise------------------------------------

    //Initialize
    if ( TTF_Init() < 0 )
    {
        cout << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0) //Initialize everything
    {
        cout << SDL_GetError() << endl;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout <<  "SDL_mixer could not initialize! SDL_mixer Error: \n" << Mix_GetError();

    }
    window = SDL_CreateWindow("Space Bars",300,50,800,600,SDL_WINDOW_BORDERLESS);
    if (window == NULL)
    {
        cout << SDL_GetError() << endl;
    }
    else
    {
        gScreenSurface = SDL_GetWindowSurface( window );
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        cout << SDL_GetError() << endl;
    }
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        cout << SDL_GetError() << endl;
    }
//------------------------------------------------Initialise textures and music------------------------------------
    splash_sur = IMG_Load("Splash Screen-02.png");
    splash_tex = SDL_CreateTextureFromSurface(renderer,splash_sur);
    surface = IMG_Load("bullet.png");
    texture_bullet = SDL_CreateTextureFromSurface(renderer,surface);
    laser_sur = IMG_Load("laser-04.png");
    laser_tex = SDL_CreateTextureFromSurface(renderer,laser_sur);
    laserpick_sur = IMG_Load("Laser-Pickup-05.png");
    laserpick_tex = SDL_CreateTextureFromSurface(renderer,laserpick_sur);
    surface_hero = IMG_Load("hero-03.png");
    texture_hero = SDL_CreateTextureFromSurface(renderer, surface_hero);
    SDL_FreeSurface(surface_hero);
    surface2 = IMG_Load("Enemy-06-06.png");
    texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    enemy_2 = SDL_CreateTextureFromSurface(renderer, surface2);
    enemy_3 = SDL_CreateTextureFromSurface(renderer, surface2);
    enemy_4 = SDL_CreateTextureFromSurface(renderer, surface2);
    enemy_5 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface2);
    menu_surface = IMG_Load("Main Menu-01.jpg");
    menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface);
    SDL_FreeSurface(menu_surface);
    gScreenSurface = IMG_Load("Background-01.jpg");
    Screen_texture = SDL_CreateTextureFromSurface(renderer, gScreenSurface);
    SDL_FreeSurface(gScreenSurface);
    gScratch = Mix_LoadWAV( "Blast.wav" );
    gLose = Mix_LoadWAV( "Hellnaw.wav" );
    Blaster = Mix_LoadWAV("blaster-2-81267.wav");
    Death = Mix_LoadWAV("Death.wav");
    Laser_charge = Mix_LoadWAV("Laserup.wav");
    Laser_down = Mix_LoadWAV("LaserDown.wav");
    gMusic = Mix_LoadMUS( "neon-gaming-128925.wav" );
    font = TTF_OpenFont("PixeloidSansBold-RpeJo.ttf", 24);
    text = TTF_RenderText_Solid(font, "Game Over ", Color);
    pts_surface = TTF_RenderText_Solid(font,"Press R to retry", Color); //(char*)update.c_str()
    score_pts = SDL_CreateTextureFromSurface(renderer, pts_surface);
    text_texture = SDL_CreateTextureFromSurface(renderer, text );
    Mix_PlayMusic( gMusic, -1 );
//------------------------------------------------Game Loop------------------------------------
    //Mix_PausedMusic();
    while(isRunning)
    {
        //Close
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                //Mix_ResumeMusic();
                Mix_PlayMusic( gMusic, -1 );
                break;
            }
        }
        //Movement
        SDL_PumpEvents();

        if(health  >= 0)
        {
            if(keystates[SDL_SCANCODE_W])
            {
                if(player.yPos >= -1)
                {
                    player.yPos -= yPos_in;
                }
            }
            if(keystates[SDL_SCANCODE_S])
            {
                if(player.yPos <= 558)
                {
                    player.yPos += yPos_in;
                }
            }
            if(keystates[SDL_SCANCODE_A])
            {
                rotater = 180;
                x_angle = -50;
                y_angle = 0;
                if(player.xPos >= 15)
                {
                    player.xPos -= xPos_in;
                }
                if(ground.xPos <= -1)
                {
                    ground.xPos += xPos_in-8;
                }
                laser.posRect.w = 800;
                laser.posRect.x =  player.posRect.x - 810;
            }
            if(keystates[SDL_SCANCODE_D])
            {
                rotater = 0;
                x_angle = 50;
                y_angle = 0;
                if(player.xPos <= 725)
                {
                    player.xPos += xPos_in;
                }
                if(ground.xPos >= -1294)
                {
                    ground.xPos -= xPos_in-8;
                }
                laser.posRect.w = (800 - player.posRect.x);
                laser.posRect.x = player.xPos+40;
            }
            /*if(keystates[SDL_SCANCODE_RIGHT])
            {
                rotater = 0;
                x_angle = 50;
                y_angle = 0;
                laser_test = true;
            }
            if(keystates[SDL_SCANCODE_LEFT])
            {
                rotater = 180;
                x_angle = -50;
                y_angle = 0;
                laser_test = false;
            }
            if(keystates[SDL_SCANCODE_DOWN])
            {
                rotater = 90;
                x_angle = 0;
                y_angle = 50;
            }
            if(keystates[SDL_SCANCODE_UP])
            {
                rotater = -90;
                x_angle = 0;
                y_angle = -50;
            }*/
            if(keystates[SDL_SCANCODE_SPACE]&&destroy == false) //Make a bullet texture every time I press space!
            {
                SDL_SetTextureAlphaMod(texture_bullet,255);
                Mix_PlayChannel( -1, Blaster, 0 );
                destroy = true;
                //texture_bullet = SDL_CreateTextureFromSurface(renderer,surface);
                bullet_init();
            }
            if(destroy)
            {
                bullet.posRect.x += x_angle; //Give the bullet a velocity
                bullet.posRect.y += y_angle;
                if(bullet.posRect.x >= 800 || bullet.posRect.x <= -5 || bullet.posRect.y >= 600 || bullet.posRect.y <= -40)
                {
                    // Destroy the bullet
                    //SDL_DestroyTexture(texture_bullet);
                    bullet_init();
                    SDL_SetTextureAlphaMod(texture_bullet,0);
                    destroy = false;
                }
            }
        }
        else
        {
            game_over();
            if(keystates[SDL_SCANCODE_R])
            {
                retry();
            }
        }
        startFrameTicks = SDL_GetTicks();
//------------------------------------------------Update Movements------------------------------------
        player.posRect.x = player.xPos;
        player.posRect.y = player.yPos;
        ground.GroundRect.x = ground.xPos;
        enemy.posRect.x  = enemy.xPos -= move_en;
        enemy2.enemyRect.x = enemy2.xPos -= move_en;
        enemy3.enemyRect.x = enemy3.xPos -= move_en;
        enemy4.enemyRect.x = enemy4.xPos -= move_en;
        enemy5.enemyRect.x = enemy5.xPos -= move_en;
//------------------------------------------------Render Some Shit------------------------------------

        //SDL_Surface* icon = IMG_Load("Bullet-Copy.ico");
        //SDL_SetWindowIcon(window,icon);

        SDL_SetWindowTitle(window,"Space Bars");
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        Mix_ResumeMusic();
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,Screen_texture,NULL,&ground.GroundRect);
        SDL_RenderCopyEx(renderer,texture_bullet,NULL,&bullet.posRect,rotater,NULL,flip);
        SDL_RenderCopy(renderer,score_pts,NULL,&pt_txt.Points_rect);
        SDL_RenderCopy(renderer,text_texture,NULL,&score_text.Message_rect);
        SDL_SetTextureAlphaMod(text_texture,0);
        laser_init();
        hero_init();
        enemy_init();
        enemy_movement();
        isColliding();
        score();
        mainmenu();
        splash_screen();
        SDL_RenderPresent(renderer);
        endFrameTicks = SDL_GetTicks();
//------------------------------------------------Calculate za frame rate------------------------------------

        float deltaTicks = endFrameTicks - startFrameTicks;
        if(deltaTicks < 16.6666f)
        {
            SDL_Delay(16.6666f - deltaTicks);
        }

//------------------------------------------------Clean 'em memories up------------------------------------
    }
    //SDL_FreeSurface(surfaceMessage);
    //SDL_DestroyTexture(Message);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(enemy_2);
    SDL_DestroyTexture(enemy_3);
    SDL_DestroyTexture(enemy_4);
    SDL_DestroyTexture(enemy_5);
    SDL_DestroyTexture(texture_hero);
    SDL_DestroyTexture(texture_bullet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(gScreenSurface);
    SDL_DestroyTexture(splash_tex);
    SDL_Quit();
    return 0;
}
//------------------------------------------------Da Func(tions)------------------------------------
void bullet_init()
{
    bullet.posRect.x = player.xPos+rel_pos; //initialise bullet give it positions
    bullet.posRect.y = player.yPos+18;
    SDL_RenderCopyEx(renderer,texture_bullet,NULL,&bullet.posRect,rotater,NULL,flip);
}
int laser_init()
{
    srand(time(NULL));
    int randomx = (rand()%800);
    int randomy = (rand()%600);
    int enemy_pos = 800+(rand()%300);
    bool sound_check;
    SDL_RenderCopy(renderer,laserpick_tex,NULL,&laser_pick.posRect);
    laser_pick.posRect.x = -200;
    if(rand_check == true)
    {
        appear =(rand()%15);
        //cout << appear << endl;
    }
    if(appear == 2)
    {
        rand_check = false;
        laser_pick.posRect.x = randomx;
        laser_pick.posRect.y = randomy;
    }
    if(SDL_HasIntersection(&player.posRect,&laser_pick.posRect))
    {
        laser_pick.posRect.x = -200;
        delay = 500;
        rand_check = true;
        laser_test = true;
        sound_check = true;
        appear = 0;
        Mix_PlayChannel( -1, Laser_charge, 0 );
    }
    if(delay == 0 && sound_check == true)
    {
        Mix_PlayChannel( -1, Laser_down, 0 );
        cout << "Yes";
        sound_check = false;
    }
    if(delay == 0)
    {
        laser_test = false;
    }
    if(keystates[SDL_SCANCODE_L] && laser_test == true)
    {
        delay--;
        //initialise laser give it positions
        laser.posRect.y = player.yPos+15;
        SDL_RenderCopyEx(renderer,laser_tex,NULL,&laser.posRect,180,NULL,flip);
        if(SDL_HasIntersection(&laser.posRect,&enemy.posRect))
        {
            Mix_PlayChannel( -1, gScratch, 0 );
            enemy.xPos = enemy_pos;
            crashed = 2;
            return 1;
        }
        if(SDL_HasIntersection(&laser.posRect,&enemy2.enemyRect))
        {
            Mix_PlayChannel( -1, gScratch, 0 );
            enemy2.xPos = enemy_pos;
            crashed = 2;
            return 1;
        }
        if(SDL_HasIntersection(&laser.posRect,&enemy3.enemyRect))
        {
            Mix_PlayChannel( -1, gScratch, 0 );
            enemy3.xPos = enemy_pos;
            crashed = 2;
            return 1;
        }
        if(SDL_HasIntersection(&laser.posRect,&enemy4.enemyRect))
        {
            enemy4.xPos = enemy_pos;
            crashed = 2;
            return 1;
        }
        if(SDL_HasIntersection(&laser.posRect,&enemy5.enemyRect))
        {
            Mix_PlayChannel( -1, gScratch, 0 );
            enemy5.xPos = enemy_pos;
            crashed = 2;
            return 1;
        }
        return 0;
    }
    return -1;
}
void enemy_init()
{
    SDL_RenderCopy(renderer,texture2,NULL,&enemy.posRect);//initialise enemy
    SDL_RenderCopy(renderer,enemy_2,NULL,&enemy2.enemyRect);
    SDL_RenderCopy(renderer,enemy_3,NULL,&enemy3.enemyRect);
    SDL_RenderCopy(renderer,enemy_5,NULL,&enemy4.enemyRect);
    SDL_RenderCopy(renderer,enemy_5,NULL,&enemy5.enemyRect);
}
int isColliding()
{
    if(SDL_HasIntersection(&bullet.posRect,&enemy.posRect))
    {
        enemy.xPos = 5000;
        crashed = 1;
        Mix_PlayChannel( -1, gScratch, 0 );
        return 1;
    }
    if(SDL_HasIntersection(&bullet.posRect,&enemy2.enemyRect))
    {
        enemy2.xPos = 2000;
        crashed = 2;
        Mix_PlayChannel( -1, gScratch, 0 );
        return 1;
    }
    if(SDL_HasIntersection(&bullet.posRect,&enemy3.enemyRect))
    {
        enemy3.xPos = 900;
        crashed = 2;
        Mix_PlayChannel( -1, gScratch, 0 );
        return 1;
    }
    if(SDL_HasIntersection(&bullet.posRect,&enemy4.enemyRect))
    {
        enemy4.xPos = 3000;
        crashed = 2;
        Mix_PlayChannel( -1, gScratch, 0 );
        return 1;
    }
    if(SDL_HasIntersection(&bullet.posRect,&enemy5.enemyRect))
    {
        enemy5.xPos = 900;
        crashed = 2;
        Mix_PlayChannel( -1, gScratch, 0 );
        return 1;
    }
    if(SDL_HasIntersection(&player.posRect,&enemy.posRect)||SDL_HasIntersection(&player.posRect,&enemy2.enemyRect)||SDL_HasIntersection(&player.posRect,&enemy3.enemyRect)||SDL_HasIntersection(&player.posRect,&enemy4.enemyRect)||SDL_HasIntersection(&player.posRect,&enemy5.enemyRect))
    {
        health--;
        return -1;
    }
    if(enemy.posRect.x <= -40)
    {
        Mix_PlayChannel( -1, gLose, 0 );
        enemy.xPos = 5000;
        return 2;
    }
    if(enemy2.enemyRect.x <= -40)
    {
        Mix_PlayChannel( -1, gLose, 0 );
        enemy2.xPos = 2000;
        return 2;
    }
    if(enemy3.enemyRect.x <= -40)
    {
        Mix_PlayChannel( -1, gLose, 0 );
        enemy3.xPos = 900;
        return 2;
    }
    if(enemy4.enemyRect.x <= -40)
    {
        Mix_PlayChannel( -1, gLose, 0 );
        enemy4.xPos = 3000;
        return 2;
    }
    if(enemy5.enemyRect.x <= -40)
    {
        Mix_PlayChannel( -1, gLose, 0 );
        enemy5.xPos = 900;
        return 2;
    }
    return 0;
}
void hero_init()//initialise Hero
{
    SDL_RenderCopyEx(renderer,texture_hero,NULL,&player.posRect,rotater,NULL,flip);
}
void enemy_movement()
{
    if(crashed == 1)
    {
        move_en = 3;
    }
    if(crashed == 2)
    {
        move_en2 = 3;
    }
}
bool game_over(){
SDL_BlendMode blending;
SDL_SetTextureBlendMode(text_texture,blending);
    if(health <= 0)
    {
        move_en = 0;
        SDL_SetTextureAlphaMod(laserpick_tex,0);
        if(sound)
        {
            Mix_PlayChannel( -1, Death, 0 );
            sound = false;
        }
        rotater += 30;
        for(int i = 0; i <= 5; i ++)
        {
            player.yPos += i;
        }
        for(float j = 0.f; j <= 255; j+=0.01){
             SDL_Delay(.01);
             SDL_SetTextureAlphaMod(text_texture,j);
        }
        Mix_PauseMusic();
    }
    return true;
}
void score()
{
    if(isColliding() == 1 ||laser_init() == 1)
    {
        points++;
        system("cls");
        cout << "Score: " << points << endl;
    }
    if(isColliding() == 1 || laser_init() == 1 && move_en <= 3.7)
    {
        move_en += 0.1;
    }
    if(isColliding() == 2 && points > 0)
    {
        points--;
        system("cls");
        cout << "Score: " << points << endl;
    }
}
void clear_space()
{
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(enemy_2);
    SDL_DestroyTexture(enemy_3);
    SDL_DestroyTexture(enemy_4);
    SDL_DestroyTexture(enemy_5);
    SDL_DestroyTexture(texture_hero);
    SDL_DestroyTexture(texture_bullet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(gScreenSurface);
}
void retry()
{
    //appear = 0;
    hero_init();
    bullet_init();
    enemy.xPos  = 900;
    enemy2.xPos =  6000;
    enemy3.xPos =  900;
    enemy4.xPos =  1000;
    enemy5.xPos =  2000;
    player.xPos = 165.f;
    player.yPos = 258.f;
    SDL_SetTextureAlphaMod(laserpick_tex,255);
    move_en = 3.f;
    move_en2 = 3.f;
    points = 0;
    health = 3;
    rotater = 0;
    x_angle = 50;
    y_angle = 0;
    Mix_ResumeMusic();
    sound = true;
    laser_test = false;
    laser_pick.posRect.x = -200;
    system("cls");
    cout << "Score: " << points;
}
void mainmenu()
{
    if(mm)
    {
        SDL_RenderCopy(renderer,menu_texture,NULL,&Main_menu.GroundRect);
        move_en = 0;
        move_en2 = 0;
        Mix_PauseMusic();
        /*xPos_in = 0;
        yPos_in = 0;*/
    }
    if(keystates[SDL_SCANCODE_SPACE] && test && splassFlag)
    {
        mm = false;
        test = false;
        SDL_DestroyTexture(menu_texture);
        move_en = 3.f;
        move_en2 = 3.f;
    }
}
void splash_screen(){
    SDL_RenderCopy(renderer,splash_tex,NULL,&Splash.splshRect);
    SDL_SetTextureAlphaMod(splash_tex,255);
    if(keystates[SDL_SCANCODE_S]){
    SDL_DestroyTexture(splash_tex);
    splassFlag = true;
    }
}
