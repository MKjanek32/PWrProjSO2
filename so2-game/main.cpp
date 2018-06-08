#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <ncurses.h>
#include <unistd.h>
#include "Brick.h"
#include "Platform.h"
#include "Stopwatch.h"

int xMax, yMax;
bool running = true, climate = false;
std::vector<Brick> bricks;
Platform platform;
Stopwatch gameClock;

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
                    attron(COLOR_PAIR(bricks[i].getColor()));
                    mvprintw(bricks[i].getyPosition(), bricks[i].getxPosition(), "*");
                    attroff(COLOR_PAIR(bricks[i].getColor()));
                }
            else
                {
                    attron(COLOR_PAIR(bricks[i].getColor()));
                    mvprintw(bricks[i].getyPosition(), bricks[i].getxPosition(), "#");
                    attroff(COLOR_PAIR(bricks[i].getColor()));
                }
        }

        attron(COLOR_PAIR(platform.getColor()));
        mvprintw(yMax - 2, platform.getPosition(), platform.getSprite());
        attroff(COLOR_PAIR(platform.getColor()));

        mvprintw(yMax - 1, 0, "%.3f", gameClock.read());
        mvprintw(yMax - 1, xMax - 3, "%.3d", Brick::getPoints());

        refresh();

        // Refresh every 0.01 s
        usleep(10000);
    }
}

int main(int argc, char *argv[])
{
    int fallingBricks = 0;
    std::vector<std::thread> brickThreads;
    //Stopwatch clock;

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

    // Initialize colors
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);

    // Non-blocking input for platform-movement
    //timeout(0);

    // Initialize scene
    Brick::initScene(xMax, yMax, &platform);
    Platform::initScene(xMax);

    // Initialize all bricks...
    for(int i = 0; i < xMax; i++)
    {
        // ...with random descent rate in range 0 (slow) to 15 (fast)
        Brick brick(i, rand() % 16);
        bricks.push_back(brick);
    }

    // Start monitor
    std::thread monitor(refreshScreen);

    // Start platform treads
    std::thread platformMover(platform.moveKeyThread());
    std::thread platformColorChanger(platform.colorChangeThread());

    // Start game
    gameClock.start();

    while(gameClock.read() < 60)
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

        // Random time in range 1000 to 2000 ms until next fall
        unsigned randTime = rand() % 10 + 10;
        usleep(100000 * randTime);
    }

    // Wait for all bricks
    for(int i = 0; i < brickThreads.size(); i++)
    {
        brickThreads.at(i).join();
    }

    // Stop platform threads
    platform.terminateThreads();
    platformMover.join();
    platformColorChanger.join();

    // Stop monitor
    sleep(1);
    running = false;
    monitor.join();

    // Stop clock
    gameClock.stop();

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
