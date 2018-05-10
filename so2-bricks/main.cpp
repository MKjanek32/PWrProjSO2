#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <ncurses.h>
#include <unistd.h>
#include "Brick.h"

bool running = true, climate = false;
std::vector<Brick> bricks;


// "Monitor" function
void refreshScreen()
{
    while(running == true)
    {
        clear();

        for(int i = 0; i < bricks.size(); i++)
        {
            // Easter egg (1)
            if(climate)
                {
                mvprintw(bricks[i].getyPosition(), bricks[i].getxPosition(), "*" );
                }
            else
                {
                mvprintw(bricks[i].getyPosition(), bricks[i].getxPosition(), "#" );
                }
        }

        refresh();

        // Refresh every 0.01 s
        usleep(10000);
    }
}

int main(int argc, char *argv[])
{
    int xMax, yMax, fallingBricks = 0;
    std::vector<std::thread> brickThreads;

    srand(time(0));

    // Easter egg (2)
    if(argc == 2)
    {
        std::string param(argv[1]);

        if(param == "--globalwarming")
        {
            climate = true;
        }
    }

    // Initialize ncurses
    initscr();
    curs_set(0);
    getmaxyx(stdscr, yMax, xMax);

    // Initialize scene
    Brick::initScene(xMax, yMax);

    // Initialize all bricks...
    for(int i = 0; i < xMax; i++)
    {
        // ...with random descent rate in range 0 (slow) to 20 (fast)
        Brick brick(i, rand() % 21);
        bricks.push_back(brick);
    }

    // Start monitor
    std::thread monitor(refreshScreen);

    while(fallingBricks < xMax)
    {
        // Determine random brick...
        int randBrick = rand() % xMax;
        while(bricks.at(randBrick).isFalling())
        {
            // ...which still isn't falling down...
            randBrick = rand() % xMax;
        }

        // ...and launch it with nuclear-powered hammer ;-)
        brickThreads.push_back(bricks.at(randBrick).fallThread());
        fallingBricks++;

        // Random time in range 100 to 500 ms until next fall
        unsigned randTime = rand() % 5 + 1;
        usleep(100000 * randTime);
    }

    // Wait for all bricks
    for(int i = 0; i < brickThreads.size(); i++)
    {
        brickThreads.at(i).join();
    }

    // Stop monitor
    sleep(1);
    running = false;
    monitor.join();

    // Close ncurses
    endwin();

    std::cout << "BRIcks Caban Kernel-thread System v1.1" << std::endl;
    std::cout << "Jan Potocki 2018" << std::endl;
    std::cout << "(beerware)" << std::endl;
    std::cout << std::endl;
    std::cout << '"' << "I had a Type-4 keyboard," << std::endl;
    std::cout << "Bought with my Sun workstation," << std::endl;
    std::cout << "Hacked on it 'til my fingers bled." << std::endl;
    std::cout << "Was the winter of '95..." << '"' << std::endl;

    // Easter egg (3)
    if(climate)
    {
        std::cout << std::endl;
        std::cout << "SEVERE WEATHER ALERT: major snowfall predicted in 48h forecast for Lower Silesia, south-western Poland" << std::endl;
        std::cout << "Global warming affecting again!... ;-)" << std::endl;
    }
    else
    {
        std::cout << "Beware of BRICKS! ;-)" << std::endl;
    }

    return 0;
}
