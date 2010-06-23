#include "StateRaycast.h"

StateRaycast::StateRaycast()
{
    m_Engine = new Raycast();
    m_Engine->init(32, 32, 480, 320);
    m_Engine->loadTexture("images/Textures/1.png");
    m_Engine->loadTexture("images/Textures/1.png");
    m_Border.loadBackground("images/Textures/Border.png");
    m_Border.setTransparentColour(MAGENTA);
    m_Border.setPosition(Vector2di(0,0));
}
StateRaycast::~StateRaycast()
{
    delete m_Engine;
}
void StateRaycast::init()
{

}

void StateRaycast::render()
{
    m_Engine->render();
    m_Border.render();
}
void StateRaycast::userInput()
{
    input->update();
    #ifdef PLATFORM_PC
        if(input->isQuit())
            nullifyState();
    #endif
    if(input->isStart())
        setNextState(STATE_TITLE);

    m_Engine->userInput(input);
}
