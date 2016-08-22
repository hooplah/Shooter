#ifndef COLLISIONOBJECT_H
#define COLLISIONOBJECT_H

#include <SFML/Graphics.hpp>

struct CollisionObjectState
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool grounded;
};

class CollisionObject
{
    public:
        CollisionObject(sf::FloatRect hitbox, std::size_t tag, bool _static=false);
        virtual ~CollisionObject();

        virtual void update(sf::Time dt);

        CollisionObjectState getState();
        void setState(CollisionObjectState& state);

        sf::Vector2f getVelocity(){return mVelocity;}
        sf::FloatRect getHitBox(){return mHitBox;}
        std::size_t getTag(){return mTag;}
        bool isStatic(){return mStatic;}
        bool isGrounded(){return mGrounded;}

        void setVelocity(sf::Vector2f vel){mVelocity=vel;}
        void setHitBox(sf::FloatRect hitbox){mHitBox=hitbox;}
        void setTag(std::size_t tag){mTag=tag;}
        void setStatic(bool s){mStatic=s;}

        sf::Vector2f mPosition;
        sf::Vector2f mVelocity;

    protected:
        sf::FloatRect mHitBox;

        std::size_t mTag;
        bool mStatic;

        bool mGrounded;
};

#endif // COLLISIONOBJECT_H
