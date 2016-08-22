#ifndef WORLDSERVER_H
#define WORLDSERVER_H

#include <memory>

#include "GameObject.h"
#include "ShooterServer.h"
#include "World.h"

class WorldServer : public World
{
    public:
        WorldServer(Context& context);
        virtual ~WorldServer();

        virtual void update(Context& context, sf::Time dt, ShooterServer& server);

    private:
};

#endif // WORLDSERVER_H
