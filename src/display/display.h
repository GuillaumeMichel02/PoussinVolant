#ifndef SCREEN_H
#define SCREEN_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <map>
#include <string>

#include "../game/game.h"
#include "render.h"
#include "sprite_blit.h"
#include "text_manager.h"

class Display
{
    private:
        SDL_Surface* screen;
        SDL_Surface* spriteSheet;
        std::map<std::string,SDL_Surface*> spriteGeneralMap;
        std::map<int, SpriteBlit> spritePoussinMap;
        TextManager* textManager;
        SDL_Surface* loadImage( std::string filename, bool transparency );
        
    public:
        Display(SDL_Surface* screen_temp, TextManager* textManager_temp);
        ~Display();
        void renderGame(Game* game);
};

#endif