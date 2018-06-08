#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
    //ctor
    // Jan Potocki 2018
}

void Stopwatch::start()
{
    running = true;
    miliseconds = 0;
    measureThread = std::thread(&Stopwatch::measure, this);
}

void Stopwatch::stop()
{
    running = false;
    measureThread.join();
}

bool Stopwatch::isRunning()
{
    return running;
}

float Stopwatch::read()
{
    float measurement = (float)miliseconds / 1000;
    return measurement;
}

void Stopwatch::measure()
{
    while(running)
    {
        usleep(1000);
        miliseconds++;
    }
}
