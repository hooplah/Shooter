#include <time.h>
#include <stdlib.h>

#include "Assets.h"
#include "Context.h"
#include "WorldServer.h"
#include "ShooterServer.h"

int main()
{
    srand(time(NULL));

    Assets::loadAssets();

    Context context;
    ShooterServer server;
    WorldServer world(context);

    sf::Clock clock;
    sf::Time timeAccumulator = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f/60.f);

    while (true)
    {
        sf::Time dt = clock.restart();
        timeAccumulator += dt;

        server.update(context, world);

        while (timeAccumulator > timePerFrame)
        {
            timeAccumulator -= timePerFrame;

            world.update(context, timePerFrame, server);
        }
    }

    return 0;
}
