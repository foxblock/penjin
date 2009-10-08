#include "SpriteParticle.h"

SpriteParticle::SpriteParticle()
{
    //ctor
    particleType = SPRITE_PARTICLE;
    spritePointer = NULL;
    colour.setAlpha(255);
}

SpriteParticle::~SpriteParticle()
{
    //dtor
}

#ifdef PENJIN_SDL
    void SpriteParticle::render(SDL_Surface* screen)
    {
        spritePointer->setAlpha(alpha);
        #ifdef PENJIN_FIXED
            spritePointer->setPosition(Vector2di(position.x.intValue >> 16, position.y.intValue >> 16));
        #else
            spritePointer->setPosition(Vector2di(position.x, position.y));
        #endif
        spritePointer->render(screen);
    }
#else
    void SpriteParticle::render()
    {
        spritePointer->setPosition(position);
        spritePointer->render();
    }
#endif


void SpriteParticle::changeAlpha(CRfloat value)
{
    #ifdef PENJIN_FIXED
        alpha = fixedpoint::fix2int(alpha - value);
    #else
        alpha-=value;
    #endif
}
