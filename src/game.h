#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <deque>
#include <fstream>
#include <random>


class Game
{
    private:
        int gameState;
        int score;
        int maxScore;
        std::map <std::string, int> autoScrollCycle;
        int obstacleHeightArray[3];
        int cloudHeightArray[2];
        int cloudTypeArray[2];
        int poussinSkinNumber;
        int poussinMovementFrame;
        int poussinHeight;
    public:
        Character character;
        int obstacleHeight[OBSTACLE_NUMBER];
        int movement_frame;

        Game();
        int updateFrame();
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