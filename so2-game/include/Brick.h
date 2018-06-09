#ifndef BRICK_H
#define BRICK_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <unistd.h>
#include "Platform.h"

class Brick
{
    public:
        Brick(int xPosition, int descentRate);
        ~Brick();
        static void initScene(int xRes, int yRes, Platform *newPlatform);
        static int getPoints();
        int getxPosition();
        int getyPosition();
        int getColor();
        bool isFalling();
        std::thread fallThread();
    protected:
    private:
        static int xMax;
        static int yMax;
        static int points;
        static bool initialized;
        static bool freezed;
        static std::mutex freezeMutex;
        static std::condition_variable freezeCondition;
        static Platform *platform;
        int xPosition;
        int yPosition;
        int descentRate;
        int color;
        bool falling;
        void fall();
        void randomColor();
        static void freeze();
};

#endif // BRICK_H
