#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <SFML/Graphics.hpp>

#include "SpriteInfo.h"

class SpriteSheet
{
    public:
        SpriteSheet(SpriteInfo& info, sf::Vector2f pos = sf::Vector2f(0.f, 0.f));
        virtual ~SpriteSheet();

        void update();
        virtual void draw(sf::RenderTarget& target);

        // Mutator
        void setRenderPosition(sf::Vector2f pos){mRenderPosition=pos; mSprite.setPosition(pos);}
        void setFrameLoop(int start, int stop, bool loop=true);

        // Accessor
        sf::Sprite& getSprite(){return mSprite;}
        sf::Vector2f getRenderPosition(){return mRenderPosition;}

        unsigned int mLayer;
        bool mVisible;
        sf::Vector2f mRenderPosition;

    protected:
        sf::Sprite mSprite;

        int mCurrentFrame;
        sf::Clock mAnimClock;
        float mFrameDelay;
        bool mLoopAnim;
        int mStartFrame;
        int mEndFrame;
        int mFrameDir;

        int mFramesPerRow;
        sf::Vector2f mFrameDim;
};

#endif // SPRITEOBJECT_H
