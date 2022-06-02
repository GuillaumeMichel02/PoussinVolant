#include "game.h"

const int BACKGROUND_SPEED = 3;
const int BACKGROUND_BASE_CYCLE = 0;

const int POUSSIN_BASE_HEIGHT = 130;
const int POUSSIN_JUMP = 0;
const int POUSSIN_SPEED = 0;

const int OBSTACLE_BASE_CYCLE = -120;
const int OBSTACLE_BASE_HEIGHT = 88;
const int OBSTACLE_SPEED = 3;

const int CLOUD_BASE_CYCLE = -40;
const int CLOUD_SPEED = 1;

const int SKIN_AMOUNT = 8;

Poussin::Poussin()
{
    skinNumber = 0;
    movementFrame = 0;
    height = POUSSIN_BASE_HEIGHT;
}

int obstacleHeightRandom()
{
    return 35 + rand()%125;
}

Obstacle::Obstacle()
{
    autoScrollCycle = OBSTACLE_BASE_CYCLE;
    heightArray[0] = OBSTACLE_BASE_HEIGHT;
    heightArray[1] = obstacleHeightRandom();
    heightArray[2] = obstacleHeightRandom();
}

Cloud::Cloud()
{
    autoScrollCycle = CLOUD_BASE_CYCLE;
    heightArray[0] = 130 + rand()%100;
    heightArray[1] = 130 + rand()%100;
    typeArray[0] = 0 + rand()%2;
    typeArray[1] = 0 + rand()%2;
}

Background::Background()
{
    autoScrollCycle = BACKGROUND_BASE_CYCLE;
}

Game::Game()
{
    poussin = Poussin();
    obstacle = Obstacle();
    cloud = Cloud();
    background = Background();

    gameState = 0;
    score = 0;
    newMaxScore = false;
    resetSaveCounter = 0;

    std::ifstream saveFile;
    saveFile.open("poussinvolant.save");
    if(!saveFile)
        saveFile.open("/mnt/Native games/poussinvolant.save");

    if(saveFile)
    {
        int saveScore, skin;
        saveFile>>saveScore>>skin;
        maxScore = saveScore;
        poussin.skinNumber = skin;
    }
    else
        maxScore = 0;

    saveFile.close();

    musicCommand = 0;

    cheatCode = 0;
    debugInvincibility = false;
    debugAutoplay = false;
    debugMaxScore = false;

}

void Game::start()
{
    if (gameState == 0)
    {
        gameState = 1;
        musicCommand = 1;
        newMaxScore = false;
        resetSaveCounter = 0;
        save();
    }
    else if (gameState == 2 && poussin.height < 0)
    {
        reset();
    }
}



bool isHeightValid(int height1, int height2, int chanceHardObstacle, int score)
{   
    return  (height2 <= height1 - 70)
            || (height2 >= height1 + 70)
            ||((height2<=height1+40)
            && (height2>=height1-40)
            && (chanceHardObstacle <= 90) 
            && (chanceHardObstacle <= score));
}

bool hasTouchedObstacle(int poussinHeight, int obstaclePosition, int obstacleHeight)
{
    if (poussinHeight<20)
        return true;
    if (obstaclePosition<-15||obstaclePosition>45)
        return false;

    const int bottomObstacle = obstacleHeight, topObstacle = obstacleHeight + OBSTACLE_GAP;
    const int leftObstacle = obstaclePosition+15, rightObstacle = obstaclePosition+49;
    int bottomPoussin = poussinHeight, topPoussin = poussinHeight+32;

    if (rightObstacle<=38)
    {
        topPoussin -=16;
        bottomPoussin +=8;
    }
    else if (rightObstacle <=44)
    {
        topPoussin -=16;
        bottomPoussin +=4;
    }
    else if (rightObstacle <=47)
    {
        topPoussin -=7;
        bottomPoussin +=4;
    }
    else if (rightObstacle <=51)
    {
        topPoussin -=4;
        bottomPoussin +=4;
    }
    else if (leftObstacle <=55)
    {
        topPoussin -=4;
        bottomPoussin +=9;
    }
    else if (leftObstacle <=58)
    {
        topPoussin -=7;
        bottomPoussin +=17;
    }
    else if (leftObstacle <=60)
    {
        topPoussin -=11;
        bottomPoussin +=17;
    }

    return topObstacle < topPoussin || bottomObstacle > bottomPoussin;
}

