#include "Player.h"

#include "Assets.h"
#include "Context.h"
#include "EntityTags.h"

Player::Player(SpriteInfo& sprite, CollisionObjectId colObj) : mSpriteInfoName(sprite.mName), mCollisionObject(colObj),
    mJumpSpeed(500.f), mRunSpeed(500.f)
{
    //ctor
}

Player::~Player()
{
    //dtor
}

Player::Player(Context& context, Packet& packet)
{
    packet >> mSpriteInfoName;

    SpriteInfo& info = Assets::sprites[mSpriteInfoName];
    mCollisionObject = context.collisionResolver.addCollisionObject(CollisionObject(info.mHitBox, EntityTags::PLAYER));
    auto& colObj = context.collisionResolver.getCollisionObject(mCollisionObject);

    packet >> colObj.mPosition;
    packet >> colObj.mVelocity;
    packet >> mJumpSpeed;
    packet >> mRunSpeed;
}

void Player::serialize(Context& context, Packet& packet)
{
    auto& colObj = context.collisionResolver.getCollisionObject(mCollisionObject);
    packet << mSpriteInfoName;
    packet << colObj.mPosition;
    packet << colObj.mVelocity;
    packet << mJumpSpeed;
    packet << mRunSpeed;
}

void Player::handleInput(Context& context, const PlayerInput& input)
{
    auto& colObj = context.collisionResolver.getCollisionObject(mCollisionObject);

    if (input.jump /*&& colObj.isGrounded()*/)
    {
        colObj.mVelocity.y = -mJumpSpeed;
        //mGrounded = false;
    }

    if (input.left)
    {
        colObj.mVelocity.x = -mRunSpeed;
    }
    else if (input.right)
    {
        colObj.mVelocity.x = mRunSpeed;
    }
    else
    {
        colObj.mVelocity.x = 0.f;
    }
}

void Player::tick(Context& context, sf::Time dt)
{
    if (mInputHistory.size() > 100)
        mInputHistory.pop_back();

    handleInput(context, mInputHistory.front());
}

void Player::rewindTicks(Context& context, std::size_t ticksBack)
{
    auto& colObj = context.collisionResolver.getCollisionObject(mCollisionObject);

    colObj.setState(mStateHistory[ticksBack].bodyState);
}

void Player::playTick(Context& context, std::size_t ticksBack)
{
    handleInput(context, mInputHistory[ticksBack]);
}
