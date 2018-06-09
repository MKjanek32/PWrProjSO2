#ifndef SCENE_H
#define SCENE_H


class Scene
{
    public:
        Scene();
        virtual ~Scene();
        static int GetxMax() { return xMax; }
        void SetxMax(static int val) { xMax = val; }
        static int GetyMax() { return yMax; }
        void SetyMax(static int val) { yMax = val; }
    protected:
    private:
        static int xMax;
        static int yMax;
};

#endif // SCENE_H
