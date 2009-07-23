#include "KeyMapMouseButton.h"

KeyMapMouseButton::KeyMapMouseButton()
{
    //ctor
    device = DEV_MOUSE_BUTTON;
    mouseButton = SDL_MOUSE_NONE;
    target = SJ_UNMAPPED;
    setDeviceID(0);
}

KeyMapMouseButton::~KeyMapMouseButton()
{
    //dtor
}

KeyMapMouseButton::KeyMapMouseButton(CRuchar b,CRstring SJ,CRuchar id)
{
    setMouseButton(b);
    setSJMap(SJ);
    setDeviceID(id);
    device = DEV_MOUSE_BUTTON;
}

void KeyMapMouseButton::setMouseButton(CRuchar b)
{
    switch(b)
    {
        case 0:     mouseButton = SDL_MOUSE_LEFT;   break;
        case 1:     mouseButton = SDL_MOUSE_CENTRE; break;
        case 2:     mouseButton = SDL_MOUSE_RIGHT;  break;
        default:    mouseButton = SDL_MOUSE_NONE;   break;
    }
}
