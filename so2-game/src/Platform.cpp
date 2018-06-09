#include "Platform.h"

bool Platform::initialized = false;
int Platform::posMax;

Platform::Platform()
{
    //ctor
    points = 0;
    color = 0;
    sprite = "<--->";
}

Platform::~Platform()
{
    //dtor
}

void Platform::initScene(int xRes)
{
    posMax = xRes;
    initialized = true;
}

const char *Platform::getSprite()
{
    return sprite.c_str();
}

int Platform::getPosition()
{
    return position;
}

int Platform::getEnd()
{
    int endPos = position + sprite.length() - 1;
    return endPos;
}

int Platform::getColor()
{
    return color;
}

void Platform::terminateThreads()
{
    running = false;
}

void Platform::moveKey()
{
    int key;

    running = true;

    while(running)
    {
        key = getch();

        switch(key)
        {
        case 'a':
            if(position > 0)
            {
                position--;
            }
            break;
        case 'd':
            if(position < posMax - sprite.length())
            {
                position++;
            }
        }
    }
}

std::thread Platform::moveKeyThread()
{
    return std::thread(&Platform::moveKey, this);
}

void Platform::colorChange()
{
    running = true;

    while(running)
    {
        color = rand() % 6 + 1;
        sleep(15);
    }
}

std::thread Platform::colorChangeThread()
{
    return std::thread(&Platform::colorChange, this);
}
