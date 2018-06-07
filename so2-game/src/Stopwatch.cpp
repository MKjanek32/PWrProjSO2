#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
    //ctor
    // PEA 3
    // Jan Potocki 2018
}

void Stopwatch::start()
{
    tstart = clock();
    measurement = 0;
}

void Stopwatch::stop()
{
    tstop = clock();
    measurement = ((double)(tstop - tstart))/CLOCKS_PER_SEC;
}

double Stopwatch::read()
{
    return measurement;
}
