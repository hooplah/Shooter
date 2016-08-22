#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "CollisionObject.h"
#include "CollisionResolver.h"

class Context;
class GameObject;

class World
{
    public:
        World(Context& context);
        virtual ~World();

        virtual void update(Context& context, sf::Time dt);

        void addGameObject(std::unique_ptr<GameObject> object) { mGameObjects.push_back(std::move(object)); }

        std::size_t getTick() { return mTick; }

    protected:
        std::vector<std::unique_ptr<GameObject>> mGameObjects;

    private:
        std::size_t mTick;
};

#endif // WORLD_H
