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

    while(running & falling & yPosition < yMax - 2)
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

        // If game terminated, we shouldn't do all this stuff
        if(running)
        {
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

                    freeze();
                }

                break;
            }

            usleep(250000 - 10000 * descentRate);
        }
    }

    if(running)
    {
        // Reset
        yPosition = -1;
        falling = false;
        randomColor();
    }
}

std::thread Brick::fallThread()
{
    return std::thread(&Brick::fall, this);
}

void Brick::randomColor()
{
    color = rand() % 6 + 1;
}
