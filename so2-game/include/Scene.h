#ifndef SCENE_H
#define SCENE_H

#include <condition_variable>
#include <mutex>
#include <thread>

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        //static int GetyMax() { return yMax; }
        //void SetyMax(static int val) { yMax = val; }
    protected:
    private:
        static bool initialized;
        static bool freezed;
        static std::mutex freezeMutex;
        static std::condition_variable freezeCondition;
        static int xMax;
        static int yMax;
};

#endif // SCENE_H
