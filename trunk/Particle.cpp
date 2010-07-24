#include "Particle.h"

Particle::Particle()
{
    init();
    setPosition(0,0);
}

#ifndef PENJIN_3D
    Particle::Particle(CRfloat x,CRfloat y)
    {
        init();
        setPosition(x,y);
    }

    Particle::Particle(const Vector2df& vec)
    {
        init();
        setPosition(vec);
    }
#else
    Particle::Particle(CRfloat x,CRfloat y)
    {
        init();
        setPosition(Vector3df(x,y,0.0f));
    }
    Particle::Particle(const Vector3df& vec)
    {
        init();
        setPosition(vec);
    }
#endif
Particle::~Particle()
{
}

void Particle::init()
{
    particleType = PARTICLE;
    colour.setColour(WHITE);
    deviation = 0;
    velocity.x = 0;
    velocity.y = 0;
    #ifdef PENJIN_3D
        velocity.z = 0;
    #endif
    gravity = acceleration = velocity;
    lifeTime = 0;
    timer.setMode(MILLI_SECONDS);
    timer.start();
    rand.setLimits(-1,1);
    useDeviance = false;
}

#ifdef PENJIN_SDL
    void Particle::render(SDL_Surface* screen)
    {
        colour.setPosition(position);
        colour.render(screen);
    }
#else
    void Particle::render()
    {
        colour.setPosition(position);
        colour.render();
    }
#endif

void Particle::advanceUpdate()
{
    ++lifeTime;
    //  Update position of particle
    position = position + velocity;

    //  Apply acceleration and gravity
    velocity += acceleration;
    acceleration += gravity;


    if(useDeviance)
        #ifndef PENJIN_3D
            #ifdef PENJIN_FIXED
                position = position + Vector2dx(rand.nextFixed()-deviation,rand.nextFixed()-deviation);
            #else
                position = position + Vector2df(rand.nextFloat()-deviation,rand.nextFloat()-deviation);
            #endif
        #else
            position = position + Vector3df(rand.nextFloat()-deviation,rand.nextFloat()-deviation,rand.nextFloat()-deviation);
        #endif
}

void Particle::update()
{
    ++lifeTime;
    timer.start();
    //  Update position of particle
    position = position + velocity;

    //  Apply acceleration and gravity
    velocity += acceleration;
    acceleration += gravity;


    if(useDeviance)
    #ifndef PENJIN_3D
        #ifdef PENJIN_FIXED
            position = position + Vector2dx(rand.nextFixed()-deviation,rand.nextFixed()-deviation);
        #else
            position = position + Vector2df(rand.nextFloat()-deviation,rand.nextFloat()-deviation);
        #endif
    #else
        position = position + Vector3df(rand.nextFloat()-deviation,rand.nextFloat()-deviation,rand.nextFloat()-deviation);
    #endif
}

void Particle::setColour(const Colour& col){colour.setColour(col);}

void Particle::setColour(const uchar& r,const uchar& g,const uchar& b){colour.setColour(r,g,b);}
#ifndef PENJIN_3D
    void Particle::setDeviation(CRfloat dev)
    {
        deviation = dev;
        #ifdef PENJIN_FIXED
            rand.setLimits(0, (fixedpoint::fix2int(dev)) *2);
        #else
            rand.setLimits(0, dev *2);
        #endif
        useDeviance = true;
    }
    void Particle::setAcceleration(const Vector2df& accel){acceleration = accel;}
    void Particle::setGravity(const Vector2df& g){gravity = g;}
    void Particle::setPosition(const Vector2df& vec){position = vec;}
    void Particle::setPosition(CRfloat x,CRfloat y){position = Vector2df(x,y);}
#else
    void Particle::setDeviation(CRfloat dev)
    {
        deviation = dev;
        rand.setLimits(0, dev *2);
        useDeviance = true;
    }
    void Particle::setAcceleration(const Vector3df& accel){acceleration = accel;}
    void Particle::setGravity(const Vector3df& grav){gravity = grav;}
#endif
void Particle::changeColour(CRfloat value)
{
    #ifdef PENJIN_FIXED
        colour.setRed(fixedpoint::fix2float(colour.getRed() - value));
        colour.setGreen(fixedpoint::fix2float(colour.getGreen() - value));
        colour.setBlue(fixedpoint::fix2float(colour.getBlue() - value));
    #else
        colour.setRed(colour.getRed() - value);
        colour.setGreen(colour.getGreen() - value);
        colour.setBlue(colour.getBlue() - value);
    #endif
}
void Particle::changeColour(const Colour& col){colour.setColour(colour.getColour() - col);}
void Particle::changeAlpha(CRfloat value)
#ifdef PENJIN_FIXED
    {colour.setAlpha(fixedpoint::fix2float(colour.getAlpha() - value));}
#else
    {colour.setAlpha(colour.getAlpha() - value);}
#endif
