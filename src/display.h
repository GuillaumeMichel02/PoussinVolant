#ifndef SCREEN_H
#define SCREEN_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <map>
#include <string>

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

class Display
{
    private:
        SDL_Surface* screen;
        SDL_Surface* spriteSheet;
        std::map<spriteName,SpriteBlit> spriteGeneralMap;
        std::map<int, SpriteBlit> spritePoussinMap;

        SDL_Surface* loadImage( std::string filename, bool transparency );
        // void applySurface( int xPosition, int yPosition, SDL_Surface* source, SpriteBlit sprite, SDL_Surface* destination );
    public:
        Display(SDL_Surface* screen);
        ~Display();
        void renderGame(std::map <std::string,int> autoScrollCycle, int obstacleHeightArray[], int obstacleNumber, const int OBSTACLE_GAP);
        void renderTime(SDL_Surface* timeMessage);
};

#endif