//Include SDL functions and datatypes
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <map>
#include <chrono>

// #include "menu.h"
#include "game.h"
#include "display.h"
// #include "input.h"

int main(int argc, char *argv[])
{   
    srand(time(NULL));

    bool running = true;
    int frameDuration = 33;

    SDL_Event event;
    

    SDL_Init(SDL_INIT_VIDEO);
    SDL_ShowCursor(0);

    SDL_Surface* screen = SDL_SetVideoMode(240, 240, 32,
                          SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

    Mix_OpenAudio( 96000, MIX_DEFAULT_FORMAT, 1, 4096);

    Mix_Music* music = Mix_LoadMUS("res/music.ogg");
    Mix_Chunk* hitSound = Mix_LoadWAV("res/bonk.wav");


    TTF_Init();

    TTF_Font *font = TTF_OpenFont("res/lazy.ttf", 50);

    SDL_Color textColor = {0,0,0};

    SDL_Surface* timeMessage = NULL;

    Game game;

    Display display(screen);

    std::string scoreShow;
    
    auto currentTime = std::chrono::system_clock::now(), lastTime= currentTime;

    while ( running )
    {      
        lastTime = std::chrono::system_clock::now();

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
        game.update();
        if(game.musicCommand != 0)
        {
            switch (game.musicCommand)
            {
                case 1:
                    Mix_PlayMusic( music, -1 );
                    break;
                case 2:
                    Mix_PlayChannel(-1,hitSound,0);
                    Mix_HaltMusic( );
                    
                    break;
                case 3:
                    Mix_HaltMusic( );
                default:
                    break;
            }
            game.musicCommand = 0;
        }
        display.renderGame(&game);

        
       
       
        
        while( SDL_PollEvent(&event) )
        { 
             if(event.type == SDL_QUIT)
            {
                running = false;
            }

            else if(event.type == SDL_KEYDOWN)
            { 
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                    {
                        game.start();
                        if(game.getState() == 1)
                            game.action();
                        break;
                    }
                    case SDLK_b:
                    {
                        game.reset();
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
                        game.skinRoll();
                        break;
                    }
                    case SDLK_n:
                    {
                        if (frameDuration == 33) frameDuration = 12;
                        else frameDuration = 33;
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
                    case SDLK_u:
                    {
                        switch (game.cheatCode)
                        {
                            case 1:
                                game.cheatCode++;
                                break;
                            case 2:
                                game.cheatCode++;
                                break;
                            case 6:
                                game.cheatCode++;
                                break;
                            default:
                                game.cheatCode = 0;
                                break;
                        }
                        break;
                    }
                    case SDLK_d:
                    {
                        switch (game.cheatCode)
                        {
                            case 0:
                                game.cheatCode++;
                                break;
                            case 7:
                                game.cheatCode++;
                                Mix_PlayChannel(-1,hitSound,0);
                                break;
                            default:
                                game.cheatCode = 0;
                                break;
                        }
                        break;
                    }
                    case SDLK_l:
                    {   
                        switch (game.cheatCode)
                        {
                            case 0:
                                game.cheatCode=5;
                                break;
                            case 5:
                                game.cheatCode++;
                                break;
                            case 3:
                                game.cheatCode++;
                                Mix_PlayChannel(-1,hitSound,0);
                                break;
                            default:
                                game.cheatCode = 0;
                                break;
                        }
                        break;
                    }
                    case SDLK_r:
                    {
                        game.cheatCode = 0;
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
                currentTime = std::chrono::system_clock::now();
        int timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count(); 
        scoreShow = std::to_string(game.getScore());
        timeMessage = TTF_RenderText_Solid(font, scoreShow.c_str(), textColor);
        display.renderTime(timeMessage);
        SDL_FreeSurface(timeMessage);
         SDL_Flip(screen);
        if (timePassed < frameDuration)
            SDL_Delay(frameDuration-timePassed);

        //SDL_framerateDelay(fpsManager);

        
    }
    /// Deinit SDL
    Mix_FreeChunk(hitSound);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}