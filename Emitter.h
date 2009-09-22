#ifndef EMITTER_INCLUDED
#define EMITTER_INCLUDED

#include "AnimatedParticle.h"
#include "SpriteParticle.h"
#include "Particle.h"
#include "Random.h"
#include <vector>
//#include <boost/shared_ptr.hpp>

using namespace std;
using namespace PenjinErrors;

/// TODO Add beam mode to particle emitter. (no random velocities and no varience)

class Emitter
{
    public:
        Emitter();
        ~Emitter();

        void start(){resetPlayback();}
        void setParticlesType(const PARTICLE_TYPES& type);

        void advanceUpdate(CRuint numCycles);

        PENJIN_ERRORS loadSprite(CRstring filename);
        PENJIN_ERRORS loadAnimatedSprite(CRstring filename);
        PENJIN_ERRORS loadAnimatedSprites(CRstring fileName,CRuint xTiles,CRuint yTiles);

        #ifdef PENJIN_SDL
            void setUseHardware(CRbool shoulduse);
            void render(SDL_Surface* screen);       //  Render all particles
            void render(){render(screen);}
        #else
            void render();
        #endif
        void update();                          //  Update all contained particles

        void setMax(CRint numParticles);          //  Sets the number of particles this emitter can emit
        uint size()const{return max;}
        void setLifeTime(int ms);               //  Sets how long a particle should be active.
        void setInvisible(CRuint invis){invisible = invis;}
        template <class T>
        void setPosition(const T& pos){position = pos;}
    #ifdef PENJIN3D
        void setPosition(const Vector2di& p){position.x = p.x;position.y = p.y;}
        Vector3df getPosition()const{return position;}
        Vector3df getPosition(CRuint i)const{if(i<=max-1){return particles[i]->getPosition();}}
        Vector3df getVelocity(CRuint i)const{if(i<=max-1){return particles[i]->getVelocity();}}
        Vector3df getAcceleration(CRuint i)const{if(i<=max-1){return particles[i]->getAcceleration();}}
        void setAcceleration(CRuint i, const Vector3df& accel)const{if(i<=max-1){particles[i]->setAcceleration(accel);}}
        void setPosition(CRuint i, const Vector3df& pos)const{if(i<=max-1){particles[i]->setPosition(pos);}}
        void setVelocity(CRuint i, const Vector3df& vel)const{if(i<=max-1){particles[i]->setVelocity(vel);}}

        void setMaxVelocity(const Vector3df& vel){maxVelocity = vel;}
        void setMaxVelocity(const Vector2df& vel){maxVelocity.x = vel.x; maxVelocity.y = vel.y;}
        void setDeviation(CRfloat dev){deviance = dev;}
        void setGravity(const Vector3df g){gravity = g;}
        void setGravity(CRfloat g){gravity.y = g;}
        void setAcceleration(const Vector3df& accel){acceleration = accel;}
    #else
        Vector2df getPosition()const{return position;}
        Vector2df getPosition(CRuint i)const{if(i<=max-1){return particles[i]->getPosition();}}
        Vector2df getVelocity(CRuint i)const{if(i<=max-1){return particles[i]->getVelocity();}}
        Vector2df getAcceleration(CRuint i)const{if(i<=max-1){return particles[i]->getAcceleration();}}
        void setPosition(CRuint i, const Vector2df& pos)const{if(i<=max-1){particles[i]->setPosition(pos);}}
        void setVelocity(CRuint i, const Vector2df& vel)const{if(i<=max-1){particles[i]->setVelocity(vel);}}
        void setAcceleration(CRuint i, const Vector2df& accel)const{if(i<=max-1){particles[i]->setAcceleration(accel);}}
        void setMaxVelocity(const Vector2df& vel){maxVelocity = vel;}
        void setAcceleration(const Vector2df& accel){acceleration = accel;}
        void setGravity(const Vector2df& g){gravity = g;}
        void setGravity(CRfloat g){gravity.y = g;}
        void setDeviation(CRfloat d){deviance = d;}
    #endif
        void setColour(const Colour& col){colour = col;}
        void shouldFadeColour(CRint fadeMode)
        {
            if(fadeMode <=2 && fadeMode >=0)
                fade = fadeMode;
        }
        void shouldFadeColour(CRbool shouldFade)
        {
            if(shouldFade)
                shouldFadeColour(1); // fade colours
            else
                shouldFadeColour(0);
        }
        void setFadeValue(CRfloat value){fadeValue = value;}
        void setFadeValue(CRint value){fadeValue = value;}
        void setLooping(CRbool l){repeat = l;}
        bool isFinished()const{return finished;}

