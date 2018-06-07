#ifndef BRICK_H
#define BRICK_H

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
        bool falling;
        void fall();
};

#endif // BRICK_H
