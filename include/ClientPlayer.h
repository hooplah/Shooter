#ifndef CLIENTPLAYER_H
#define CLIENTPLAYER_H

#include "Player.h"
#include "SpriteManager.h"

class ClientPlayer : public Player
{
    public:
        ClientPlayer(SpriteInfo& spriteInfo, SpriteId sprite, CollisionObjectId colObj);
        ~ClientPlayer();

        ClientPlayer(Context& context, Packet& packet);

        virtual void update(Context& context, sf::Time dt);

        virtual void handlePacket(Packet& packet);

    private:
        SpriteId mSprite;
};

std::unique_ptr<GameObject> createClientPlayer(Context& context, SpriteInfo& info, sf::Vector2f pos);

#endif // CLIENTPLAYER_H
