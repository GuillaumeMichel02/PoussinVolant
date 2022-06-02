#ifndef RENDER_H
#define RENDER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <map>
#include <string>

#include "sprite_blit.h"
#include "text_manager.h"

void applySurface( int xPosition, int yPosition, SDL_Surface* source, SDL_Surface* destination, const SpriteBlit* spriteBlit);

void applySurface(int xPosition, int yPosition, SDL_Surface* source, SDL_Surface* destination);

void renderBackground(SDL_Surface* screen, SDL_Surface* spriteBackground, int autoScrollCycle);

void renderCloud(SDL_Surface* screen, SDL_Surface* spriteSheet, int autoScrollCycle, int cloudHeightArray[], int cloudTypeArray[], const int CLOUD_NUMBER);

void renderObstacle(SDL_Surface* screen, SDL_Surface* spriteSheet, int autoScrollCycle, int obstacleHeightArray[], const int OBSTACLE_NUMBER, const int OBSTACLE_GAP);

void renderPoussin(SDL_Surface* screen, SDL_Surface* spriteSheet, int poussinHeight, int poussinMovementFrame, int poussinSkinNumber, std::map<int, SpriteBlit> spritePoussinMap);

void renderForeground(SDL_Surface* screen, SDL_Surface* spriteForeground, int autoScrollCycle);

void renderTitleScreen(SDL_Surface* screen, SDL_Surface* spriteSheet);

int getAnchoredPosition(std::string anchor, int sourceSize, int destinationSize);

void renderMessage(SDL_Surface* screen, TextManager* textManager, std::string message, bool isBig, int xOffset, int yOffset, std::string xAnchor, std::string yAnchor);

#endif