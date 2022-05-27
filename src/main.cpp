//Include SDL functions and datatypes
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_framerate.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <map>
#include <sstream>
#include <chrono>

// #include "menu.h"
// #include "game.h"
#include "display.h"
// #include "input.h"

const int FRAMES_PER_SECOND = 30;
const int OBSTACLE_GAP = 80;


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

    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096);

    Mix_Music *music = Mix_LoadMUS("res/music.ogg");

    Mix_PlayMusic( music, -1 );

    TTF_Init();

    TTF_Font *font = TTF_OpenFont("res/lazy.ttf", 50);

    SDL_Color textColor = {255,255,255};

    // SDL_Surface* timeMessage = NULL;

    Display display(screen, OBSTACLE_GAP);

    std::map <std::string, int> autoScrollCycle;
    autoScrollCycle.insert(std::pair<std::string, int>("Background",0));
    autoScrollCycle.insert(std::pair<std::string, int>("Obstacle",-120));
    autoScrollCycle.insert(std::pair<std::string, int>("Cloud",-80));

    int obstacleHeightArray[3] = {100, 80, 120};
    int cloudHeightArray[4] = {180,150};
    int cloudTypeArray[4] = {0,1};
    // auto startTime = std::chrono::system_clock::now();
    int obstaclePassed = 0;
    // auto execTime = std::chrono::system_clock::now();
    // auto stopTime = std::chrono::system_clock::now();

    FPSmanager* fpsManager = new FPSmanager;

    SDL_initFramerate(fpsManager);
    SDL_setFramerate(fpsManager, 30);

    int skinNumber = 0;

    while ( running )
    {      

        //execTimeShow.str(std::string());
        // execTime = std::chrono::system_clock::now();
        autoScrollCycle["Background"] += 3;
        autoScrollCycle["Background"] = autoScrollCycle["Background"]%240;
        autoScrollCycle["Obstacle"] += 3;
        if (autoScrollCycle["Obstacle"] == 120)
        {
            autoScrollCycle["Obstacle"] = 0;
            obstacleHeightArray[0] = obstacleHeightArray[1];
            obstacleHeightArray[1] = obstacleHeightArray[2];
            obstacleHeightArray[2] = 50 + rand()%100;
            obstaclePassed++;
        }
        autoScrollCycle["Cloud"] += 1;
        if (autoScrollCycle["Cloud"] == 240)
        {
            autoScrollCycle["Cloud"] = 0;
            cloudHeightArray[0] = cloudHeightArray[1];
            cloudHeightArray[1] = 130 + rand()%100;
            cloudTypeArray[0] = cloudTypeArray[1];
            cloudTypeArray[1] = 0 + rand()%2;
        }
        display.renderGame(autoScrollCycle, obstacleHeightArray, 3, OBSTACLE_GAP, cloudHeightArray, cloudTypeArray, 2, skinNumber);

        // stopTime = std::chrono::system_clock::now();
        // execTimeShow << execTime << " / " << (SDL_GetTicks() - startTime)/1000 << " / "<<obstaclePassed;

    

        // timeMessage = TTF_RenderText_Solid(font, std::to_string(frameDuration).c_str(), textColor);
        // display.renderTime(timeMessage);

        // SDL_Delay(31);

        
        
        
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
                        skinNumber = (skinNumber + 1)%16;
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
                        Mix_HaltMusic( );
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
        SDL_framerateDelay(fpsManager);
    }
    delete fpsManager;
    /// Deinit SDL
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}