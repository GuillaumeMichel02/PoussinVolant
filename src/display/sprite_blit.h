#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

class SpriteBlit
{
    public:
        int XOffSet;
        int YOffSet;
        int XSize;
        int YSize;
        SpriteBlit(int XOffSet_temp, int YOffSet_temp, int XSize_temp, int YSize_temp);
};

const SpriteBlit SPRITE_BACKGROUND = SpriteBlit(0,240,240,456);
const SpriteBlit SPRITE_FOREGROUND = SpriteBlit(0,456,240,24);
const SpriteBlit SPRITE_TITLE = SpriteBlit(0,160,64,64);
const SpriteBlit SPRITE_OBSTACLEDOWN = SpriteBlit(0,0,64,160);
const SpriteBlit SPRITE_OBSTACLEUP = SpriteBlit(64,0,64,160);
const SpriteBlit SPRITE_CLOUD_A = SpriteBlit(64,160,64,32);
const SpriteBlit SPRITE_CLOUD_B = SpriteBlit(64,192,64,32);

#endif