bool shouldJump(int poussinHeight, int obstaclePosition, int obstacleHeight[])
{
    int frontHeight;
    if (obstaclePosition > -15)
        frontHeight = obstacleHeight[0];
    else frontHeight = obstacleHeight[1];

    return poussinHeight <= frontHeight;
}


int Game::update()
{
    if (cheatCode == 4)
    {
        debugInvincibility = !debugInvincibility;
        cheatCode = 0;
        debugMaxScore = true;
    }
    if (cheatCode == 8)
    {
        debugAutoplay = !debugAutoplay;
        cheatCode = 0;
        debugMaxScore = true;
    }
    if (resetSaveCounter == 10)
    {
        maxScore = 0;
        save();
    }
    switch(gameState) {
        case 0: //Title Screen
            break;
        case 1: //Play
            background.autoScrollCycle += BACKGROUND_SPEED;
            background.autoScrollCycle = background.autoScrollCycle%240;

            obstacle.autoScrollCycle += OBSTACLE_SPEED;
            if (obstacle.autoScrollCycle >= 60)
            {
                obstacle.autoScrollCycle = -60;
                obstacle.heightArray[0] = obstacle.heightArray[1];
                obstacle.heightArray[1] = obstacle.heightArray[2];
                obstacle.heightArray[2] =  obstacleHeightRandom();
                int chanceHardObstacle = rand()%100;
                while (isHeightValid(obstacle.heightArray[1],obstacle.heightArray[2], chanceHardObstacle, score))
                    obstacle.heightArray[2] = obstacleHeightRandom();
            }
            else if(obstacle.autoScrollCycle == 0)
                score++;
            
            
            cloud.autoScrollCycle += 1;
            if (cloud.autoScrollCycle == 240)
            {
                cloud.autoScrollCycle = 0;
                cloud.heightArray[0] = cloud.heightArray[1];
                cloud.heightArray[1] = 130 + rand()%100;
                cloud.typeArray[0] = cloud.typeArray[1];
                cloud.typeArray[1] = 0 + rand()%2;
            }

            if(poussin.movementFrame < 6)
                poussin.height = poussin.height -2*poussin.movementFrame+12;
            else
                poussin.height = poussin.height -(poussin.movementFrame-6)/2 ;
            poussin.movementFrame++;

            if(debugAutoplay && shouldJump(poussin.height, -obstacle.autoScrollCycle, obstacle.heightArray))
            {
                poussin.movementFrame = 0;
            }

            if(!debugInvincibility && hasTouchedObstacle(poussin.height, -obstacle.autoScrollCycle, obstacle.heightArray[0]))
            {   
                musicCommand = 2;
                poussin.movementFrame = 0;
                gameState = 2;
                if(!debugMaxScore && score > maxScore)
                {
                    maxScore = score;
                    newMaxScore = true;
                    save();
                }
            }

            break;
        
        case 2: //GameOver
            
            if (poussin.height > -10)
            {
                poussin.height = poussin.height -2*poussin.movementFrame+6;
                poussin.movementFrame++;
            }
            break;

        default:
            break;
    }

    return gameState;
}

void Game::action()
{
    poussin.movementFrame = 0;
}

void Game::skinRoll()
{
    poussin.skinNumber = (poussin.skinNumber + 1)%SKIN_AMOUNT;
}

void Game::reset()
{
    gameState = 0;
    background.autoScrollCycle=0;
    obstacle.autoScrollCycle=-120;
    obstacle.heightArray[0]=OBSTACLE_BASE_HEIGHT;
    cloud.autoScrollCycle=-80;
    poussin.height = POUSSIN_BASE_HEIGHT;
    poussin.movementFrame = 0;
    score = 0;
    musicCommand = 3;
}

void Game::save()
{
    std::ofstream saveFile;

    saveFile.open("poussinvolant.save");
    if(!saveFile)
        saveFile.open("/mnt/Native games/poussinvolant.save");

    if(saveFile)
        saveFile<<maxScore<<" "<<poussin.skinNumber;

    saveFile.close();
}

int Game::getState()
{
    return gameState;
}

int Game::getScore()
{
    return score;
}

int Game::getMaxScore()
{
    return maxScore;
}