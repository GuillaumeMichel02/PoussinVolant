#include "display.h"

SpriteBlit::SpriteBlit(int XOffSet_temp, int YOffSet_temp, int XSize_temp, int YSize_temp) : XOffSet(XOffSet_temp), YOffSet(YOffSet_temp), XSize(XSize_temp), YSize(YSize_temp) {}

const SpriteBlit SPRITE_BACKGROUND = SpriteBlit(0,240,240,456);
const SpriteBlit SPRITE_FOREGROUND = SpriteBlit(0,456,240,24);
const SpriteBlit SPRITE_OBSTACLEDOWN = SpriteBlit(0,0,64,128);
const SpriteBlit SPRITE_OBSTACLEUP = SpriteBlit(64,0,64,128);
const SpriteBlit SPRITE_CLOUD_A = SpriteBlit(64,128,64,32);
const SpriteBlit SPRITE_CLOUD_B = SpriteBlit(64,160,64,32);

const int SKIN_AMOUNT = 8;

void applySurface( int xPosition, int yPosition, SDL_Surface* source, SDL_Surface* destination, const SpriteBlit* spriteBlit)
{
    if (xPosition >= destination->w || yPosition >= destination->h) return;

    if (xPosition + spriteBlit->XSize < 0 || yPosition + spriteBlit->YSize < 0) return;

    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    SDL_Rect crop;
    
    //Give the offsets to the rectangle
    offset.x = xPosition;
    offset.y = yPosition;

    //Crop according to the spriteBlit
    crop.x = spriteBlit->XOffSet;
    crop.y = spriteBlit->YOffSet;
    crop.w = spriteBlit->XSize;
    crop.h = spriteBlit->YSize;

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

Display::Display(SDL_Surface* screen_temp, int OBSTACLE_GAP)
{
    screen = screen_temp;
    std::string spriteSheetFile = "res/spritesheet1.png";
    spriteSheet = loadImage(spriteSheetFile, true);

    //Preload Background/Foreground images.
    spriteGeneralMap.insert(std::pair<std::string,SDL_Surface*>("Background",SDL_CreateRGBSurface(0,480,216,32,0,0,0,0)));
    applySurface(0,0,spriteSheet,spriteGeneralMap.at("Background"),&SPRITE_BACKGROUND);
    applySurface(240,0,spriteSheet,spriteGeneralMap.at("Background"),&SPRITE_BACKGROUND);

    spriteGeneralMap.insert(std::pair<std::string,SDL_Surface*>("Foreground",SDL_CreateRGBSurface(0,480,24,32,0,0,0,0)));
    applySurface(0,0,spriteSheet,spriteGeneralMap.at("Foreground"),&SPRITE_FOREGROUND);
    applySurface(240,0,spriteSheet,spriteGeneralMap.at("Foreground"),&SPRITE_FOREGROUND);

    for(int i = 0; i < SKIN_AMOUNT; i++)
    {
        spritePoussinMap.insert(std::pair<int,SpriteBlit>(2*i,SpriteBlit(128+32*(i/3),64*(i%3),32,32)));
        spritePoussinMap.insert(std::pair<int,SpriteBlit>(2*i+1,SpriteBlit(128+32*(i/3),32+64*(i%3),32,32)));
    }
}

Display::~Display()
{
    SDL_FreeSurface(spriteSheet);
    SDL_FreeSurface(spriteGeneralMap.at("Background"));
    SDL_FreeSurface(spriteGeneralMap.at("Foreground"));
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

void renderBackground(SDL_Surface* screen, SDL_Surface* spriteBackground, std::map <std::string,int> autoScrollCycle)
{

    applySurface(-autoScrollCycle.at("Background"),0,spriteBackground,screen);
}

void renderCloud(SDL_Surface* screen, SDL_Surface* spriteSheet, std::map <std::string,int> autoScrollCycle, int cloudHeightArray[], int cloudTypeArray[], int cloudNumber)
{
    const SpriteBlit* SPRITE_CLOUD = NULL;
    for(int i = 0; i < cloudNumber; i++)
    {
        if(cloudTypeArray[i] == 0)
            SPRITE_CLOUD = &SPRITE_CLOUD_A;
        else
            SPRITE_CLOUD = &SPRITE_CLOUD_B;
        applySurface(240*i-autoScrollCycle.at("Cloud"), 240-cloudHeightArray[i], spriteSheet, screen, SPRITE_CLOUD);
    }
}

void renderObstacle(SDL_Surface* screen, SDL_Surface* spriteSheet, std::map <std::string,int> autoScrollCycle, int obstacleHeightArray[], int obstacleNumber, const int OBSTACLE_GAP)
{
    for(int i = 0; i < obstacleNumber; i++)
    {
        applySurface(120*i-autoScrollCycle.at("Obstacle"), 240-obstacleHeightArray[i], spriteSheet, screen, &SPRITE_OBSTACLEUP);
        applySurface(120*i-autoScrollCycle.at("Obstacle"), 120-obstacleHeightArray[i]-OBSTACLE_GAP, spriteSheet, screen, &SPRITE_OBSTACLEDOWN);
    }
}

void renderPoussin(SDL_Surface* screen, SDL_Surface* spriteSheet, int poussinHeight, int poussinMovementFrame, int poussinSkinNumber, std::map<int, SpriteBlit> spritePoussinMap)
{
    if (poussinMovementFrame >=2 && poussinMovementFrame <=4)
        applySurface(30,poussinHeight+32,spriteSheet,screen, &spritePoussinMap.at(poussinSkinNumber*2+1));
    else
        applySurface(30,poussinHeight+32,spriteSheet,screen, &spritePoussinMap.at(poussinSkinNumber*2));
}

void renderForeground(SDL_Surface* screen, SDL_Surface* spriteForeground, std::map <std::string,int> autoScrollCycle)
{
    applySurface(-autoScrollCycle.at("Background"),216,spriteForeground,screen);
}

void Display::renderGame(std::map <std::string,int> autoScrollCycle, int obstacleHeightArray[], int obstacleNumber, const int OBSTACLE_GAP, int cloudHeightArray[], int cloudTypeArray[], int cloudNumber, int poussinSkinNumber, int poussinHeight, int poussinMovementFrame)
{   
    renderBackground(screen, spriteGeneralMap.at("Background"), autoScrollCycle);
    renderCloud(screen, spriteSheet, autoScrollCycle, cloudHeightArray, cloudTypeArray, cloudNumber);
    renderObstacle(screen, spriteSheet, autoScrollCycle, obstacleHeightArray, obstacleNumber, OBSTACLE_GAP);
    renderPoussin(screen, spriteSheet, poussinHeight, poussinMovementFrame, poussinSkinNumber, spritePoussinMap);
    renderForeground(screen, spriteGeneralMap.at("Foreground"), autoScrollCycle);
}

void Display::renderTime(SDL_Surface* timeMessage)
{
    applySurface(10,10, timeMessage, screen);
    
}
