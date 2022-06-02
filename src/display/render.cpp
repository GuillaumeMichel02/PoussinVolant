#include "render.h"

void applySurface(int xPosition, int yPosition, SDL_Surface* source, SDL_Surface* destination)
{
    const SpriteBlit spriteBlit = SpriteBlit(0,0,source->w,source->h);
    applySurface(xPosition, yPosition, source, destination, &spriteBlit);
}

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

void renderBackground(SDL_Surface* screen, SDL_Surface* spriteBackground, int autoScrollCycle)
{
    applySurface(-autoScrollCycle,0,spriteBackground,screen);
}

void renderCloud(SDL_Surface* screen, SDL_Surface* spriteSheet, int autoScrollCycle, int cloudHeightArray[], int cloudTypeArray[], const int CLOUD_NUMBER)
{
    const SpriteBlit* SPRITE_CLOUD = NULL;
    for(int i = 0; i < CLOUD_NUMBER; i++)
    {
        if(cloudTypeArray[i] == 0)
            SPRITE_CLOUD = &SPRITE_CLOUD_A;
        else
            SPRITE_CLOUD = &SPRITE_CLOUD_B;
        applySurface(240*i-autoScrollCycle, 240-cloudHeightArray[i], spriteSheet, screen, SPRITE_CLOUD);
    }
}

void renderObstacle(SDL_Surface* screen, SDL_Surface* spriteSheet, int autoScrollCycle, int obstacleHeightArray[], const int OBSTACLE_NUMBER, const int OBSTACLE_GAP)
{
    for(int i = 0; i < OBSTACLE_NUMBER; i++)
    {
        applySurface(120*i-autoScrollCycle, 240-obstacleHeightArray[i], spriteSheet, screen, &SPRITE_OBSTACLEUP);
        applySurface(120*i-autoScrollCycle, 80-obstacleHeightArray[i]-OBSTACLE_GAP, spriteSheet, screen, &SPRITE_OBSTACLEDOWN);
    }

    if(autoScrollCycle <=-61)
    {
        applySurface(9-(120+autoScrollCycle),108,spriteSheet,screen,&SPRITE_OBSTACLEUP);
    }
}

void renderPoussin(SDL_Surface* screen, SDL_Surface* spriteSheet, int poussinHeight, int poussinMovementFrame, int poussinSkinNumber, std::map<int, SpriteBlit> spritePoussinMap)
{
    if (poussinMovementFrame >=2 && poussinMovementFrame <=4)
        applySurface(30,(240-poussinHeight)-32,spriteSheet,screen, &spritePoussinMap.at(poussinSkinNumber*2+1));
    else
        applySurface(30,(240-poussinHeight)-32,spriteSheet,screen, &spritePoussinMap.at(poussinSkinNumber*2));
}

void renderForeground(SDL_Surface* screen, SDL_Surface* spriteForeground, int autoScrollCycle)
{
    applySurface(-autoScrollCycle,216,spriteForeground,screen);
}

void renderTitleScreen(SDL_Surface* screen, SDL_Surface* spriteSheet)
{
    applySurface(88,88,spriteSheet,screen,&SPRITE_TITLE);
}

int getAnchoredPosition(std::string anchor, int sourceSize, int destinationSize)
{   
    
    int anchoredPosition = 0; 
    if (anchor == "") return anchoredPosition;

    if (anchor == "center") anchoredPosition = destinationSize/2 - sourceSize/2;
    else if (anchor == "right"||anchor == "bottom") anchoredPosition = destinationSize - sourceSize;
    return anchoredPosition;
}

void renderMessage(SDL_Surface* screen, TextManager* textManager, std::string message, bool isBig, int xOffset, int yOffset, std::string xAnchor = "", std::string yAnchor = "")
{   
    int xPosition;
    int yPosition;
    int border;
    if (isBig)
    {
        textManager->frontMessage = TTF_RenderText_Solid(textManager->fontBig, message.c_str(), textManager->frontColor);
        textManager->backMessage = TTF_RenderText_Solid(textManager->fontBig, message.c_str(), textManager->backColor);
        border = 4;
    }
    else 
    {
        textManager->frontMessage = TTF_RenderText_Solid(textManager->fontSmall, message.c_str(), textManager->frontColor);
        textManager->backMessage = TTF_RenderText_Solid(textManager->fontSmall, message.c_str(), textManager->backColor);
        border = 2;
    }
    xPosition = xOffset + getAnchoredPosition(xAnchor, textManager->frontMessage->w, screen->w);
    yPosition = yOffset + getAnchoredPosition(yAnchor, textManager->frontMessage->h, screen->h);

    applySurface(xPosition-border, yPosition-border, textManager->backMessage, screen);
    applySurface(xPosition+border, yPosition-border, textManager->backMessage, screen);
    applySurface(xPosition-border, yPosition+border, textManager->backMessage, screen);
    applySurface(xPosition+border, yPosition+border, textManager->backMessage, screen);
    applySurface(xPosition, yPosition, textManager->frontMessage, screen);
    SDL_FreeSurface(textManager->frontMessage);
    SDL_FreeSurface(textManager->backMessage);
}