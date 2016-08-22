#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "SpriteSheet.h"

typedef std::size_t SpriteId;

class SpriteManager
{
    public:
        SpriteManager();
        ~SpriteManager();

        void update(sf::Time dt);
        void draw(sf::RenderTarget& target);

        SpriteId addSprite(SpriteSheet sprite) { mSpriteSheets.push_back(sprite); return mSpriteSheets.size()-1; }
        SpriteSheet& getSpriteSheet(SpriteId id) { return mSpriteSheets[id]; }

    private:
        std::vector<SpriteSheet> mSpriteSheets;
};

#endif // SPRITEMANAGER_H
