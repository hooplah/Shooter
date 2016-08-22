#include "ServerPlayer.h"

#include "Context.h"
#include "EntityTags.h"

std::unique_ptr<GameObject> createServerPlayer(Context& context, SpriteInfo& info, sf::Vector2f pos)
{
    CollisionObjectId col = context.collisionResolver.addCollisionObject(CollisionObject(info.mHitBox, EntityTags::PLAYER));

    std::unique_ptr<ServerPlayer> player = std::make_unique<ServerPlayer>(info, col);

    return std::move(player);
}

ServerPlayer::ServerPlayer(SpriteInfo& sprite, CollisionObjectId colObj) : Player(sprite, colObj)
{
    //ctor
}

ServerPlayer::~ServerPlayer()
{
    //dtor
}

void ServerPlayer::update(Context& context, sf::Time dt)
{
    mInputHistory.push_front(mInputHistory.front().next());
    tick(context, dt);
}

void ServerPlayer::handlePacket(Packet& packet)
{
}
