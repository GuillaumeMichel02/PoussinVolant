//Include SDL functions and datatypes
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_framerate.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <map>
#include <sstream>

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


    SDL_Init(SDL_INIT_VIDEO);
    SDL_ShowCursor(0);

    SDL_Surface* screen = SDL_SetVideoMode(240, 240, 32,
                          SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

    // image = load_image("res/spritesheet1.png");
    // apply_surface(0,0,image,screen);

    // SDL_UpdateRect(screen, 0,0,0,0);

    TTF_Init();

    TTF_Font *font = TTF_OpenFont("res/lazy.ttf", 28);

    SDL_Color textColor = {0,0,0};

    SDL_Surface* timeMessage = NULL;

    Display display(screen);

    std::map <std::string, int> autoScrollCycle;
    autoScrollCycle.insert(std::pair<std::string, int>("Background",0));
    autoScrollCycle.insert(std::pair<std::string, int>("Obstacle",-120));

    int obstacleHeightArray[3] = {100, 80, 120};

    const int OBSTACLE_GAP = 80;

    while ( running )
    {      
        //SDL_framerateDelay(fpsManager);
        std::stringstream execTimeShow;
        int execTime = SDL_GetTicks();
        autoScrollCycle["Background"] += 3;
        autoScrollCycle["Background"] = autoScrollCycle["Background"]%240;
        autoScrollCycle["Obstacle"] += 3;
        if (autoScrollCycle["Obstacle"] == 120)
        {
            autoScrollCycle["Obstacle"] = 0;
            obstacleHeightArray[0] = obstacleHeightArray[1];
            obstacleHeightArray[1] = obstacleHeightArray[2];
            obstacleHeightArray[2] = 50 + rand()%100;
        }
        display.renderGame(autoScrollCycle, obstacleHeightArray, 3, OBSTACLE_GAP);

        execTime = SDL_GetTicks() - execTime;
        
        execTimeShow << execTime;

        timeMessage = TTF_RenderText_Solid(font, execTimeShow.str().c_str(), textColor);
        display.renderTime(timeMessage);

        SDL_Delay(33 - execTime);
        
        
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
    delete timeMessage;
    /// Deinit SDL
    SDL_Quit();

    return 0;
}