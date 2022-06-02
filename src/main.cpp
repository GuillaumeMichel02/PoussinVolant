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

#include "game/game.h"
#include "display/display.h"

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

    // SDL_Surface* icon = IMG_Load("res/PoussinVolant.png");
    // SDL_WM_SetIcon(icon, NULL);
    // SDL_WM_SetCaption("Poussin Volant", "Poussin Volant");
    // SDL_FreeSurface(icon);

    Mix_OpenAudio( 96000, MIX_DEFAULT_FORMAT, 1, 4096);

    Mix_Music* music = Mix_LoadMUS("res/music.ogg");
    Mix_Chunk* hitSound = Mix_LoadWAV("res/bonk.wav");

    TTF_Init();
    TTF_Font* fontBig = TTF_OpenFont("res/riffic-bold.ttf", 80);
    TTF_Font* fontSmall = TTF_OpenFont("res/riffic-bold.ttf", 30);

    TextManager textManager = TextManager(fontBig, fontSmall);

    Game game;

    Display display(screen, &textManager);


    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,100,100,100));
    
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
                    case SDLK_SPACE:
                    {
                        game.start();
                        if(game.getState() == 1)
                            game.action();
                        break;
                    }
                    case SDLK_b:
                    case SDLK_ESCAPE:
                    {
                        game.reset();
                        game.resetSaveCounter++;
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
                        break;
                    }
                    case SDLK_k:
                    {
                        break;
                    }
                    case SDLK_q:
                    {
                        running = false;
                        break;
                    }
                    case SDLK_u:
                    case SDLK_UP:
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
                    case SDLK_DOWN:
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
                    case SDLK_LEFT:
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
                    case SDLK_RIGHT:
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

        currentTime = std::chrono::system_clock::now();
        int timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count(); 
        SDL_Flip(screen);
        if (timePassed < frameDuration)
            SDL_Delay(frameDuration-timePassed);

        
    }
    /// Deinit SDL
    Mix_HaltMusic();
    Mix_FreeChunk(hitSound);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    TTF_CloseFont(textManager.fontBig);
    TTF_CloseFont(textManager.fontSmall);
    TTF_Quit();
    SDL_Quit();

    return 0;
}