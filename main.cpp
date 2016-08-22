#include <time.h>
#include <stdlib.h>

#include <SFML/Graphics.hpp>

#include "Assets.h"
#include "Context.h"
#include "WorldClient.h"
#include "ShooterClient.h"

int main()
{
    srand(time(NULL));

    Assets::loadAssets();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer");

    Context context;
    ShooterClient client("localhost", 30000);
    WorldClient world(context);

    sf::Clock clock;
    sf::Time timeAccumulator = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f/60.f);

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        timeAccumulator += dt;

        client.update(context, world);

        while (timeAccumulator > timePerFrame)
        {
            timeAccumulator -= timePerFrame;

            context.playerController.update();

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                }

                context.playerController.handleEvent(event);
            }

            world.update(context, timePerFrame, client);
        }

        window.clear(sf::Color::Black);
        world.draw(context, window);
        window.display();
    }

    return 0;
}
