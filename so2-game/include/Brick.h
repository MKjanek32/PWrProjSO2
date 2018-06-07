#ifndef BRICK_H
#define BRICK_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <unistd.h>

class Brick
{
    public:
        Brick(int xPosition, int descentRate);
        ~Brick();
        static void initScene(int xRes, int yRes);
        int getxPosition();
        int getyPosition();
        int getColor();
        bool isFalling();
        std::thread fallThread();
    protected:
    private:
        static bool initialized;
        static int xMax;
        static int yMax;
        int xPosition;
        int yPosition;
        int descentRate;
        int color;
        bool falling;
        void fall();
        void randomColor();
};

#endif // BRICK_H
