#include "Brick.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>

Platform *Brick::platform = 0;

Brick::Brick(int xPosition, int descentRate)
{
    //ctor
    this->xPosition = xPosition;
    this->yPosition = -1;
    this->descentRate = descentRate;
    this->falling = false;

    randomColor();
}

Brick::~Brick()
{
    //dtor
}

//void Brick::initScene(int xRes, int yRes, Platform *newPlatform)
//{
//    xMax = xRes;
//    yMax = yRes;
//    platform = newPlatform;
//    initialized = true;
//}

void Brick::setPlatform(Platform *newPlatform)
{
    platform = newPlatform;
}

int Brick::getxPosition()
{
    return xPosition;
}

int Brick::getyPosition()
{
    return yPosition;
}

int Brick::getColor()
{
    return color;
}


bool Brick::isFalling()
{
    return falling;
}

void Brick::fall()
{
    if(!initialized)
    {
        std::cout << "Scene size not initialized!" << std::endl;
        return;
    }

    if(platform == 0)
    {
        std::cout << "Platform not set!" << std::endl;
        return;
    }

    falling = true;

    while(falling & yPosition < yMax - 2)
    {
        // Freeze game
        if(freezed)
        {
            std::unique_lock<std::mutex> freezeLock(freezeMutex);

            while(freezed)
            {
                freezeCondition.wait(freezeLock);
            }
        }

        yPosition++;

        if(yPosition == yMax - 2 && platform->getPosition() <= xPosition && platform->getEnd() >= xPosition)
        {
            falling = false;

            if(platform->getColor() == color)
            {
                points += 5;
            }
            else
            {
                if(points != 0)
                {
                    points--;
                }

                Brick::freeze();
            }
        }

        usleep(250000 - 10000 * descentRate);
    }

    // Reset
    yPosition = -1;
    falling = false;
    randomColor();
}

std::thread Brick::fallThread()
{
    return std::thread(&Brick::fall, this);
}

void Brick::randomColor()
{
    color = rand() % 6 + 1;
}

//void Brick::freeze()
//{
//    std::unique_lock<std::mutex> freezeLock(freezeMutex);
//    freezed = true;
//    sleep(10);
//    freezed = false;
//    freezeCondition.notify_all();
//}
