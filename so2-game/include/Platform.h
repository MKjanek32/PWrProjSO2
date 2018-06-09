#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include <thread>
#include <ncurses.h>
#include <unistd.h>

class Platform
{
    public:
        Platform();
        ~Platform();
        static void initScene(int xRes);
        const char *getSprite();
        int getPosition();
        int getEnd();
        int getColor();
        void terminateThreads();
        std::thread moveKeyThread();
        std::thread colorChangeThread();
    protected:
    private:
        static bool initialized;
        static int posMax;
        std::string sprite;
        int position;
        int points;
        int color;
        bool running;
        void moveKey();
        void colorChange();
};

#endif // PLATFORM_H
