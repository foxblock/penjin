#include "KeyMapJoyAxis.h"

KeyMapJoyAxis::KeyMapJoyAxis()
{
    //ctor
    device = DEV_JOYSTICK_AXIS;
    joyAxis =0;
    target = SJ_UNMAPPED;
    setDeviceID(0);
}

KeyMapJoyAxis::KeyMapJoyAxis(CRint a,CRstring SJ,CRuchar id)
{
    joyAxis = a;
    setSJMap(SJ);
    setDeviceID(id);
    device = DEV_JOYSTICK_AXIS;
}


KeyMapJoyAxis::~KeyMapJoyAxis()
{
    //dtor
}
