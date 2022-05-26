//Include SDL functions and datatypes
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>

// #include "menu.h"
// #include "game.h"
#include "display.h"
// #include "input.h"



int main(int argc, char *argv[])
{   
    srand(time(NULL));

    bool running = true;

    SDL_Event event;

    Display display;

    int movementFrame = 0;
    int frame = 0;
    

    while ( running )
    {   
        if(frame == 0)
        {
            display.renderGame(movementFrame);
            movementFrame += 1;
            movementFrame = movementFrame%240;
        }
        frame = (frame+1)%10000;
        
        while( SDL_PollEvent(&event) )
        { 
             if(event.type == SDL_QUIT)
            {
                running = false;
            }

            else if(event.type == SDL_KEYUP)
            { 
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                    {
                    
                       break;
                    }
                    case SDLK_b:
                    {
                      
                       break;
                    }
                    case SDLK_x:
                    {
           
                       break;
                    }
                    case SDLK_y:
                    {
                     
                       break;
                    }
                    case SDLK_m:
                    {
                     
                       break;
                    }
                    case SDLK_n:
                    {
                      
                       break;
                    }
                    case SDLK_s:
                    {
                        running = false;
                        break;
                    }
                    case SDLK_k:
                    {
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
        
    }

    /// Deinit SDL
    SDL_Quit();

    return 0;
}