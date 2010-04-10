#include "StateTitle.h"

StateTitle::StateTitle()
{
    //ctor
}

StateTitle::~StateTitle()
{
    //dtor
}

void StateTitle::init()
{
    input->resetKeys();
    initMenu();
}


void StateTitle::initMenu()
{
    choice = -1;
    menu.clear();
    menu.setMenuStart(GFX::getXResolution()*0.25f - 15,50);
    menu.setSelection(1);
    menu.loadFont("font/unispace.ttf", 14);

    menu.setTextColour(Colour(YELLOW));
    menu.setTextSelectionColour(Colour(WHITE));
    menu.addItem(MENU_STRING_ITEM);
    menu.setIsSelectable(false);
    menu.setMenuItemText("Penjin TestSuite");
    const int spacing = 0;
    menu.setSpacing(spacing);
    menu.setHorizontalOffset(110);
    #ifdef PENJIN_SDL
        menu.setUseHardware(true);
    #endif
    menu.addItem(MENU_STRING_ITEM);
    menu.setIsSelectable(true);
    menu.setMenuItemText("Animation Test");
    menu.setSpacing(spacing);

    menu.addItem(MENU_STRING_ITEM);
    menu.setIsSelectable(true);
    menu.setMenuItemText("Colour Test");
    menu.setSpacing(spacing);

    menu.addItem(MENU_STRING_ITEM);
    menu.setIsSelectable(true);
    menu.setMenuItemText("Primitives Test");
    menu.setSpacing(spacing);

    menu.addItem(MENU_STRING_ITEM);
    menu.setIsSelectable(true);
    menu.setMenuItemText("RayCaster Test WIP");
    menu.setSpacing(spacing);

    menu.addItem(MENU_STRING_ITEM);
    menu.setIsSelectable(true);
    menu.setMenuItemText("FileLister");
    menu.setSpacing(spacing);

    menu.addItem(MENU_STRING_ITEM);
    menu.setIsSelectable(true);
    menu.setMenuItemText("Rotation Test");
    menu.setSpacing(spacing);

    menu.addItem(MENU_STRING_ITEM);
    menu.setIsSelectable(true);
    menu.setMenuItemText("Collision Test");
    menu.setSpacing(spacing);

    menu.addItem(MENU_STRING_ITEM);
    menu.setIsSelectable(true);
    menu.setMenuItemText("Quit!");
    menu.setSpacing(spacing);
    menu.centreText();
}

void StateTitle::render()
{
    GFX::clearScreen();
    menu.render();

    /*test.setPosition(0,GFX::getYResolution()*0.5f);
    test.setFontSize(8);
    test.print("8 Point Font\n");
    test.setFontSize(16);
    test.print("16 Point font\n");;
    test.setFontSize(8);
    test.print("8 Point Font\n");
    test.print("Tab\tTab\tTab\t");
    test.print("This text is a load of garbage really and I'm only wanting to test text wrapping... if you see that this scrolls on the next line on a per word basis then all is well.");
*/}

void StateTitle::update()
{
    menu.update();
    menuLogic();
}

void StateTitle::userInput()
{
    input->update();
    #ifdef PLATFORM_PC
        if(input->isQuit())
            nullifyState();
    #endif
    menu.setMouseSelection(input->getTouch());
    if(input->isTouch() || input->isA() || input->isStart())
    {
        choice = menu.getSelection();
        input->resetKeys();
    }
    if(input->isUp())
    {
        menu.menuUp();
        input->resetKeys();
    }
    else if(input->isDown())
    {
        menu.menuDown();
        input->resetKeys();
    }
}

void StateTitle::menuLogic()
{
    // Choice starts from 1 since 0 is used by a non-selectable menu header

    if (choice == 1)        //  Animations
        setNextState(STATE_ANIMATION);
    else if(choice == 2)    //  Colours
        setNextState(STATE_COLOUR);
    else if(choice == 3)    //  Primitives
        setNextState(STATE_PRIMITIVE);
    else if(choice == 4)
        setNextState(STATE_RAYCAST);
    else if(choice == 5)
        setNextState(STATE_FILE_LIST);
    else if(choice == 6)
        setNextState(STATE_ROTATION);
    else if (choice == 7)
        setNextState(STATE_COLLISION);
    else if(choice == 8)    //  Quit
        nullifyState();
}
