#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <ctime>

// Klasa do pomiaru czasu (wieloplatformowa)
// Jan Potocki 2017
class Stopwatch
{
    public:
        Stopwatch();
        void start();
        void stop();
        double read();
        double measurement;
    protected:
    private:
        clock_t tstart;
        clock_t tstop;
};

#endif // STOPWATCH_H
