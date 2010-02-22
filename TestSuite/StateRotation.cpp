#include "StateRotation.h"

StateRotation::StateRotation()
{
    //ctor
    angle = 0;
    autoRot = true;
}

StateRotation::~StateRotation()
{
    //dtor
}

void StateRotation::init()
{
    GFX::setClearColour(BLACK);
    GFX::clearScreen();

    txt.loadFont("font/unispace.ttf", 14);
    txt.setBgColour(BLACK);
    txt.setColour(WHITE);
    txt.setRelativity(true);
    txtPos.x = GFX::getXResolution()*0.05f;
    txtPos.y = GFX::getYResolution()*0.05f;
    txt.setPosition(txtPos.x,txtPos.y);

    spr.loadSprite("images/Bullet.png");
    spr.setPosition(GFX::getXResolution()*0.5f,GFX::getYResolution()*0.5f);

    timer.start();
}

void StateRotation::update()
{
    if(autoRot && timer.getScaledTicks() > 500)
    {
        --angle;
        timer.start();
    }
    spr.setRotation(angle);
}

void StateRotation::render()
{
    GFX::clearScreen();
    txt.setPosition(txtPos.x,txtPos.y);
    txt.print("Angle: ");txt.print(angle);
    spr.render();
}

void StateRotation::userInput()
{
    input->update();
    #ifdef PLATFORM_PC
        if(input->isQuit())
            nullifyState();
    #endif
    if(input->isStart())
    {
        setNextState(STATE_TITLE);
    }
}
