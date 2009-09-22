#include "KeyMapJoyButton.h"

namespace JoyButton
{
    const int JOY_NO_BUTTON = -1;
}

KeyMapJoyButton::KeyMapJoyButton()
{
    //ctor
    device = DEV_JOYSTICK_BUTTON;
    joyButton = JoyButton::JOY_NO_BUTTON;
    target = SJ_UNMAPPED;
    setDeviceID(0);
}

KeyMapJoyButton::KeyMapJoyButton(CRint b,CRstring SJ,CRuchar id)
{
    joyButton = b;
    setSJMap(SJ);
    setDeviceID(id);
    device = DEV_JOYSTICK_BUTTON;
}

KeyMapJoyButton::~KeyMapJoyButton()
{
    //dtor
}
