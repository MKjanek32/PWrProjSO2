#include "Platform.h"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

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
    if(!initialized)
    {
        std::cout << "Scene size not initialized!" << std::endl;
        return;
    }

    int key;

    while(running)
    {
        ncursesMutex.lock();
        key = getch();
        ncursesMutex.unlock();

        // Freeze game
        if(freezed)
        {
            std::unique_lock<std::mutex> freezeLock(freezeMutex);

            while(freezed)
            {
                freezeCondition.wait(freezeLock);
            }

            // Ignore keys pressed when frozen
            flushinp();
        }

        switch(key)
        {
        case 'a':
            if(position > 0)
            {
                position--;
            }
            break;
        case 'd':
            if(position < xMax - sprite.length())
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
    while(running)
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

        color = rand() % 6 + 1;
        sleep(15);
    }
}

std::thread Platform::colorChangeThread()
{
    return std::thread(&Platform::colorChange, this);
}
