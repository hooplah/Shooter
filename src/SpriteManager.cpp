#include "SpriteManager.h"

SpriteManager::SpriteManager()
{
    //ctor
}

SpriteManager::~SpriteManager()
{
    //dtor
}

void SpriteManager::update(sf::Time dt)
{
    for (auto& spr : mSpriteSheets)
    {
        spr.update();
    }
}

void SpriteManager::draw(sf::RenderTarget& target)
{
    for (auto& spr : mSpriteSheets)
    {
        spr.draw(target);
    }
}
