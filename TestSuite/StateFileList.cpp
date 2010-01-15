#include "StateFileList.h"

StateFileList::StateFileList()
{
    //ctor
    choice = "NULL";
    loaded = false;
}

StateFileList::~StateFileList()
{
    //dtor
}

void StateFileList::init()
{
    list.loadFont("font/unispace.ttf",18);
    list.setSelection(1);
    list.setTextBgColour(BLACK);
    list.setTextColour(YELLOW);
    list.setTextSelectionColour(BLUE);
}


void StateFileList::render()
{
    GFX::clearScreen();
    if(loaded == true)
        test.render();
    list.render();
}

void StateFileList::update()
{
    list.update();
    //cout << choice;
}


void StateFileList::userInput()
{
    input->update();
    #ifdef PLATFORM_PC
        if(input->isQuit())
            nullifyState();
    #endif
    if(input->isStart())
        setNextState(STATE_TITLE);
    if(input->isUp())
        list.menuUp();
    else if(input->isDown())
        list.menuDown();

    if(input->isA())
    {
        choice = list.enter();
        if(choice.find(".png") != choice.npos)
        {
            test.clear();
            PENJIN_ERRORS t = test.loadSprite(list.getPath()+"/"+choice);
            if(t == PENJIN_OK)
                loaded = true;
        }
    }
    else if(input->isB())
    {
        list.goUp();
    }
    input->resetKeys();
}
