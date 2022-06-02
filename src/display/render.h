#ifndef RENDER_H
#define RENDER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <map>
#include <string>

#include "sprite_manager.h"

void renderBackground(SDL_Surface* screen, SDL_Surface* spriteBackground, int autoScrollCycle);

void renderCloud(SDL_Surface* screen, SDL_Surface* spriteSheet, int autoScrollCycle, int cloudHeightArray[], int cloudTypeArray[], const int CLOUD_NUMBER);

void renderObstacle(SDL_Surface* screen, SDL_Surface* spriteSheet, int autoScrollCycle, int obstacleHeightArray[], const int OBSTACLE_NUMBER, const int OBSTACLE_GAP);

#endif