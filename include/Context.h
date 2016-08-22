#ifndef CONTEXT_H
#define CONTEXT_H

#include "SpriteManager.h"
#include "CollisionResolver.h"
#include "PlayerController.h"

struct Context
{
    SpriteManager spriteManager;
    CollisionResolver collisionResolver;
#ifdef SHOOTER_CLIENT
    PlayerController playerController;
#endif
};

#endif // CONTEXT_H
