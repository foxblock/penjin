#ifndef PARTICLECOLLIDER_H
#define PARTICLECOLLIDER_H

/*
This is a base class for the Penjin Particle system which describes a collidable object
to interact with the Particles.

You can create sub classes from this to allow different interactions.
e.g. a simple class which reflects upon collision
another which kills and resets the particles.

Author PokeParadox
*/
#include "Emitter.h"

class ParticleCollider
{

    public:
        ParticleCollider();
        virtual ~ParticleCollider();

        void linkEmitter(Emitter* e){emit.push_back(e);}
        void setPosition(const Vector2di& position){this->position = position;}
        void setDimensions(const Vector2di& dims){dimensions = dims;}
        void setColour(const Colour& c){colour = c;}

        virtual void update(){;}
    #ifdef PENJIN_SDL
        void render(SDL_Surface* screen);
    #else
        void render();
    #endif

    protected:
        vector <Emitter*> emit; // These are just pointers, we manipulate already existing particles
        Vector2di position;
        Vector2di dimensions;
        Colour colour;
};

#endif // PARTICLECOLLIDER_H
