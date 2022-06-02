#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

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


#endif