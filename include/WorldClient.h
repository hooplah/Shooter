#ifndef WORLDCLIENT_H
#define WORLDCLIENT_H

#include <memory>

#include "GameObject.h"
#include "ShooterClient.h"
#include "World.h"

class WorldClient : public World
{
    public:
        WorldClient(Context& context);
        virtual ~WorldClient();

        void handleEvent(sf::Event& event);
        virtual void update(Context& context, sf::Time dt, ShooterClient& client);
        void draw(Context& context, sf::RenderTarget& target);

    private:
};

#endif // WORLDCLIENT_H
