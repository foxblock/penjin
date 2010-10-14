#include "StatePrimitive.h"
#include "Pixel.h"
#include "Line.h"
#include "Rectangle.h"
#include "Text.h"
#include "NumberUtility.h"
StatePrimitive::StatePrimitive()
{
    //ctor
    primMode = PIXEL;
    numPrims = 10;
    thickness = 10;
    text = new Text;
    pix = new Pixel;
    line = new Line;
    rect = new Rectangle;
    rect->setThickness(thickness);
}

StatePrimitive::~StatePrimitive()
{
    //dtor
    delete pix;
    delete line;
    delete rect;
    delete text;
}

void StatePrimitive::init()
{
    GFX::setClearColour(BLACK);
    GFX::clearScreen();
    text->loadFont("font/unispace.ttf",15);
    text->setBoundaries(Vector2di(0,0),Vector2di(GFX::getXResolution(),GFX::getYResolution()));
    text->setRelativity(true);
}

void StatePrimitive::render()
{
    PRIM_MODE tprm = NO_PRIM;
    if(primMode == RAND_PRIM)
    {
        tprm = primMode;
        primMode = (PRIM_MODE)Random::nextInt(0,2);
        thickness = Random::nextInt(0,50);
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
            pix->setPosition(p.x,p.y);
            pix->setColour(c);
            pix->render();
        }
        else if(primMode == LINE)
        {
            Point2di t;
            t.x = p.x + d.x;
            t.y = p.y + d.y;
            line->setStartPosition(p);
            line->setEndPosition(t);
            line->setColour(c);
            line->setLineWidth(thickness);
            line->render();
        }
        else if(primMode == RECT)
        {
            rect->setColour(c);
            rect->setPosition(p.x,p.y);
            rect->setDimensions(d.x,d.y);
            rect->setThickness(thickness);
            rect->render();
        }
    }
    if(tprm != NO_PRIM)
    {
        primMode = tprm;
    }
    text->setPosition(GFX::getXResolution()/10, GFX::getYResolution()/10);
    text->print("Penjin - Primitives Test.\n\n");
    text->print("Mode (Up/Down):");
    if(primMode == PIXEL)
        text->print("PIXEL");
    else if(primMode == LINE)
        text->print("LINE");
    else if(primMode == RECT)
        text->print("RECTANGLE");
    else if(primMode == RAND_PRIM)
        text->print("RANDOM");
    text->print("\n");
    text->print("Width (Left/Right): ");text->print(thickness);
    text->print("\nStart: Return to Menu.\n");
    text->print("Select: Clear Screen.");
}

void StatePrimitive::update()
{
    thickness = NumberUtility::limit(thickness,0,50);
}


void StatePrimitive::userInput()
{
    /*
        Controls description:
    */
    input->update();
    if(input->isQuit())
        nullifyState();
    uint tPM = primMode;
    if(input->isUp())
    {
        tPM = tPM + 1;
        GFX::clearScreen();
    }

    else if(input->isDown())
    {
        tPM = tPM - 1;
        GFX::clearScreen();
    }
    primMode = (PRIM_MODE)NumberUtility::limit(tPM,(uint)PIXEL,(uint)RAND_PRIM);

    if(input->isLeft())
        thickness--;
    else if(input->isRight())
        thickness++;

    if(input->isStart())
        setNextState(STATE_TITLE);
    if(input->isSelect())
        GFX::clearScreen();
    input->resetKeys();
}
