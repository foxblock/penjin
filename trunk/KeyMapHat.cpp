#include "KeyMapHat.h"

KeyMapHat::KeyMapHat()
{
    //ctor
    device = DEV_JOYSTICK_HAT;
    direction = SDL_HAT_CENTERED;
    target = SJ_UNMAPPED;
    setDeviceID(0);
}

KeyMapHat::~KeyMapHat()
{
    //dtor
}

KeyMapHat::KeyMapHat(const Uint8& d,CRstring SJ,CRuchar id)
{
    direction=d;
    setSJMap(SJ);
    setDeviceID(id);
    device = DEV_JOYSTICK_HAT;
}

KeyMapHat::KeyMapHat(CRstring d,CRstring SJ,CRuchar id)
{
    setDirection(d);
    setSJMap(SJ);
    setDeviceID(id);
    device = DEV_JOYSTICK_HAT;
}

void KeyMapHat::setDirection(CRstring dir)
{
    if(dir == "UP")
        direction = SDL_HAT_UP;
    else if(dir == "DOWN")
        direction = SDL_HAT_DOWN;
    else if(dir == "LEFT")
        direction = SDL_HAT_LEFT;
    else if(dir == "RIGHT")
        direction = SDL_HAT_RIGHT;
    else if(dir == "UPLEFT")
        direction = SDL_HAT_LEFTUP;
    else if(dir == "UPRIGHT")
        direction = SDL_HAT_RIGHTUP;
    else if(dir == "DOWNLEFT")
        direction = SDL_HAT_LEFTDOWN;
    else if(dir == "DOWNRIGHT")
        direction = SDL_HAT_RIGHTDOWN;
    else
        direction = SDL_HAT_CENTERED;
}
