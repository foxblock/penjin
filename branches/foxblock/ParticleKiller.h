#ifndef PARTICLEKILLER_H
#define PARTICLEKILLER_H

#include "ParticleCollider.h"


class ParticleKiller : public ParticleCollider
{
    public:
        ParticleKiller();
        virtual ~ParticleKiller();

        virtual void update();
};

#endif // PARTICLEKILLER_H
