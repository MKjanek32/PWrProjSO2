#ifndef BRICK_H
#define BRICK_H

#include <thread>
#include "Platform.h"
#include "Scene.h"

class Brick : public Scene
{
    public:
        Brick(int xPosition, int descentRate);
        ~Brick();
        static void setPlatform(Platform *newPlatform);
        int getxPosition();
        int getyPosition();
        int getColor();
        bool isFalling();
        std::thread fallThread();
    protected:
    private:
        static Platform *platform;
        int xPosition;
        int yPosition;
        int descentRate;
        int color;
        bool falling;
        void fall();
        void randomColor();
};

#endif // BRICK_H
