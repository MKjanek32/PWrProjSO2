#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include <thread>
#include "Scene.h"

class Platform : public Scene
{
    public:
        Platform();
        ~Platform();
        const char *getSprite();
        int getPosition();
        int getEnd();
        int getColor();
        void terminateThreads();
        std::thread moveKeyThread();
        std::thread colorChangeThread();
    protected:
    private:
        std::string sprite;
        int position;
        int points;
        int color;
        void moveKey();
        void colorChange();
};

#endif // PLATFORM_H
