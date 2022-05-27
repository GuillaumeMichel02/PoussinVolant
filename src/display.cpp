#include "display.h"

SpriteBlit::SpriteBlit(int XOffSet_temp, int YOffSet_temp, int XSize_temp, int YSize_temp) : XOffSet(XOffSet_temp), YOffSet(YOffSet_temp), XSize(XSize_temp), YSize(YSize_temp) {}

const SpriteBlit SPRITE_BACKGROUND = SpriteBlit(0,240,240,456);
const SpriteBlit SPRITE_FOREGROUND = SpriteBlit(0,456,240,24);
const SpriteBlit SPRITE_OBSTACLEDOWN = SpriteBlit(0,0,64,128);
const SpriteBlit SPRITE_OBSTACLEUP = SpriteBlit(64,0,64,128);

Display::Display(SDL_Surface* screen_temp)
{
    screen = screen_temp;
    std::string spriteSheetFile = "res/spritesheet1.png";
    spriteSheet = loadImage(spriteSheetFile, true);

    spriteGeneralMap.insert(std::pair<spriteName, SpriteBlit>(Background, SpriteBlit(0,240,240,480)));



}

Display::~Display()
{
    SDL_FreeSurface(spriteSheet);
}

SDL_Surface* Display::loadImage( std::string filename, bool transparency = false) 
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image using SDL_image
    loadedImage = IMG_Load( filename.c_str() );

        //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        
        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

    //Return the optimized image
    return optimizedImage;
}

void applySurface( int xPosition, int yPosition, SDL_Surface* source, SDL_Surface* destination, const SpriteBlit* spriteBlit)
{
    if (xPosition >= 240 || yPosition >= 240) return;

    if (xPosition + spriteBlit->XSize < 0 || yPosition + spriteBlit->YSize < 0) return;

    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    SDL_Rect crop;
    
    //Give the offsets to the rectangle
    offset.x = xPosition;
    offset.y = yPosition;

    //Crop according to the spriteBlit
    if(spriteBlit != NULL)
    {
        crop.x = spriteBlit->XOffSet;
        crop.y = spriteBlit->YOffSet;
        crop.w = spriteBlit->XSize;
        crop.h = spriteBlit->YSize;
    }

    if(xPosition<0)
    {
        crop.x -= xPosition;
        crop.w += xPosition;
        offset.x = 0;
    }

    if(yPosition<0)
    {
        crop.y -= yPosition;
        crop.h += yPosition;
        offset.y = 0;
    }

    SDL_BlitSurface( source, &crop, destination, &offset);

    
}

void applySurface(int xPosition, int yPosition, SDL_Surface* source, SDL_Surface* destination)
{
    const SpriteBlit spriteBlit = SpriteBlit(0,0,source->w,source->h);
    applySurface(xPosition, yPosition, source, destination, &spriteBlit);
}

void renderBackground(SDL_Surface* screen, SDL_Surface* spriteSheet, std::map <std::string,int> autoScrollCycle)
{
    applySurface(-autoScrollCycle.at("Background"),0,spriteSheet,screen,&SPRITE_BACKGROUND);
    applySurface(240-autoScrollCycle.at("Background"),0,spriteSheet,screen,&SPRITE_BACKGROUND);
}

void renderObstacle(SDL_Surface* screen, SDL_Surface* spriteSheet, std::map <std::string,int> autoScrollCycle, int obstacleHeightArray[], int obstacleNumber, const int OBSTACLE_GAP)
{
    for(int i = 0; i < obstacleNumber; i++)
    {
        applySurface(120*i-autoScrollCycle.at("Obstacle"),240-obstacleHeightArray[i],spriteSheet, screen, &SPRITE_OBSTACLEUP);
        applySurface(120*i-autoScrollCycle.at("Obstacle"),120-obstacleHeightArray[i]-OBSTACLE_GAP, spriteSheet, screen, &SPRITE_OBSTACLEDOWN);
    }
}

void renderForeground(SDL_Surface* screen, SDL_Surface* spriteSheet, std::map <std::string,int> autoScrollCycle)
{
    applySurface(-autoScrollCycle.at("Background"),216,spriteSheet,screen,&SPRITE_FOREGROUND);
    applySurface(240-autoScrollCycle.at("Background"),216,spriteSheet,screen,&SPRITE_FOREGROUND);
}

void Display::renderGame(std::map <std::string,int> autoScrollCycle, int obstacleHeightArray[], int obstacleNumber, const int OBSTACLE_GAP)
{   
    renderBackground(screen, spriteSheet, autoScrollCycle);
    renderObstacle(screen, spriteSheet, autoScrollCycle, obstacleHeightArray, obstacleNumber, OBSTACLE_GAP);
    renderForeground(screen, spriteSheet, autoScrollCycle);
    
}

void Display::renderTime(SDL_Surface* timeMessage)
{
    applySurface(100,100, timeMessage, screen);
    SDL_Flip(screen);
}