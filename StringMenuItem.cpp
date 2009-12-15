#include "StringMenuItem.h"

StringMenuItem::~StringMenuItem()
{
}

void StringMenuItem::init()
{
    setType(MENU_STRING_ITEM);
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
    selectionIndicator = '-';
}

#ifdef PENJIN_SDL
void StringMenuItem::render()
{
    text->setPosition(position/*+ Vector2di(horizontalOffset,0)*/);
    string out;
    if(isSelected)
    {
        Colour temp = text->getColour();
        if(temp != selectedColour)
            text->setColour(selectedColour);
        out = selectionIndicator;
        out += " " + menuItemText + " " + selectionIndicator;
        text->print(out);
        text->setColour(temp);
        return;
    }
    else
        out = "  " + menuItemText + "  ";

    text->print(out);
}
void StringMenuItem::render(SDL_Surface* screen)
{
    text->setPosition(position/*+ Vector2di(horizontalOffset,0)*/);
    string out;
    if(isSelected)
    {
        Colour temp = text->getColour();
        if(temp != selectedColour)
            text->setColour(selectedColour);
        out = selectionIndicator;
        out += " " + menuItemText + " " + selectionIndicator;
        text->print(screen,out);
        text->setColour(temp);
        return;
    }
    else
        out = "  " + menuItemText + "  ";

    text->print(screen,out);
}
#else
void StringMenuItem::render()
{
    text->setPosition(position+ Vector3df(horizontalOffset,0.0f,0.0f));
    string out;
    if(isSelected)
    {
        out = selectionIndicator;
        out += " " + menuItemText + " " + selectionIndicator;
    }
    else
        out = menuItemText;

    text->print(out);
}
#endif
void StringMenuItem::update()
{
    return;
}

Vector2di StringMenuItem::getDimensions()
{
    dimensions = text->getDimensions(menuItemText);
    return dimensions;
}

