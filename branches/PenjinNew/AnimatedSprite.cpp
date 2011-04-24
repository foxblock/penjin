/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "AnimatedSprite.h"
using Penjin::AnimatedSprite;

AnimatedSprite::AnimatedSprite()
{
	currentFrame = 0;
	animationTimer.setMode(THIRTY_FRAMES);
    numLoops = -1;
	animationTimer.start();
	position.x = 0;
	position.y = 0;
	#ifdef PENJIN_SDL
        screen = GFX::getInstance()->getSDLVideoSurface();
    #endif
    #ifdef PENJIN_3D
        position.z = 0.0f;
    #endif

    hasFinishedVal = false;
	reachedEnd = false;
	mode = pmNormal;
}
#ifdef PENJIN_SDL
    AnimatedSprite::AnimatedSprite(CRint x,CRint y)
    {
        currentFrame = 0;
        animationTimer.setMode(THIRTY_FRAMES);
        numLoops = firstLoops = -1;
        animationTimer.start();
        hasFinishedVal = false;
        reachedEnd = false;
        mode = pmNormal;
        screen = GFX::getInstance()->getSDLVideoSurface();
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
        hasFinishedVal = false;
        reachedEnd = false;
        mode = pmNormal;
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
        hasFinishedVal = false;
        reachedEnd = false;
        mode = pmNormal;
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

PENJIN_ERRORS AnimatedSprite::loadFrames(CRstring fileName,CRuint xTiles,CRuint yTiles){image.clear(); return image.loadImageSheet(fileName, xTiles, yTiles);}

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
    if (not hasFinishedVal && animationTimer.getScaledTicks() >= 1) // has the next frame been reached?
    {
        animationTimer.start();
        switch (mode)
        {
            case pmNormal:
            {
                ++currentFrame;
                if (currentFrame > image.size()-1)
                {
                    if (numLoops != 0) // looping
                    {
                        currentFrame = 0;
                        if (numLoops > 0) // don't loop forever
                            --numLoops;
                    }
                    else
                    {
                        currentFrame = image.size()-1;
                        hasFinishedVal = true;
                    }
                }
                break;
            }
            case pmReverse:
            {
                --currentFrame;
                if (currentFrame < 0)
                {
                    if (numLoops != 0) // looping
                    {
                        currentFrame = image.size()-1;
                        if (numLoops > 0)
                            --numLoops;
                    }
                    else
                    {
                        currentFrame = 0;
                        hasFinishedVal = true;
                    }
                }
                break;
            }
            case pmPulse:
            {
                if (reachedEnd) // play backwards (phase 2)
                {
                    --currentFrame;
                    if (currentFrame < 0)
                    {
                        if (numLoops != 0)
                        {
                            reachedEnd = false;
                            currentFrame = min((size_t)1,image.size()-1); // set to second frame so we don't play the first frame two times in a row
                            if (numLoops > 0)
                                --numLoops;
                        }
                        else
                        {
                            currentFrame = 0;
                            hasFinishedVal = true;
                            reachedEnd = false;
                        }
                    }
                }
                else // play forwards (phase 1)
                {
                    ++currentFrame;
                    if (currentFrame > image.size()-1)
                    {
                        currentFrame = max((int)image.size()-2,0); // set to penultimate frame so we don't play the last one two times in a row
                        reachedEnd = true;
                    }
                }
                break;
            }
        }
    }
}
