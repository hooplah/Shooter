#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <SFML/Window/Event.hpp>

#include "Player.h"

class PlayerController
{
    public:
        PlayerController();
        ~PlayerController();

        void handleEvent(const sf::Event& event);

        void update();

        const PlayerInput& getInput() { return mInput; }

    private:
        PlayerInput mInput;
};

#endif // PLAYERCONTROLLER_H
