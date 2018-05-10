#include <iostream>
#include <mutex>
#include "Entry.h"

bool Entry::initialized = false;
int Entry::xMax;
int Entry::yMax;

bool full;
std::mutex state;
std::mutex ready1;
std::mutex ready2;
std::mutex service;

Entry::Entry(int speedRate)
{
    //ctor
    this->xPosition = -1;
    this->yPosition = yMax / 2;
    this->speedRate = speedRate;
    this->symbol = "*";

    if(initialized == false)
    {
        std::cout << "WARNING: Scene size not initialized!" << std::endl;
    }
}

Entry::~Entry()
{
    //dtor
}

void Entry::initScene(int xRes, int yRes)
{
    xMax = xRes;
    yMax = yRes;
    initialized = true;
}

int Entry::getxPosition()
{
    return xPosition;
}

int Entry::getyPosition()
{
    return yPosition;
}

std::string Entry::getSymbol()
{
    return symbol;
}

void Entry::run()
{
    if(initialized)
    {
        while(xPosition < xMax / 2)
        {
            xPosition++;
            usleep(100000 - 10000 * speedRate);
        }

        bool goAround;

        state.lock();
        if(full == true)
        {
            goAround = true;
        }
        else
        {
            goAround = false;
            full = true;
            ready2.lock();
        }
        state.unlock();

        while(goAround)
        {
            while(yPosition < 3 * yMax / 4)
            {
                yPosition++;
                usleep(100000 - 10000 * speedRate);
            }

            while(xPosition < 3 * xMax / 4)
            {
                xPosition++;
                usleep(100000 - 10000 * speedRate);
            }

            while(yPosition > yMax / 4)
            {
                yPosition--;
                usleep(100000 - 10000 * speedRate);
            }

            while(xPosition > xMax / 2)
            {
                xPosition--;
                usleep(100000 - 10000 * speedRate);
            }

            while(yPosition < yMax / 2)
            {
                yPosition++;
                usleep(100000 - 10000 * speedRate);
            }

            state.lock();
            if(full == false)
            {
                goAround = false;
                full = true;
                ready2.lock();
            }
            state.unlock();
        }

        xPosition++;
        symbol = "2";

        ready1.lock();
        state.lock();
        full = false;
        state.unlock();
        ready2.unlock();
        xPosition++;
        symbol = "1";

        service.lock();
        ready1.unlock();
        xPosition++;
        symbol = "#";
        sleep(5);

        service.unlock();
        symbol = "*";

        while(xPosition < xMax)
        {
            xPosition++;
            usleep(100000 - 10000 * speedRate);
        }
    }
    else
    {
        std::cout << "ERROR: Scene size not initialized!" << std::endl;
    }
}

std::thread Entry::runThread()
{
    return std::thread(&Entry::run, this);
}
