#include "game.h"

const int POUSSIN_BASE_HEIGHT = 50;
const int OBSTACLE_NUMBER = 3;
const int OBSTACLE_BASE_CYCLE = -120;
const int OBSTACLE_GAP = 90;
const int CLOUD_NUMBER = 2;
const int CLOUD_BASE_CYCLE = -80;

int maxScoreKeyGen(int max_score)
{
    for(int i = 1; i < 10; i++)
    {
        max_score = max_score * i+1 * 7;
        max_score = max_score - i;
        max_score = max_score/2;
        max_score = max_score%10000
    }

    return max_score;
}





Game::Game()
{
    game_state = 0;
    score = 0;
    
    std::ifstream saveFile("poussinvolant.save")

    if(save_file)
    {
        int key;
        save_file>>maxScore>>key;
        if(maxScoreKeyGen(maxScore) != key)
        {
            maxScore = 0;
        }
    }
    else
        max_score = 0;
    
    autoScrollCycle.insert(std::pair<std::string, int>("Background",0));
    autoScrollCycle.insert(std::pair<std::string, int>("Obstacle",OBSTACLE_BASE_CYCLE));
    autoScrollCycle.insert(std::pair<std::string, int>("Cloud",CLOUD_BASE_CYCLE));
    
    obstacleHeightArray[3] = {100, 80, 120};
    cloudHeightArray[2] = {180,150};
    cloudTypeArray[2] = {0,1};
    
    poussinSkinNumber = 0;
    poussinMovementFrame = 0;
    poussinHeight = POUSSIN_BASE_HEIGHT;
}

int Game::update()
{
    bool obstacle_passed = false;
    int obstacle_yposition = 0;
    character.update();

    for(int i = 0; i<obstacles.size(); i++)
    {
        obstacles[i].update();
        if (obstacle_passed)
            continue;
        if obstacle_in_range(obstacles[i].getElementXPosition)
        {
            obstacle_yposition = obstacles[i].getElementYPosition;
        }
    }

    for(int i = 0; i<clouds.size(); i++)
    {
        clouds[i].update();
    }

    

    return game_state;
}

void Game::save()
{
    std::ofstream save_file("poussinvolant.save")

    if(save_file)
        save_file<<max_score<<" "<<max_scoreKeyGen(max_score);
}

void Game::changeState(int state)
{
    game_state = state;
}

vector<int> Game::getElementXPosition(ElementType element)
{
    vector<int> XPosition;
    switch(element)
    {
        case Character:
            XPosition.push_back(character.getXPosition);
            break;
        case Obstacle:
            for(int i = 0; i < obstacles.size(); i++)
                XPosition.push_back(obstacles[i].getXPosition);
            break;
        case Cloud:
            for(int i = 0; i < clouds.size(); i++)
                XPosition.push_back(clouds[i].getXPosition);
            break;
        default:
            break;
    }
    return XPosition;
}

vector<int> Game::getElementYPosition(ElementType element)
{
    vector<int> YPosition;
    switch(element)
    {
        case Character:
            YPosition.push_back(character.getYPosition);
            break;
        case Obstacle:
            for(int i = 0; i < obstacles.size(); i++)
                YPosition.push_back(obstacles[i].getYPosition);
            break;
        case Cloud:
            for(int i = 0; i < clouds.size(); i++)
                YPosition.push_back(clouds[i].getYPosition);
            break;
        default:
            break;
    }
    return YPosition;
}

vector<int> Game::getElementSkin(ElementType element)
{
    vector<int> Skin;
    switch(element)
    {
        case Character:
            Skin.push_back(character.getSkin);
            break;
        case Obstacle:
            for(int i = 0; i < obstacles.size(); i++)
                Skin.push_back(obstacles[i].getSkin);
            break;
        case Cloud:
            for(int i = 0; i < clouds.size(); i++)
                Skin.push_back(clouds[i].getSkin);
            break;
        default:
            break;
    }
    return Skin;
}

int Element::getXPosition()
{
    return xposition;
}

int Element::getYPosition()
{
    return yposition;
}

int Element::getSkin()
{
    return skin;
}

Character::Character()
{
    yposition = 120;
    xposition = 20;
    skin = 1;
    movement_frame = 0;
}

void Character::update()
{
    if movement_frame < 60 
        yposition = yposition + jump - movement_frame;
        movement_frame++;
    else
        yposition = yposition + jump - 60;
}

void Character::reset()
{
    yposition = 120;
    xposition = 20;
    movement_frame = 1;
}

Obstacle::Obstacle()
{
    xposition = 240;
    yposition = 264 - rand()%120;
    skin = 11;
}

void Obstacle::update()
{
    xposition = xposition - 1;
}

Cloud::Cloud()
{
    xposition = 240;
    yposition = rand()%208;
    skin = 9 + rand()%2;
}

void Cloud::update()
{
    xposition = xposition - 1;
}
