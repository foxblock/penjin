#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include "PenjinTypes.h"
#include "Colour.h"
#include "Timer.h"
#include "Random.h"
#include <cmath>
#include "Pixel.h"
#ifdef PENJIN_GL
    #include <SDL/SDL_opengl.h>
#endif
/*
This is a particle, it can use coloured pixels, animated sprites and static sprites for each particle.
The sprite object must be passed into the render function of the particle from the Emitter...
*/

namespace ParticleTypes
{
    enum PARTICLE_TYPES
    {
        PARTICLE = 0,
        SPRITE_PARTICLE,
        ANIMATED_PARTICLE,
        MODEL3D_PARTICLE
    };
}

using namespace ParticleTypes;

class Particle
{
    public:
        #ifdef PENJIN3D
            Particle(const Vector3df& vec);
            Particle(CRfloat x,CRfloat y);
        #else
            Particle(const Vector2df& vec);
            Particle(CRfloat x, CRfloat y);
        #endif  // PENJIN3D
        Particle();
        void init();

        virtual ~Particle();

        virtual void update();
        void advanceUpdate();

        ///  WARNING THE EMITTER HANDLES SCREEN LOCKING AND UNLOCKING IN SDL!
        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
        #else
            virtual void render();
        #endif
        void setColour(const Colour& col);
        void setColour(const uchar& r,const uchar& g, const uchar& b);
        Colour getColour()const{return colour.getColour();}
        void changeColour(CRfloat value);
        void changeColour(const Colour& col);
        virtual void changeAlpha(CRfloat value);
        virtual void setAlpha(CRuchar a){colour.setAlpha(a);}
        uchar getAlpha()const{return colour.getAlpha();}

        #ifdef PENJIN3D
            void setPosition(const Vector3df& vec){position = vec;}
            void setPosition(const Vector2df& vec){position = Vector3df(vec.x, vec.y, 0.0f);}
            void setPosition(CRfloat x,CRfloat y,CRfloat z){position = Vector3df(x,y,z);}
            void setPosition(CRfloat x,CRfloat y){position = Vector3df(x,y,0.0f);}

            Vector3df getPosition()const{return position;}

            void setDeviation(CRfloat dev);
            void setAcceleration(const Vector3df& accel);
            void setGravity(CRfloat g);
            void setGravity(const Vector3df& g);
            void setVelocity(const Vector3df& vel){velocity = vel;}
            Vector3df getVelocity()const{return velocity;}
            Vector3df getAcceleration()const{return acceleration;}
        #else
            void setPosition(const Vector2df& vec);
            void setPosition(CRfloat x,CRfloat y);
            Vector2df getPosition()const{return position;}

            void setDeviation(CRfloat dev);
            void setAcceleration(const Vector2df& accel);
            void setGravity(const Vector2df& g);

            void setVelocity(const Vector2df& vel){velocity = vel;}
            Vector2df getVelocity()const{return velocity;}
            Vector2df getAcceleration()const{return acceleration;}
        #endif  //  PENJIN3D

        int getLifeTime()const{return lifeTime;}

        PARTICLE_TYPES getParticleType()const{return particleType;}
        void setLifeTime(CRint s){lifeTime = s;}

    protected:
        #ifdef PENJIN3D
            Vector3df position;
            Vector3df velocity;
            float deviation;            //  This is the random variance of the particle position
            Vector3df gravity;              //  Should this particle be influenced by gravity?
            Vector3df acceleration;     //  The actual acceleration
        #else
            Vector2df position;
            Vector2df velocity;
            float deviation;
            Vector2df gravity;
            Vector2df acceleration;
        #endif

        RandomClass rand;
        Pixel colour;
        Timer timer;                //  This regulates the updates of the particle
        bool useDeviance;
        int lifeTime;               //  Life of particles in ms;
        PARTICLE_TYPES particleType;          //  identifies between particle, SpriteParticle and AnimatedParticle types
};

#endif // PARTICLE_H_INCLUDED
