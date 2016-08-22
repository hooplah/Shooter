#include "ClientPlayer.h"

#include "Assets.h"
#include "Context.h"
#include "EntityTags.h"

std::unique_ptr<GameObject> createClientPlayer(Context& context, SpriteInfo& info, sf::Vector2f pos)
{
    SpriteId sprite = context.spriteManager.addSprite(SpriteSheet(info, pos));
    CollisionObjectId col = context.collisionResolver.addCollisionObject(CollisionObject(info.mHitBox, EntityTags::PLAYER));

    std::unique_ptr<ClientPlayer> player = std::make_unique<ClientPlayer>(info, sprite, col);

    return std::move(player);
}

ClientPlayer::ClientPlayer(SpriteInfo& spriteInfo, SpriteId sprite, CollisionObjectId colObj) : Player(spriteInfo, colObj),
    mSprite(sprite)
{
    //ctor
}

ClientPlayer::~ClientPlayer()
{
    //dtor
}

ClientPlayer::ClientPlayer(Context& context, Packet& packet) : Player(context, packet),
    mSprite(context.spriteManager.addSprite(SpriteSheet(Assets::sprites[mSpriteInfoName])))
{
    context.spriteManager.getSpriteSheet(mSprite).mRenderPosition = context.collisionResolver.getCollisionObject(mCollisionObject).mPosition;
}

void ClientPlayer::update(Context& context, sf::Time dt)
{
    mInputHistory.push_front(context.playerController.getInput());
    tick(context, dt);

    context.spriteManager.getSpriteSheet(mSprite).mRenderPosition = context.collisionResolver.getCollisionObject(mCollisionObject).mPosition;
}

void ClientPlayer::handlePacket(Packet& packet)
{
}
