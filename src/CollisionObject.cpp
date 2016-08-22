#include "CollisionObject.h"

CollisionObject::CollisionObject(sf::FloatRect hitbox, std::size_t tag, bool _static) :
    mHitBox(hitbox),
    mTag(tag),
    mStatic(_static),
    mGrounded(false)
{
    //ctor
}

CollisionObject::~CollisionObject()
{
    //dtor
}

void CollisionObject::update(sf::Time dt)
{
    mPosition += mVelocity*dt.asSeconds();
}

CollisionObjectState CollisionObject::getState()
{
    CollisionObjectState state;
    state.position = mPosition;
    state.velocity = mVelocity;
    state.grounded = mGrounded;

    return state;
}

void CollisionObject::setState(CollisionObjectState& state)
{
    mPosition = state.position;
    mVelocity = state.velocity;
    mGrounded = state.grounded;
}