        void reset(CRint i)
        {
            if(!stopNew)
            {
                particles[i]->setPosition(position);
                #ifndef PENJIN3D
                    #ifdef PENJIN_FIXED
                        Fixed x = Random::nextFixed(0,(maxVelocity.x.intValue >> 16) *2)-maxVelocity.x;
                        Fixed y = Random::nextFixed(0,(maxVelocity.y.intValue >> 16) *2)-maxVelocity.y;
                    #else
                        float x = Random::nextFloat(0,maxVelocity.x *2)-maxVelocity.x;
                        float y = Random::nextFloat(0,maxVelocity.y *2)-maxVelocity.y;
                    #endif
                    particles[i]->setVelocity(Vector2df(x,y));
                #else
                    float x = Random::nextFloat(0,maxVelocity.x *2)-maxVelocity.x;
                    float y = Random::nextFloat(0,maxVelocity.y *2)-maxVelocity.y;
                    float z = Random::nextFloat(0,maxVelocity.z *2)-maxVelocity.z;
                    particles[i]->setVelocity(Vector3df(x,y,z));
                #endif
                particles[i]->setColour(colour);
                particles[i]->setGravity(gravity);
                particles[i]->setAcceleration(acceleration);
                particles[i]->setDeviation(deviance);
                particles[i]->setLifeTime(0);
            }
        }
        void resetPlayback()
        {
            for(int i = max-1; i >=0; --i)
                reset(i);

            finished = false;
        }
        void setShouldStopNew(CRbool stop){stopNew = stop;}
        void setUpBoundary(const Vector2di& bound)
        {
            clipBoundary.w = bound.x;
            clipBoundary.h = bound.y;
        }
        void setDownBoundary(const Vector2di& bound)
        {
            clipBoundary.x = bound.x;
            clipBoundary.y = bound.y;
        }
        void setBoundaries(const Vector2di& lowBound,const Vector2di& hiBound)
        {
            setUpBoundary(hiBound);
            setDownBoundary(lowBound);
        }
        void setBoundaries(const SDL_Rect& boundaries){clipBoundary = boundaries;}
    private:
        void clearParticles();
        Particle** particles;
        Sprite* sprite;
        AnimatedSprite* animSprite;

        uint max;                   //  The max number of particles
        int lifeTime;               //  The max life of each particle
        Timer emitTimer;            //  The timer regulating this particle system.
        Colour colour;              //  The base colour of the particles
        #ifndef PENJIN3D
            Vector2df gravity;              //  The gravity of this particle system
            Vector2df position;
            Vector2df maxVelocity;      //  The maximum velocity that each particle can travel at
            Vector2df acceleration;   //  The direction that the particles are biased towards
        #else
            Vector3df gravity;
            Vector3df position;
            Vector3df maxVelocity;
            Vector3df acceleration;
        #endif

        int fade;                   //  Do we want the colour to gradually fade each cycle?
                                    //  0-no fade 1-fade colour 2 fade alpha
        bool repeat;                //  Should the particles repeat?
        bool finished;
        bool stopNew;               //  stop the creation of new particles?
        float deviance;
        float fadeValue;              //  The rate that the colour fades
        int updatePeriod;
        uint invisible;              //  number of particles which are classed as invisible
        SDL_Rect clipBoundary;      //  The area that the particle is allowed to exist within
        #ifdef PENJIN_SDL
            SDL_Surface* screen;
        #endif
};

#endif // EMITTER_INCLUDED
