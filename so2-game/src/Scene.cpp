#include "Scene.h"
#include <unistd.h>

int Scene::xMax;
int Scene::yMax;
int Scene::points = 0;
bool Scene::initialized = false;
bool Scene::freezed = false;
bool Scene::running = false;
std::mutex Scene::ncursesMutex;
std::mutex Scene::freezeMutex;
std::condition_variable Scene::freezeCondition;

Scene::Scene()
{
    //ctor
}

Scene::~Scene()
{
    //dtor
}

void Scene::init(int xRes, int yRes)
{
    xMax = xRes;
    yMax = yRes;
    running = true;
    initialized = true;
}

int Scene::getPoints()
{
    return points;
}

bool Scene::isFreezed()
{
    return freezed;
}

void Scene::freeze()
{
    const int idleSeconds = 10;

    std::unique_lock<std::mutex> freezeLock(freezeMutex);
    freezed = true;
    sleep(idleSeconds);

//    // This must be interruptable, so it can't be just sleep(idleSeconds)
//    for(int i = 0; i < idleSeconds * 10; i++)
//    {
//        if(running)
//        {
//            // Every tick = 100 ms
//            usleep(100000);
//        }
//        else
//        {
//            break;
//        }
//    }

    freezed = false;
    freezeCondition.notify_all();
}

void Scene::terminateAll()
{
    Scene::running = false;
}
