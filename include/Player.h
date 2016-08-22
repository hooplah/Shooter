#ifndef PLAYER_H
#define PLAYER_H

#include <tuple>
#include <deque>

#include "GameObject.h"
#include "CollisionResolver.h"
#include "Packet.h"
#include "SpriteInfo.h"
#include "World.h"

struct PlayerInput
{
    PlayerInput() : left(false), right(false), jump(false) { }
    PlayerInput(bool l, bool r, bool j) : left(l), right(r), jump(j) { }

    PlayerInput next()
    {
        return PlayerInput(left, right, false);
    }

    bool left;
    bool right;
    bool jump;
};

struct PlayerState
{
    CollisionObjectState bodyState;
};

class Player : public GameObject
{
    public:
        Player(SpriteInfo& sprite, CollisionObjectId colObj);
        ~Player();

        Player(Context& context, Packet& packet);
        virtual void serialize(Context& context, Packet& packet);

        void handleInput(Context& context, const PlayerInput& input);
        void tick(Context& context, sf::Time dt);
        virtual void rewindTicks(Context& context, std::size_t tick);
        virtual void playTick(Context& context, std::size_t ticksBack);

    protected:
        std::string mSpriteInfoName;
        CollisionObjectId mCollisionObject;

        float mJumpSpeed;
        float mRunSpeed;

        std::deque<PlayerInput> mInputHistory; // Most recent first
        std::deque<PlayerState> mStateHistory; // Most recent first
};

#endif // PLAYER_H
