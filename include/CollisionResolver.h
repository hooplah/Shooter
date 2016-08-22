#ifndef COLLISIONRESOLVER_H
#define COLLISIONRESOLVER_H

#include <vector>
#include <memory>

#include "CollisionObject.h"

typedef std::size_t CollisionObjectId;

class CollisionResolver
{
    public:
        CollisionResolver();
        ~CollisionResolver();

        void update(sf::Time dt);

        bool checkCollision(CollisionObject& a, CollisionObject& b);
        void handleCollisions(CollisionObject& a, CollisionObject& b);
        void defaultCollision(CollisionObject& a, CollisionObject& b);

        CollisionObjectId addCollisionObject(CollisionObject colObj) { mCollisionObjects.push_back(colObj); return mCollisionObjects.size()-1; }
        CollisionObject& getCollisionObject(CollisionObjectId id) { return mCollisionObjects[id]; }

    private:
        std::vector<CollisionObject> mCollisionObjects;
};

#endif // COLLISIONRESOLVER_H
