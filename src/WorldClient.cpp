#include "WorldClient.h"

#include "Context.h"

WorldClient::WorldClient(Context& context) : World(context)
{
    //ctor
}

WorldClient::~WorldClient()
{
    //dtor
}

void WorldClient::handleEvent(sf::Event& event)
{
    //mPlayer->handleEvents(event);
}

void WorldClient::update(Context& context, sf::Time dt, ShooterClient& client)
{
    World::update(context, dt);

    for (auto& gameObject : mGameObjects)
    {
        for (auto& packet : gameObject->getPacketsToSend())
        {
            client.send(packet);
        }
    }

    context.spriteManager.update(dt);
}

void WorldClient::draw(Context& context, sf::RenderTarget& target)
{
    context.spriteManager.draw(target);
}
