#include "AnimationMenuItem.h"

AnimationMenuItem::~AnimationMenuItem()
{
    if(selection)
    {
        delete selection;
        selection = NULL;
    }
}

Vector2di AnimationMenuItem::getDimensions(){return Vector2di(anim.getWidth(),anim.getHeight());}

void AnimationMenuItem::init()
{
    setType(MENU_ANIM_ITEM);
    anim.setFrameRate(FIFTEEN_FRAMES);
    anim.setLooping(true);
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
    selection = NULL;
}

PENJIN_ERRORS AnimationMenuItem::loadFrame(CRstring fileName){return anim.loadFrame(fileName);}
PENJIN_ERRORS AnimationMenuItem::loadFrames(CRstring fileName,CRuint xTiles,CRuint yTiles){return anim.loadFrames(fileName,xTiles,yTiles);}
PENJIN_ERRORS AnimationMenuItem::loadSelectionFrames(CRstring fileName,CRuint xTiles,CRuint yTiles)
{
    if(!selection)
    {
        selection = NULL;
        selection = new AnimatedSprite;
    }
    return selection->loadFrames(fileName, xTiles, yTiles);
}

PENJIN_ERRORS AnimationMenuItem::loadSelectionFrame(CRstring fileName)
{
    if(!selection)
    {
        selection = NULL;
        selection = new AnimatedSprite;
    }
    return selection->loadFrame(fileName);
}

void AnimationMenuItem::update()
{
    #ifndef PENJIN_3D
        Vector2di Offset(horizontalOffset,0);
    #else
        Vector3df Offset(horizontalOffset,0.0f,0.0f);
    #endif
    anim.setPosition(position + Offset);
    anim.update();

    if(selection)
    {
        selection->setPosition(position + Offset);
        selection->update();
    }
}

#ifdef PENJIN_SDL
    void AnimationMenuItem::render(SDL_Surface* screen)
    {
        if(!isSelected)
            anim.render(screen);
        else if(selection && isSelected)
        {
            selection->setPosition(position);
            selection->render(screen);
        }
    }

    void AnimationMenuItem::setUseHardware(CRbool use)
    {
        anim.setUseHardware(use);
        if(selection)
            selection->setUseHardware(use);
    }
#else
    void AnimationMenuItem::render()
    {
        if(!isSelected)
            anim.render();
        else if(selection && isSelected)
        {
            selection->setPosition(position);
            selection->render();
        }
    }
#endif
