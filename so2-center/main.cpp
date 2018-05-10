#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <ncurses.h>
#include <unistd.h>
#include "Entry.h"

bool running = true;
std::vector<Entry> entries;

std::mutex display;

// "Monitor" function
void refreshScreen()
{
    while(running == true)
    {
        clear();

        for(int i = 0; i < entries.size(); i++)
        {
            mvprintw(entries[i].getyPosition(), entries[i].getxPosition(), entries[i].getSymbol().c_str());
        }

        refresh();

        // Refresh every 0.01 s
        usleep(10000);
    }
}

int main()
{
    int xMax, yMax, fallingBricks = 0;
    std::vector<std::thread> entriesThreads;

    srand(time(0));

    // Initialize ncurses
    initscr();
    curs_set(0);
    getmaxyx(stdscr, yMax, xMax);

    // Initialize scene
    Entry::initScene(xMax, yMax);

    // Start monitor
    std::thread monitor(refreshScreen);


    for(int i = 0; i < 15; i++)
    {
        entries.push_back(*(new Entry(rand() % 6)));
    }

    for(int i = 0; i < entries.size(); i++)
    {
        unsigned randTime = rand() % 3 + 1;
        sleep(1 * randTime);
        entriesThreads.push_back(entries[i].runThread());
    }

    // Wait for all entries
    for(int i = 0; i < entriesThreads.size(); i++)
    {
        entriesThreads.at(i).join();
    }

    // Stop monitor
    sleep(1);
    running = false;
    monitor.join();

    // Close ncurses
    endwin();

    std::cout << "SYncsys Next Caban SYStem v1.1" << std::endl;
    std::cout << "Jan Potocki 2018" << std::endl;
    std::cout << "(beerware)" << std::endl;
    std::cout << std::endl;
    std::cout << '"' << "...And now the times have changed" << std::endl;
    std::cout << "Repos on the web, git," << std::endl;
    std::cout << "Now githubs everywhere." << std::endl;
    std::cout << "Not like the winter of '95..." << '"' << std::endl;

    return 0;
}
