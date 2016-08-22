#include "World.h"

#include "Assets.h"
#include "Context.h"
#include "EntityTags.h"
#include "Player.h"

#include <iostream>

World::World(Context& context) : mTick(0)
{
    /*auto player = createPlayer(context, Assets::sprites["ammocrate"], sf::Vector2f());

    mGameObjects.push_back(std::move(player));*/
}

World::~World()
{
    //dtor
}

void World::update(Context& context, sf::Time dt)
{
    for (auto& gameObject : mGameObjects)
    {
        gameObject->update(context, dt);
    }

    context.collisionResolver.update(dt);

    mTick++;
}
