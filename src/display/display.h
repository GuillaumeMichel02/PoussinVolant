#ifndef SCREEN_H
#define SCREEN_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <map>
#include <string>

#include "game.h"

enum spriteName {Background, Title, ObstacleUp, ObstacleDown, Cloud1, Cloud2};

class SpriteBlit
{
    public:
        int XOffSet;
        int YOffSet;
        int XSize;
        int YSize;
        SpriteBlit(int XOffSet_temp, int YOffSet_temp, int XSize_temp, int YSize_temp);
};

class TextManager
{
    public:
        TTF_Font *fontBig;
        TTF_Font *fontSmall;

        SDL_Color frontColor;
        SDL_Color backColor;

        SDL_Surface* frontMessage;
        SDL_Surface* backMessage;

        TextManager(TTF_Font* fontBig_temp, TTF_Font* fontSmall_temp);
};

class Display
{
    private:
        SDL_Surface* screen;
        SDL_Surface* spriteSheet;
        std::map<std::string,SDL_Surface*> spriteGeneralMap;
        std::map<int, SpriteBlit> spritePoussinMap;
        TextManager* textManager;

        SDL_Surface* loadImage( std::string filename, bool transparency );
        // void applySurface( int xPosition, int yPosition, SDL_Surface* source, SpriteBlit sprite, SDL_Surface* destination );
    public:
        Display(SDL_Surface* screen_temp, TextManager* textManager_temp);
        ~Display();
        void renderGame(Game* game);
};

#endif