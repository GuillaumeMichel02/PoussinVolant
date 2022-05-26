#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <deque>
#include <fstream>
#include <random>

const int SPEED_VALUE = 30;
const int JUMP_VALUE = 30;
const int OBSTACLE_NUMBER = 5;

int maxScoreKeyGen(int max_score);

bool isObstacleInRange(int xposition);

bool isCharacterHit(int character_yposition, int obstacle_yposition);

class Game
{
    private:
        int game_state;
        int score;
        int max_score;
    public:
        Character character;
        int obstacleHeight[OBSTACLE_NUMBER];
        int movement_frame;

        Game();
        int update();
        void save();

        void getState();
        void setState(int state);
};

class Position
{
    private:
        int y;
        int x;
};

class Character
{
    private:
        //float rotation;
        Position position;
        int movement_frame;
        int skin;

    public:
        Character();
        void update();
        void render();
        int getSkin();
        int setSkin();
};

//YPosition of obstacle is the top-left corner of the top part of the obstacle
class Obstacle : public Element
{
    public:
        Obstacle();
        void update();

};

class Cloud : public Element
{
    public:
        Cloud();
        void update();
};


#endif