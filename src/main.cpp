//Include SDL functions and datatypes
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_framerate.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <map>

// #include "menu.h"
// #include "game.h"
#include "display.h"
// #include "input.h"

const int FRAMES_PER_SECOND = 30;


int main(int argc, char *argv[])
{   
    srand(time(NULL));

    bool running = true;

    SDL_Event event;

    FPSmanager* fpsManager = new FPSmanager;

    SDL_initFramerate(fpsManager);


    Display display;

    std::map <std::string, int> autoScrollCycle;
    autoScrollCycle.insert(std::pair<std::string, int>("Background",0));
    autoScrollCycle.insert(std::pair<std::string, int>("Obstacle",-120));

    int obstacleHeightArray[3] = {100, 80, 120};

    const int OBSTACLE_GAP = 80;

    while ( running )
    {   
        SDL_framerateDelay(fpsManager);	

        display.renderGame(autoScrollCycle, obstacleHeightArray, 3, OBSTACLE_GAP);
        
        autoScrollCycle["Background"] += 2;
        autoScrollCycle["Background"] = autoScrollCycle["Background"]%240;
        autoScrollCycle["Obstacle"] += 2;
        if (autoScrollCycle["Obstacle"] == 120)
        {
            autoScrollCycle["Obstacle"] = 0;
            obstacleHeightArray[0] = obstacleHeightArray[1];
            obstacleHeightArray[1] = obstacleHeightArray[2];
            obstacleHeightArray[2] = 50 + rand()%100;
        }
        
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

    delete fpsManager;
    /// Deinit SDL
    SDL_Quit();

    return 0;
}