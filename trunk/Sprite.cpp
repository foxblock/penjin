#include "Sprite.h"

Sprite::Sprite()
{
    position.x = 0;
    position.y = 0;
    #ifdef PENJIN3D
        position.z = 0.0f;
    #endif
    #ifdef PENJIN_SDL
        screen = SDL_GetVideoSurface();
    #endif
}
#ifndef PENJIN3D
    Sprite::Sprite(CRint x,CRint y)
    {
        setPosition(x,y);
        #ifdef PENJIN_SDL
            screen = SDL_GetVideoSurface();
        #endif
    }
#else
    Sprite::Sprite(CRfloat x,CRfloat y)
    {
        setPosition(x,y);
    }
    Sprite::Sprite(CRfloat x,CRfloat y,CRfloat z)
    {
        setPosition(x,y,z);
    }
    Sprite::Sprite(const Vector3df& position)
    {
        setPosition(position);
    }
    Sprite::Sprite(const Vector2df& position)
    {
        setPosition(position);
    }
#endif

PENJIN_ERRORS Sprite::loadSprite(CRstring fileName){return image.loadImage(fileName);}

#ifdef PENJIN_SDL
    void Sprite::render(SDL_Surface* screen){image.renderImage(screen,position);}
#else
    void Sprite::render(){image.renderImage(position);}
#endif

#ifdef PENJIN_SDL
bool Sprite::hasCollided(Sprite &spr)
{/*
   uint a = image.getWidth()/2;
   uint b = spr.image.getWidth()/2;

   IntVector2d temp = *this - IntVector2d(spr.getX(),spr.getY());

	if (temp.lengthSquared() <= a * a + b * b)
	 	return true;
*/
	return false;
}
#endif
