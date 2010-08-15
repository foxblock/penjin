#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{
	currentFrame = 0;
	animationTimer.setMode(THIRTY_FRAMES);
    numLoops = -1;
	animationTimer.start();
	position.x = 0;
	position.y = 0;
	#ifdef PENJIN_SDL
        screen = GFX::getVideoSurface();
    #endif
    #ifdef PENJIN_3D
        position.z = 0.0f;
    #endif

    playReversed = false;
	reachedEnd = false;
}
#ifdef PENJIN_SDL
    AnimatedSprite::AnimatedSprite(CRint x,CRint y)
    {
        currentFrame = 0;
        animationTimer.setMode(THIRTY_FRAMES);
        numLoops = firstLoops = -1;
        animationTimer.start();
        playReversed = false;
        reachedEnd = false;
        screen = GFX::getVideoSurface();
    }
#else
    AnimatedSprite::AnimatedSprite(CRfloat x,CRfloat y)
    {
        currentFrame = 0;
        animationTimer.setMode(THIRTY_FRAMES);
        numLoops = -1;
        animationTimer.start();
        position.x = x;
        position.y = y;
        #ifdef PENJIN_3D
            position.z = 0.0f;
        #endif
        playReversed = false;
        reachedEnd = false;
    }
    #ifdef PENJIN_3D
    AnimatedSprite::AnimatedSprite(CRfloat x,CRfloat y,CRfloat z)
    {
        currentFrame = 0;
        animationTimer.setMode(THIRTY_FRAMES);
        numLoops = -1;
        animationTimer.start();
        position.x = x;
        position.y = y;
        position.z = z;
        playReversed = false;
        reachedEnd = false;
    }
    #endif
#endif

/*
bool AnimatedSprite::hasCollided(AnimatedSprite &spr)
{
   uint a = image.getWidth()/2;
   uint b = spr.image.getWidth()/2;

   IntVector2d temp = *this - IntVector2d(spr.getX(),spr.getY());

	if (temp.lengthSquared() <= a * a + b * b)
	 	return true;

	return false;
}
*/

/*PENJIN_ERRORS AnimatedSprite::setTransparentColour(const Colour& c)
{
    PENJIN_ERRORS error = PENJIN_ERROR;
    for(int i = image.size()-1; i>= 0; --i)
    {
        error = image.setTransparentColour(i,c);
        if(error != PENJIN_OK)
            return error;
    }
    return PENJIN_OK;
}
*/
PENJIN_ERRORS AnimatedSprite::setTransparentColour(const Vector2di& v)
{
    PENJIN_ERRORS error = PENJIN_ERROR;
    for(int i = image.size()-1; i>= 0; --i)
    {
        error = image.setTransparentColour(i,v);
        if(error != PENJIN_OK)
            return error;
    }
    return PENJIN_OK;
}

PENJIN_ERRORS AnimatedSprite::loadFrame(SDL_Surface* s)
{
    #ifdef PENJIN_SDL
        image.loadImage(s);
        return PENJIN_OK;
    #elif PENJIN_ES
        return PENJIN_FUNCTION_IS_STUB;
    #else
        return PENJIN_FUNCTION_IS_STUB;
    #endif
}

PENJIN_ERRORS AnimatedSprite::loadFrame(CRstring fileName){return image.loadImage(fileName);}

PENJIN_ERRORS AnimatedSprite::loadFrames(CRstring fileName,CRuint xTiles,CRuint yTiles){image.clear();return image.loadImageSheet(fileName, xTiles, yTiles);}

PENJIN_ERRORS AnimatedSprite::loadFrames(SDL_Surface* s,CRuint xTiles,CRuint yTiles,CRuint skipTiles,CRuint numTiles,CRbool transparent)
{
    image.clear();
    if (transparent)
        return image.loadImageSheet(s, xTiles, yTiles, skipTiles, numTiles);
    else
        return image.loadImageSheetNoKey(s, xTiles, yTiles, skipTiles, numTiles);
}

#ifdef PENJIN_SDL
    void AnimatedSprite::render(SDL_Surface *screen){image.renderImage(currentFrame,screen,position);}
#else
    void AnimatedSprite::render(){image.renderImage(currentFrame, position);}
#endif

void AnimatedSprite::update()
{
	if(!playReversed)
	{
    	if(animationTimer.getScaledTicks() >= 1)
        {
            animationTimer.start();
            ++currentFrame;
        }
        int size = image.size()-1;
        if((int)currentFrame > size)
        {
            if(numLoops == -1) {
                currentFrame = 0;
                reachedEnd = true;
            }
            else if( numLoops > 0)
            {
                currentFrame = 0;
                --numLoops;
            }
            else
                currentFrame = size;
        }
	}
	else
	{
	    if(!reachedEnd)
	    {
            if(animationTimer.getScaledTicks() >= 1)
            {
                currentFrame++;
                animationTimer.start();
            }
            int size = image.size()-1;
            if((int)currentFrame > size)
            {
                    currentFrame = size;
                    reachedEnd = true;
            }
	    }
	    else
	    {
            if(animationTimer.getScaledTicks() >= 1)
            {
                animationTimer.start();
                --currentFrame;
            }
            if(currentFrame <= 0)
            {
                if(numLoops == -1)
                    currentFrame = 0;
                else if( numLoops > 0)
                {
                    currentFrame = 0;
                    --numLoops;
                }
                reachedEnd = false;
            }
	    }
	}
}

