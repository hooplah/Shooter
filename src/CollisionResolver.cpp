#include "CollisionResolver.h"

#include "EntityTags.h"

CollisionResolver::CollisionResolver()
{
    //ctor
}

CollisionResolver::~CollisionResolver()
{
    //dtor
}

void CollisionResolver::update(sf::Time dt)
{
    for (auto& col : mCollisionObjects)
    {
        col.update(dt);

        // apply gravity
        if (!col.isStatic())
            col.setVelocity(col.getVelocity() + sf::Vector2f(0.f, 400.f)*dt.asSeconds());
    }

    for (unsigned int i = 0; i < mCollisionObjects.size(); i++)
    {
        for (unsigned int j = 1; j < mCollisionObjects.size(); j++)
        {
            if (checkCollision(mCollisionObjects[i], mCollisionObjects[j]))
                handleCollisions(mCollisionObjects[i], mCollisionObjects[j]);
        }
    }
}

bool CollisionResolver::checkCollision(CollisionObject& a, CollisionObject& b)
{
    sf::Vector2f a1 = a.mPosition + sf::Vector2f(a.getHitBox().left, a.getHitBox().top);
    sf::Vector2f a2(a.getHitBox().width, a.getHitBox().height);

    sf::Vector2f b1 = b.mPosition + sf::Vector2f(b.getHitBox().left, b.getHitBox().top);
    sf::Vector2f b2(b.getHitBox().width, b.getHitBox().height);

    sf::FloatRect aRect(a1, a2);
    sf::FloatRect bRect(b1, b2);

    return aRect.intersects(bRect);
}

void CollisionResolver::handleCollisions(CollisionObject& a, CollisionObject& b)
{
    defaultCollision(a, b);
}

void CollisionResolver::defaultCollision(CollisionObject& a, CollisionObject& b)
{
    auto aLeft = a.mPosition.x + a.getHitBox().left;
    auto aTop = a.mPosition.y + a.getHitBox().top;
    auto aRight = aLeft + a.getHitBox().width;
    auto aBottom = aTop + a.getHitBox().height;

    auto bLeft = b.mPosition.x + b.getHitBox().left;
    auto bTop = b.mPosition.y + b.getHitBox().top;
    auto bRight = bLeft + b.getHitBox().width;
    auto bBottom = bTop + b.getHitBox().height;

    float overlapLeft {aRight - bLeft};
    float overlapRight {bRight - aLeft};
    float overlapTop {aBottom - bTop};
    float overlapBottom {bBottom - aTop};

    bool fromLeft(std::abs(overlapLeft) < std::abs(overlapRight));
    bool fromTop(std::abs(overlapTop) < std::abs(overlapBottom));

    float minOverlapX {fromLeft ? overlapLeft : overlapRight};
    float minOverlapY {fromTop ? overlapTop : overlapBottom};

    auto y_collision = [fromTop](CollisionObject& a, float overlapX, float overlapY, bool stair=false)
    {
        if (fromTop)
        {
            if (stair)
            {
                a.setVelocity(sf::Vector2f(a.getVelocity().x, 0.f));
                a.mPosition = a.mPosition - sf::Vector2f(5.f, overlapY);
            }
            else
            {
                a.setVelocity(sf::Vector2f(a.getVelocity().x, 0.f));
                a.mPosition.y -= overlapY;
            }
        }
        else if (!fromTop)
        {
            a.setVelocity(sf::Vector2f(a.getVelocity().x, 0.f));
            a.mPosition.y += overlapY;
        }
    };

    auto x_collision = [fromLeft, fromTop, y_collision](CollisionObject& a, float overlapX, float overlapY)
    {
        if (overlapY < 20.f && fromTop) // it's probably a stair
        {
            y_collision(a, overlapX, overlapY, true);
            return;
        }

        a.setVelocity(sf::Vector2f(0.f, a.getVelocity().y));

        if (fromLeft)
        {
            a.mPosition.x -= overlapX;
        }
        else if (!fromLeft)
        {
            a.mPosition.x += overlapX;
        }
    };

    //if (a.onContactBegin(b, fromLeft, fromTop) && b.onContactBegin(a, fromLeft, fromTop))
    {
        if (std::abs(minOverlapX) > std::abs(minOverlapY)) // y overlap
        {
            y_collision(a, minOverlapX, minOverlapY);
        }
        else if (std::abs(minOverlapX) < std::abs(minOverlapY)) // x overlap
        {
            x_collision(a, minOverlapX, minOverlapY);
        }

        //a.onContactEnd(b);
        //b.onContactEnd(a);
    }
}
