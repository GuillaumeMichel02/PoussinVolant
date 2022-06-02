#include "display.h"



Display::Display(SDL_Surface* screen_temp, TextManager* textManager_temp)
{
    screen = screen_temp;
    std::string spriteSheetFile = "res/spritesheet.png";
    spriteSheet = loadImage(spriteSheetFile, true);

    textManager = textManager_temp;

    //Preload Background/Foreground images.
    spriteGeneralMap.insert(std::pair<std::string,SDL_Surface*>("Background",SDL_CreateRGBSurface(0,480,216,32,0,0,0,0)));
    applySurface(0,0,spriteSheet,spriteGeneralMap.at("Background"),&SPRITE_BACKGROUND);
    applySurface(240,0,spriteSheet,spriteGeneralMap.at("Background"),&SPRITE_BACKGROUND);

    spriteGeneralMap.insert(std::pair<std::string,SDL_Surface*>("Foreground",SDL_CreateRGBSurface(0,480,24,32,0,0,0,0)));
    applySurface(0,0,spriteSheet,spriteGeneralMap.at("Foreground"),&SPRITE_FOREGROUND);
    applySurface(240,0,spriteSheet,spriteGeneralMap.at("Foreground"),&SPRITE_FOREGROUND);

    for(int i = 0; i < 8; i++)
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

void Display::renderGame(Game* game)
{   
    renderBackground(screen, spriteGeneralMap.at("Background"), game->background.autoScrollCycle);
    renderCloud(screen, spriteSheet, game->cloud.autoScrollCycle, game->cloud.heightArray, game->cloud.typeArray, CLOUD_NUMBER);
    renderObstacle(screen, spriteSheet, game->obstacle.autoScrollCycle, game->obstacle.heightArray, OBSTACLE_NUMBER, OBSTACLE_GAP);
    renderPoussin(screen, spriteSheet, game->poussin.height, game->poussin.movementFrame, game->poussin.skinNumber, spritePoussinMap);
    renderForeground(screen, spriteGeneralMap.at("Foreground"), game->background.autoScrollCycle);

    switch (game->getState())
    {
        case 0:
            renderTitleScreen(screen, spriteSheet);
            renderMessage(screen, textManager, "Record : "+std::to_string(game->getMaxScore()), false, 5, -5, "", "bottom");
            break;
        case 1:
            renderMessage(screen, textManager, std::to_string(game->getScore()), false, 10, 0, "", "bottom");
            break;
        case 2:
            renderMessage(screen, textManager, std::to_string(game->getScore()), true, 0, 0, "center", "center");
            if (game->newMaxScore)
                renderMessage(screen, textManager, "NEW RECORD !", false, 0, 80, "center", "center");
            break;
        default:
            break;
    }
}