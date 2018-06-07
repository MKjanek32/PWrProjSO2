#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <ctime>

// Klasa do pomiaru czasu (wieloplatformowa)
// Jan Potocki 2018
class Stopwatch
{
    public:
        Stopwatch();
        void start();
        void check();
        double read();
        double measurement;
    protected:
    private:
        clock_t tstart;
        clock_t tstop;
};

#endif // STOPWATCH_H
