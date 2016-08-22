#include "WorldServer.h"

WorldServer::WorldServer(Context& context) : World(context)
{
    //ctor
}

WorldServer::~WorldServer()
{
    //dtor
}

void WorldServer::update(Context& context, sf::Time dt, ShooterServer& server)
{
    World::update(context, dt);

    for (auto& gameObject : mGameObjects)
    {
        for (auto& packet : gameObject->getPacketsToSend())
        {
            server.send(packet, gameObject->getId());
        }
    }
}
