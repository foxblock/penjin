#include "Animation.h"

Animation::Animation()
{
	currentFrame = 0;
	animationTimer.setMode(THIRTY_FRAMES);
	numLoops = -1;
	firstLoops = -1;
    animationTimer.start();
	position.x = 0;
	position.y = 0;
	#ifdef PENJIN3D
        position.z = 0.0f;
	#endif
	playReversed = false;
	reachedEnd = false;
	#ifdef PENJIN_SDL
        screen = SDL_GetVideoSurface();
	#endif
}

PENJIN_ERRORS Animation::setTransparentColour(const Colour& c)
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

PENJIN_ERRORS Animation::setTransparentColour(const Vector2di& v)
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

PENJIN_ERRORS Animation::loadFrame(CRstring fileName)
{
    PENJIN_ERRORS result = image.loadImageNoKey(fileName);
    #ifdef PENJIN_SDL
    if(result == PENJIN_OK)
        image.setUseHardware(true);
    #endif
    return result;
}

PENJIN_ERRORS Animation::loadFrames(CRstring fileName,CRuint xTiles,CRuint yTiles)
{
    PENJIN_ERRORS t = image.loadImageSheetNoKey(fileName, xTiles, yTiles);
    #ifdef PENJIN_SDL
    if(t == PENJIN_OK)
        image.setUseHardware(true);
    #endif
    return t;
}


void Animation::update()
{
	if(!playReversed)
	{
    	if(animationTimer.getScaledTicks() >= 1)
        {
            animationTimer.start();
            ++currentFrame;
        }
        if((size_t)currentFrame > image.size()-1)
        {
            if(numLoops == -1)
                currentFrame = 0;
            else if( numLoops > 0)
            {
                currentFrame = 0;
                --numLoops;
            }
            else
                currentFrame = image.size()-1;
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
            if((size_t)currentFrame > image.size()-1)
            {
                    currentFrame = image.size()-1;
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

#ifdef PENJIN_SDL
    void Animation::render(SDL_Surface *screen){image.renderImage(currentFrame, screen, position);}
#else
    void Animation::render(){image.renderImage(currentFrame, position);}
#endif

