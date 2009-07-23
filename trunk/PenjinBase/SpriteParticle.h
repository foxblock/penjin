#ifndef SPRITEPARTICLE_H
#define SPRITEPARTICLE_H

#include "Particle.h"
#include "Sprite.h"

class SpriteParticle : public Particle
{
    public:
        SpriteParticle();
        SpriteParticle(SpriteParticle& spr){*this = spr;}
        //SpriteParticle(Particle& part){*this = part;}
        virtual ~SpriteParticle();

        ///  WARNING THE EMITTER HANDLES SCREEN LOCKING AND UNLOCKING IN SDL!
        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
        #else
            virtual void render();
        #endif
        virtual void changeAlpha(CRfloat value);
        virtual void setAlpha(CRuchar a){alpha = a;}
        void setSprite(Sprite* sprite){spritePointer = sprite;}

    private:
        Sprite* spritePointer;
        uint alpha;
};

#endif // SPRITEPARTICLE_H
