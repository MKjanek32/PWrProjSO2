#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <thread>
#include <unistd.h>

// Klasa do pomiaru czasu w oparciu o funkcje systemowe
// Jan Potocki 2018
class Stopwatch
{
    public:
        Stopwatch();
        void start();
        void stop();
        bool isRunning();
        float read();
    protected:
    private:
        unsigned long long int miliseconds;
        bool running;
        std::thread measureThread;
        void measure();
};

#endif // STOPWATCH_H
