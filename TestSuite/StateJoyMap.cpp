#include "StateJoyMap.h"
#include "Text.h"
#include "AnimatedSprite.h"
#include "Parser.h"

StateJoyMap::StateJoyMap()
{
    //ctor
    text = new Text;
    buttons = new AnimatedSprite;
    parse = new Parser;
    timer = new Timer;
    line = new Line;
    rect = new Rectangle;
    testMode = true;
}

StateJoyMap::~StateJoyMap()
{
    //dtor
    delete text;
    delete buttons;
    delete parse;
    delete timer;
    delete line;
    delete rect;
}

void StateJoyMap::init()
{
    //  Load button images
    buttons->loadFrames("images/ButtonsSheet.png",10,2);
    text->loadFont("font/unispace.ttf", 14);
    text->setColour(BLUE);
    line->setColour(BLACK);
    rect->setColour(RED);
    GFX::setClearColour(WHITE);
    currentButton = 0;

    //  Setup joytest areas
    joyCentre[0].x = GFX::getXResolution()*0.33333f;
    joyCentre[1].x = GFX::getXResolution() - joyCentre[0].x;
    joyCentre[0].y = joyCentre[1].y = GFX::getYResolution()*0.5f;
    joyBoxStart[0] = joyCentre[0];
    joyBoxStart[1] = joyCentre[1];
    joyBoxEnd[0] = joyBoxStart[0] + Vector2di(1,1);
    joyBoxEnd[1] = joyBoxStart[1] + Vector2di(1,1);
}

void StateJoyMap::render()
{
    GFX::clearScreen();
    if(testMode)
    {
        text->print("JoyMap - Test Mode");
        //  draw test area
        rect->setPosition(joyBoxStart[0]);
        rect->setDimensions(joyBoxEnd[0]-joyBoxStart[0]);
        rect->render();
        rect->setPosition(joyBoxStart[1]);
        rect->setDimensions(joyBoxEnd[1]-joyBoxStart[1]);
        rect->render();
        renderCross(cursorPos,1);
        renderCross(joyCentre[0]+joyPos[0],2);
        renderCross(joyCentre[1]+joyPos[1],2);
    }
    else
    {
        text->print("JoyMap - Mapping Mode");
    }
}

void StateJoyMap::update()
{
    if(testMode)
    {

    }
    else
    {
    }
}

void StateJoyMap::userInput()
{
    input->update();
    if(input->isQuit())
        nullifyState();

    if(testMode)
    {

        cursorPos = input->getMouse();
        lastJoyPos[0] = joyPos[0];
        lastJoyPos[1] = joyPos[1];
        joyPos[0] = input->getLeftStick();
        joyPos[1] = input->getRightStick();
        // Stick 1
        if(joyBoxStart[0].x > joyCentre[0].x + joyPos[0].x && joyPos[0].x < lastJoyPos[0].x)
            joyBoxStart[0].x = joyCentre[0].x + joyPos[0].x;
        else if(joyBoxEnd[0].x < joyCentre[0].x + joyPos[0].x && joyPos[0].x > lastJoyPos[0].x)
            joyBoxEnd[0].x = joyCentre[0].x + joyPos[0].x;
        if(joyBoxStart[0].y > joyCentre[0].y + joyPos[0].y && joyPos[0].y < lastJoyPos[0].y)
            joyBoxStart[0].y = joyCentre[0].y + joyPos[0].y;
        else if(joyBoxEnd[0].y < joyCentre[0].y + joyPos[0].y && joyPos[0].y > lastJoyPos[0].y)
            joyBoxEnd[0].y = joyCentre[0].y + joyPos[0].y;

        //  Stick 2
        if(joyBoxStart[1].x > joyCentre[1].x + joyPos[1].x && joyPos[1].x < lastJoyPos[1].x)
            joyBoxStart[1].x = joyCentre[1].x + joyPos[1].x;
        else if(joyBoxEnd[1].x < joyCentre[1].x + joyPos[1].x && joyPos[1].x > lastJoyPos[1].x)
            joyBoxEnd[1].x = joyCentre[1].x + joyPos[1].x;
        if(joyBoxStart[1].y > joyCentre[1].y + joyPos[1].y && joyPos[1].y < lastJoyPos[1].y)
            joyBoxStart[1].y = joyCentre[1].y + joyPos[1].y;
        else if(joyBoxEnd[1].y < joyCentre[1].y + joyPos[1].y && joyPos[1].y > lastJoyPos[1].y)
            joyBoxEnd[1].y = joyCentre[1].y + joyPos[1].y;
    }
    else
    {
    }
}

void StateJoyMap::renderCross(Vector2di centre, CRint size)
{
    //  draw horiz
    line->setStartPosition(Vector2di(centre.x-size,centre.y));
    line->setEndPosition(Vector2di(centre.x+size, centre.y));
    line->render();
    //draw vert
    line->setStartPosition(Vector2di(centre.x,centre.y-size));
    line->setEndPosition(Vector2di(centre.x, centre.y+size));
    line->render();
}
