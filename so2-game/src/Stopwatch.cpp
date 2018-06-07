#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
    //ctor
    // Jan Potocki 2018
}

void Stopwatch::start()
{
    tstart = clock();
    measurement = 0;
}

void Stopwatch::check()
{
    tstop = clock();
    measurement = 10 * ((double)(tstop - tstart)) / CLOCKS_PER_SEC;
}

double Stopwatch::read()
{
    return measurement;
}
