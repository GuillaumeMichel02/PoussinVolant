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

    SDL_Color textColor = {0,0,0};

    SDL_Surface* timeMessage = NULL;

    Display display(screen, OBSTACLE_GAP);

 
    bool hasGameStarted = false;
    

    // auto stopTime = std::chrono::system_clock::now();

    FPSmanager* fpsManager = new FPSmanager;

    SDL_initFramerate(fpsManager);
    SDL_setFramerate(fpsManager, 30);

    

    auto currentTime = std::chrono::system_clock::now(), lastTime= currentTime;

    while ( running )
    {      
        lastTime = std::chrono::system_clock::now();

        //execTimeShow.str(std::string());
        // execTime = std::chrono::system_clock::now();
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
        display.renderGame(autoScrollCycle, obstacleHeightArray, 3, OBSTACLE_GAP, cloudHeightArray, cloudTypeArray, 2, poussinSkinNumber, poussinHeight, poussinMovementFrame);
        if(hasGameStarted)
        {
            autoScrollCycle["Background"] += 3;
            autoScrollCycle["Background"] = autoScrollCycle["Background"]%240;
            autoScrollCycle["Obstacle"] += 3;
            if (autoScrollCycle["Obstacle"] == 120)
            {
                autoScrollCycle["Obstacle"] = 0;
                obstacleHeightArray[0] = obstacleHeightArray[1];
                obstacleHeightArray[1] = obstacleHeightArray[2];
                obstacleHeightArray[2] = 40 + rand()%100;
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
            if(poussinMovementFrame < 6)
                poussinHeight = poussinHeight +2*poussinMovementFrame-12;
            else
                poussinHeight = poussinHeight +(poussinMovementFrame-6)/2 ;
            poussinMovementFrame++;
            timeMessage = TTF_RenderText_Solid(font, std::to_string(poussinHeight).c_str(), textColor);
            display.renderTime(timeMessage);
        }
        SDL_Flip(screen);
        
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
                        hasGameStarted = true;
                        poussinMovementFrame = 0;
                        break;
                    }
                    case SDLK_b:
                    {
                        hasGameStarted = false;
                        autoScrollCycle.at("Background")=0;
                        autoScrollCycle.at("Obstacle")=-120;
                        autoScrollCycle.at("Cloud")=-80;
                        poussinHeight = POUSSIN_BASE_HEIGHT;
                        poussinMovementFrame = 0;
                        obstaclePassed = 0;
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
                       poussinSkinNumber = (poussinSkinNumber + 1)%8;
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

        // int time_passed = 33 - (currentTime - lastTime > 0)?(currentTime - lastTime):0;
        // timeMessage = TTF_RenderText_Solid(font, std::to_string(time_passed).c_str(), textColor);
        // display.renderTime(timeMessage);
                currentTime = std::chrono::system_clock::now();
        int timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count(); 
        SDL_Delay(33-timePassed);

        //SDL_framerateDelay(fpsManager);

        
    }
    delete fpsManager;
    /// Deinit SDL
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}