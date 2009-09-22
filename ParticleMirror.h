#ifndef PARTICLEMIRROR_H
#define PARTICLEMIRROR_H

/*
    This class is to be used in conjunction with a particle Emitter class
    You grant this class access to the emitter and it will create a surface which will interect with
    that emitter's particles
*/
#include "ParticleCollider.h"

class ParticleMirror : public ParticleCollider
{
    public:
        ParticleMirror();
        virtual ~ParticleMirror();

        void setDampening(const Vector2di& d){dampening = d;}
        void setDampening(CRfloat d){dampening.x= dampening.y = d;}


        virtual void update();

    private:
        Vector2df dampening;
};

#endif // PARTICLEMIRROR_H
