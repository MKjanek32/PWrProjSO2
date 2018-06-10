#include "Scene.h"
#include <unistd.h>

int Scene::xMax;
int Scene::yMax;
int Scene::points = 0;
bool Scene::initialized = false;
bool Scene::freezed = false;
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
    initialized = true;
}

int Scene::getPoints()
{
    return points;
}

void Scene::freeze()
{
    std::unique_lock<std::mutex> freezeLock(freezeMutex);
    freezed = true;
    sleep(10);
    freezed = false;
    freezeCondition.notify_all();
}