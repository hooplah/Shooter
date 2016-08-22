#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(SpriteInfo& info, sf::Vector2f pos) :
    mLayer(0), mVisible(true),
    mCurrentFrame(0), mFrameDelay(100.f), mLoopAnim(true), mStartFrame(0), mEndFrame(0), mFrameDir(1),
    mFramesPerRow(info.mFramesPerRow), mFrameDim(info.mFrameDim)
{
    mSprite = sf::Sprite(info.mTexture);
    mRenderPosition = pos;
}

SpriteSheet::~SpriteSheet()
{
    //dtor
}

void SpriteSheet::update()
{
    mSprite.setPosition(mRenderPosition);
}

void SpriteSheet::draw(sf::RenderTarget& target)
{
    if (!mVisible)
        return;

    if (mAnimClock.getElapsedTime().asMilliseconds() >= mFrameDelay &&
            (mLoopAnim || (mFrameDir == 1 && mCurrentFrame != mEndFrame) || (mFrameDir == -1 && mCurrentFrame != mStartFrame)))
    {
        mAnimClock.restart();
        mCurrentFrame += mFrameDir;

        if (mCurrentFrame > mEndFrame && mFrameDir == 1 && mLoopAnim)
            mCurrentFrame = mStartFrame;
        else if (mCurrentFrame < mStartFrame && mFrameDir == -1 && mLoopAnim)
            mCurrentFrame = mEndFrame;
    }

    // Calculate frame position
    if (mFramesPerRow > 1)
    {
        int frameX = (mCurrentFrame%mFramesPerRow)*mFrameDim.x;
        int frameY = (mCurrentFrame/mFramesPerRow)*mFrameDim.y;

        mSprite.setTextureRect(sf::IntRect(frameX, frameY, mFrameDim.x, mFrameDim.y));
    }

    // Stop here
    //*****************************************************************************************
    target.draw(mSprite); // Rendahhh!!!!
}

void SpriteSheet::setFrameLoop(int start, int stop, bool loop)
{
    mLoopAnim = loop;

    if (start == mStartFrame && stop == mEndFrame)
        return;

    if (start <= stop)
    {
        mStartFrame = start;
        mEndFrame = stop;
        mCurrentFrame = start;
        mFrameDir = 1;
    }
    else
    {
        mStartFrame = stop;
        mEndFrame = start;
        mCurrentFrame = start;
        mFrameDir = -1;
    }
}
