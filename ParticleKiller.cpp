#include "ParticleKiller.h"

ParticleKiller::ParticleKiller()
{
    //ctor
}

ParticleKiller::~ParticleKiller()
{
    //dtor
}

void ParticleKiller::update()
{
    for(int i = emit.size()-1; i >=0; --i)
    {
        if(emit[i])
        {
            for(int j = emit[i]->size()-1; j>=0; --j)
            {
                #ifdef PENJIN_3D
                    // TODO 3D version
                #else
                    // Check direction of particle
                    Vector2df v = emit[i]->getVelocity(j);
                    Vector2df pos = emit[i]->getPosition(j);
                    if(pos.x >= position.x && pos.x <= position.x + dimensions.x
                    && pos.y >= position.y && pos.y <= position.y + dimensions.y)
                    {
                        //collision
                        // Check particle velocity to guess which side is hit
                        emit[i]->setPosition(j,pos-v);
                        emit[i]->setAcceleration(j,Vector2df(0.0f,0.0f));
                        emit[i]->reset(j);
                    }
                #endif
            }
        }
    }
}
