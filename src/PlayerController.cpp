#include "PlayerController.h"

PlayerController::PlayerController()
{
    //ctor
}

PlayerController::~PlayerController()
{
    //dtor
}

void PlayerController::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::A)
            mInput.left = true;
        else if (event.key.code == sf::Keyboard::D)
            mInput.right = true;
        else if (event.key.code == sf::Keyboard::W)
            mInput.jump = true;
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::A)
            mInput.left = false;
        else if (event.key.code == sf::Keyboard::D)
            mInput.right = false;
    }
}

void PlayerController::update()
{
    mInput = mInput.next();
}
