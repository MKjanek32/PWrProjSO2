#include "Brick.h"

bool Brick::initialized = false;
int Brick::xMax;
int Brick::yMax;

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

void Brick::initScene(int xRes, int yRes)
{
    xMax = xRes;
    yMax = yRes;
    initialized = true;
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
    if(initialized)
    {
        falling = true;

        while(yPosition < yMax - 2)
        {
            yPosition++;
            usleep(250000 - 10000 * descentRate);
        }

        // Reset
        yPosition = -1;
        falling = false;
        randomColor();
    }
    else
    {
        std::cout << "Scene size not initialized!" << std::endl;
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
