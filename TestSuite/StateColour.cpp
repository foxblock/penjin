#include "StateColour.h"

StateColour::StateColour()
{
    //ctor
    text.setPosition(50,50);
    text.setRelativity(true);
    text.loadFont("font/unispace.ttf",20);
    current = 0;
    col.setColour(BLACK);
    GFX::setClearColour(col);
}

void StateColour::init()
{
    text.setBoundaries(Vector2di(0,0),Vector2di(getStateXResolution(),getStateYResolution()));
    rect.setDimensions(getStateXResolution(),getStateYResolution());
}

StateColour::~StateColour()
{
    //dtor
}

void StateColour::render()
{
    rect.render();
    text.setPosition(50,50);
    text.print("R:");text.print(col.red);text.print(" \n");
    text.print(" G:");text.print(col.green);text.print(" \n");
    text.print(" B:");text.print(col.blue);text.print(" \n");
    text.print(" A:");text.print(col.alpha);text.print(" \n");
    text.print("  UINT:");text.print((int)col.getSDL_Uint32Colour());text.print(" \n");text.print(" \n");
    Colour tCol = GFX::getPixel(1,1);
    text.print("GP_R:");text.print(tCol.red);text.print(" \n");
    text.print(" GP_G:");text.print(tCol.green);text.print(" \n");
    text.print(" GP_B:");text.print(tCol.blue);text.print(" \n");
    text.print(" GP_A:");text.print(tCol.alpha);text.print(" \n");
    text.print("  GP_UINT:");text.print((int)tCol.getSDL_Uint32Colour());
}

void StateColour::update()
{
     rect.setColour(col);
}

void StateColour::userInput()
{
    input->update();
    #ifdef PLATFORM_PC
        if(input->isQuit())
            nullifyState();
    #endif
    if(input->isStart())
        setNextState(STATE_TITLE);
    if(input->isLeft())
    {
        --current;
        input->resetKeys();
        if(current<0)
            current = 3;
    }
    else if(input->isRight())
    {
        ++current;
        input->resetKeys();
        if(current >3)
            current =0;
    }

    if(input->isUp())
    {
        if(current == 0)
            ++col.red;
        else if(current == 1)
            ++col.green;
        else if(current == 2)
            ++col.blue;
        else if(current == 3)
            ++col.alpha;
    }
    else if(input->isDown())
    {
        if(current == 0)
            --col.red;
        else if(current == 1)
            --col.green;
        else if(current == 2)
            --col.blue;
        else if(current == 3)
            --col.alpha;
    }
}
