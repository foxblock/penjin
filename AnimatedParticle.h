#ifndef ANIMATEDPARTICLE_H
#define ANIMATEDPARTICLE_H

#include "Particle.h"
#include "AnimatedSprite.h"
#include "Random.h"
class AnimatedParticle : public Particle
{
    public:
        AnimatedParticle();
        //AnimatedParticle(Particle& part){*this = part;}
        virtual ~AnimatedParticle();

        ///  WARNING THE EMITTER HANDLES SCREEN LOCKING AND UNLOCKING IN SDL!
        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
        #else
            virtual void render();
        #endif
        virtual void changeAlpha(CRuchar value);
        virtual void update();

        void setSprite(AnimatedSprite* sprite){spritePointer = sprite;}

    protected:
    private:
        AnimatedSprite* spritePointer;
};

#endif // ANIMATEDPARTICLE_H
