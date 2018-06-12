#ifndef SCENE_H
#define SCENE_H

#include <condition_variable>
#include <mutex>
#include <thread>

class Scene
{
    public:
        static std::mutex ncursesMutex;
        static std::mutex freezeMutex;
        static std::condition_variable freezeCondition;
        Scene();
        virtual ~Scene();
        static void init(int xRes, int yRes);
        static int getPoints();
        static bool isFreezed();
        static void terminateAll();
    protected:
        static int xMax;
        static int yMax;
        static int points;
        static bool initialized;
        static bool freezed;
        static bool running;
        static void freeze();
    private:
};

#endif // SCENE_H
