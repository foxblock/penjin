#include "AnimatedParticle.h"

AnimatedParticle::AnimatedParticle()
{
    //ctor
    particleType = ANIMATED_PARTICLE;
    spritePointer = NULL;
}

AnimatedParticle::~AnimatedParticle()
{
    //dtor
}

#ifdef PENJIN_SDL
    void AnimatedParticle::render(SDL_Surface* screen)
    {
        #ifdef PENJIN_FIXED
            spritePointer->setPosition(Vector2di(position.x.intValue >> 16, position.y.intValue >> 16));
        #else
            spritePointer->setPosition(Vector2di(position.x, position.y));
        #endif
        spritePointer->render(screen);
    }
#else
    void AnimatedParticle::render()
    {
        spritePointer->setPosition(position);
        spritePointer->render();
    }
#endif


void AnimatedParticle::changeAlpha(CRuchar value)
{
    spritePointer->setAlpha(spritePointer->getAlpha() + value);
}

void AnimatedParticle::update()
{
    spritePointer->update();
    ++lifeTime;

    //  Update position of particle
    position = position + velocity;

    //  Apply acceleration and gravity
    velocity += acceleration;
    acceleration += gravity;


    if(useDeviance)
        #ifndef PENJIN3D
            #ifdef PENJIN_FIXED
                position = position + Vector2dx(Random::nextFixed()-deviation,Random::nextFixed()-deviation);
            #else
                position = position + Vector2df(Random::nextFloat()-deviation,Random::nextFloat()-deviation);
            #endif
        #else
            position = position + Vector3df(Random::nextFloat()-deviation,Random::nextFloat()-deviation,Random::nextFloat()-deviation);
        #endif

}
