#include "DirMenuItem.h"

DirMenuItem::DirMenuItem()
{
    init();
}

DirMenuItem::~DirMenuItem()
{
}

void DirMenuItem::init()
{
    setType(MENU_DIR_ITEM);
    position.x = 0;
    position.y = 0;
    #ifdef PENJIN3D
        position.z = 0.0f;
    #endif
    dimensions.x = 0;
    dimensions.y = 0;
    isSelected = false;
    isSelectable = true;
    verticalSpacing = 0;
    horizontalOffset = 0;
    selectionIndicator = '>';
    dirType = -1; // UNKNOWN
}

#ifdef PENJIN_SDL
void DirMenuItem::render()
{
    text->setPosition(position/*+ Vector2di(horizontalOffset,0)*/);
    string out;
    if(isSelected)
    {
        Colour temp = text->getColour();
        if(temp != selectedColour)
            text->setColour(selectedColour);
        out = selectionIndicator;
        out += " " + menuItemText;
        text->print(out);
        text->setColour(temp);
        return;
    }
    else
        out = menuItemText;

    text->print(out);
}
void DirMenuItem::render(SDL_Surface* screen)
{
    text->setPosition(position/*+ Vector2di(horizontalOffset,0)*/);
    string out;
    if(isSelected)
    {
        Colour temp = text->getColour();
        if(temp != selectedColour)
            text->setColour(selectedColour);
        out = selectionIndicator;
        out += " " + menuItemText;
        text->print(screen,out);
        text->setColour(temp);
        return;
    }
    else
        out = menuItemText;

    text->print(screen,out);
}
#else

#endif


#ifndef PENJIN_ASCII
    Vector2di DirMenuItem::getDimensions()
    {
        if(menuItemText.empty())
            return Vector2di(0,0);
        dimensions = text->getDimensions(menuItemText);
        return dimensions;
    }
#endif
