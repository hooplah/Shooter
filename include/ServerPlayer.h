#ifndef SERVERPLAYER_H
#define SERVERPLAYER_H

#include "Player.h"
#include "SpriteInfo.h"

class ServerPlayer : public Player
{
    public:
        ServerPlayer(SpriteInfo& spriteInfo, CollisionObjectId colObj);
        ~ServerPlayer();

        virtual void update(Context& context, sf::Time dt);

        virtual void handlePacket(Packet& packet);

    private:
};

std::unique_ptr<GameObject> createServerPlayer(Context& context, SpriteInfo& info, sf::Vector2f pos);

#endif // SERVERPLAYER_H
