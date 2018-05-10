#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <thread>
#include <unistd.h>

class Entry
{
    public:
        Entry(int speedRate);
        ~Entry();
        static void initScene(int xRes, int yRes);
        int getxPosition();
        int getyPosition();
        std::string getSymbol();
        std::thread runThread();
    protected:
    private:
        static bool initialized;
        static int xMax;
        static int yMax;
        int xPosition;
        int yPosition;
        int speedRate;
        std::string symbol;
        void run();
};

#endif // ENTRY_H
