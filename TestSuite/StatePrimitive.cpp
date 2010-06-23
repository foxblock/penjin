#include "StatePrimitive.h"

StatePrimitive::StatePrimitive()
{
    //ctor
    primMode = PIXEL;
    numPrims = 10;
    rect.setThickness(10);
}

StatePrimitive::~StatePrimitive()
{
    //dtor
}

void StatePrimitive::init()
{

}

void StatePrimitive::render()
{
//    GFX::renderStatic(0,0,800,480,1,50);
    PRIM_MODE tprm = NO_PRIM;
    if(primMode == RAND_PRIM)
    {
        tprm = primMode;
        primMode = (PRIM_MODE)Random::nextInt(0,2);
    }
    for(int i = numPrims; i >=0; --i)
    {
        Colour c;
        Random::setLimits(0,255);
        c.setColour((uchar)Random::nextInt(),Random::nextInt(),Random::nextInt(),Random::nextInt());
        Point2di p;
        p.x = Random::nextInt(0,GFX::getXResolution());
        p.y = Random::nextInt(0,GFX::getYResolution());
        Point2di d;
        d.x = Random::nextInt(1,GFX::getXResolution()*0.1f);
        d.y = Random::nextInt(1,GFX::getYResolution()*0.1f);
        if(primMode == PIXEL)
        {
            pix.setPosition(p.x,p.y);
            pix.setColour(c);
            pix.render();
        }
        else if(primMode == LINE)
        {
            Point2di t;
            t.x = p.x + d.x;
            t.y = p.y + d.y;
            line.setStartPosition(p);
            line.setEndPosition(t);
            line.setColour(c);
            line.render();
        }
        else if(primMode == RECT)
        {
            rect.setColour(c);
            rect.setPosition(p.x,p.y);
            rect.setDimensions(d.x,d.y);
            rect.render();
        }
    }
    if(tprm != NO_PRIM)
    {
        primMode = tprm;
    }
}

void StatePrimitive::update()
{
}

void StatePrimitive::userInput()
{
    /*
        Controls description:
    */
    input->update();
    #ifdef PLATFORM_PC
        if(input->isQuit())
            nullifyState();
    #endif
    if(input->isStart())
        setNextState(STATE_TITLE);
    input->resetKeys();
}
