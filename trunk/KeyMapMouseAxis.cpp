#include "KeyMapMouseAxis.h"

KeyMapMouseAxis::KeyMapMouseAxis()
{
    //ctor
    device = DEV_MOUSE_AXIS;
    mouseAxis = 0;
    target = SJ_UNMAPPED;
    setDeviceID(0);
}

KeyMapMouseAxis::~KeyMapMouseAxis()
{
    //dtor
}

KeyMapMouseAxis::KeyMapMouseAxis(CRuchar a,CRstring SJ,CRuchar id)
{
    mouseAxis = a;
    setSJMap(SJ);
    setDeviceID(id);
    device = DEV_MOUSE_AXIS;
}
