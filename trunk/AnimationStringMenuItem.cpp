#include "AnimationStringMenuItem.h"

AnimationStringMenuItem::~AnimationStringMenuItem()
{

}

void AnimationStringMenuItem::init()
{
    setType(MENU_ANIM_STRING_ITEM);
    position.x = 0;
    position.y = 0;
    #ifdef PENJIN_3D
        position.z = 0.0f;
    #endif
    dimensions.x = 0;
    dimensions.y = 0;
    isSelected = false;
    isSelectable = true;
    verticalSpacing = 0;
    horizontalOffset = 0;
    setSelectionIndicator('-');
    anim.setFrameRate(FIFTEEN_FRAMES);
    anim.setLooping(true);
    anim.setHorizontalOffset(horizontalOffset);
    text.setHorizontalOffset(horizontalOffset);
}

void AnimationStringMenuItem::update()
{
    anim.setIsSelected(isSelected);
    anim.update();

    text.setIsSelected(isSelected);
    text.update();
}

#ifdef PENJIN_SDL
    void AnimationStringMenuItem::render(SDL_Surface* screen)
    {
        anim.render(screen);
        text.render();
    }
#else
    void AnimationStringMenuItem::render()
    {
        anim.render();
        text.render();
    }
#endif

Vector2di AnimationStringMenuItem::getDimensions()
{
    Vector2di dims = anim.getDimensions();
    Vector2di txtDims = text.getDimensions();

    if(dims.x >= txtDims.x)
        dimensions.x = dims.x;
    else
        dimensions.x = txtDims.x;

    if(dims.y >= txtDims.y)
        dimensions.y = dims.y;
    else
        dimensions.y = txtDims.y;

    return dimensions;
}

PENJIN_ERRORS AnimationStringMenuItem::loadSelectionFrames(CRstring fileName,CRuint xTiles,CRuint yTiles){return anim.loadSelectionFrames(fileName, xTiles, yTiles);}
PENJIN_ERRORS AnimationStringMenuItem::loadSelectionFrame(CRstring fileName){return anim.loadSelectionFrame(fileName);}

#ifndef PENJIN_3D
    void AnimationStringMenuItem::setPosition(const Vector2df& pos)
    {
        position = pos;
        anim.setPosition(pos);
        text.setPosition(pos);
    }
#else
    void AnimationStringMenuItem::setPosition(const Vector3df& pos)
    {
        position = pos;
        anim.setPosition(pos);
        text.setPosition(pos);
    }
#endif

void AnimationStringMenuItem::centreText(CRint corr)
{
    /// Get the difference of the text and the animFrame
    Vector2di diff = text.getDimensions()-anim.getDimensions();
    diff = diff*0.5f;
    #ifdef PENJIN_3D
        text.setPosition(Vector3df(diff.x+corr,diff.y,0.0f));
    #else
        text.setPosition(Vector2df(diff.x+corr,diff.y));
    #endif
}

