#include "KeyMapDigitalJoyAxis.h"

KeyMapDigitalJoyAxis::KeyMapDigitalJoyAxis()
{
    //ctor
    device = DEV_DIGITAL_JOYSTICK_AXIS;
    axis =0;
    trigger = 0;
    target = SJ_UNMAPPED;
    setDeviceID(0);
}

KeyMapDigitalJoyAxis::~KeyMapDigitalJoyAxis()
{
    //dtor
}


KeyMapDigitalJoyAxis::KeyMapDigitalJoyAxis(CRstring SJ,CRint a,CRint triggerVal,CRuchar id)
{
    axis = a;
    setSJMap(SJ);
    setDeviceID(id);
    device = DEV_DIGITAL_JOYSTICK_AXIS;
    trigger = triggerVal * 32767;
}
