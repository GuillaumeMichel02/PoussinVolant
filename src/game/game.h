#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <iostream>
#include <fstream>
#include <random>
#include <stdlib.h>
#include <SDL/SDL_mixer.h>

const int OBSTACLE_NUMBER = 3;
const int CLOUD_NUMBER = 2;
const int OBSTACLE_GAP = 75;

class Poussin
{
    public:
        int skinNumber;
        int movementFrame;
        int height;
        Poussin();
};

class Obstacle
{
    public:
        int autoScrollCycle;
        int heightArray[OBSTACLE_NUMBER];
        Obstacle();

};

class Cloud
{
    public:
        int autoScrollCycle;
        int heightArray[2];
        int typeArray[2];
        Cloud();
};

class Background
{
    public:
        int autoScrollCycle;
        Background();
};

class Game
{
    private:
        int gameState;
        int score;
        int maxScore;
        bool debugInvincibility;
        bool debugAutoplay;
        bool debugMaxScore;
        
    public:
        Poussin poussin;
        Obstacle obstacle;
        Cloud cloud;
        Background background;
        int musicCommand;
        int cheatCode;
        int resetSaveCounter;
        bool newMaxScore;

        Game();

        void start();
        int update();
        void action();
        void skinRoll();
        void reset();
        void save();
    
        int getState();
        int getScore();
        int getMaxScore();

};


#endif