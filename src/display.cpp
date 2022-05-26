#include "display.h"

SpriteBlit::SpriteBlit(int XOffSet_temp, int YOffSet_temp, int XSize_temp, int YSize_temp) : XOffSet(XOffSet_temp), YOffSet(YOffSet_temp), XSize(XSize_temp), YSize(YSize_temp) {}

Display::Display()
{
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(240, 240, 32,
                         SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_ShowCursor(0);

    std::string spriteSheetFile = "res/spritesheet.png";
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

void Display::applySurface( int xPosition, int yPosition, SDL_Surface* source, SpriteBlit spriteBlit, SDL_Surface* destination )
{

    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    SDL_Rect crop;
    
    //Give the offsets to the rectangle
    offset.x = xPosition;
    offset.y = yPosition;

    //Crop according to the spriteBlit

    crop.x = spriteBlit.XOffSet;
    crop.y = spriteBlit.YOffSet;
    crop.w = spriteBlit.XSize;
    crop.h = spriteBlit.YSize;

    if(!(xPosition>0 && yPosition>0))
    {
        crop.x -= xPosition;
        crop.y -= yPosition;
        crop.w += xPosition;
        crop.h += yPosition;
    }

    SDL_BlitSurface( source, &crop, destination, NULL );

    
}

void Display::renderGame(int movementFrame)
{   
    applySurface(-movementFrame,0,spriteSheet,SpriteBlit(0,240,240,480),screen);
    applySurface(240-movementFrame,0,spriteSheet,SpriteBlit(0,240,240,480),screen);
    SDL_UpdateRect( screen, 0,0,0,0 );
}