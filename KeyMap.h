#ifndef KEYMAP_H
#define KEYMAP_H

#include "PenjinTypes.h"
#if defined(PLATFORM_PANDORA)
#if !defined(PENJIN_SDL_INPUT)
// && (defined(PENJIN_ES) || defined(PENJIN_ES2))
    #include <linux/input.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdio.h>
#endif
#endif
#include <SDL/SDL.h>
#include <string>
using std::string;

namespace KeyMappings
{
    /// Device types
    enum KEY_MAP_DEVICE
    {
        DEV_KEYBOARD,
        DEV_MOUSE_BUTTON,
        DEV_MOUSE_AXIS,
        DEV_DIGITAL_JOYSTICK_AXIS,
        DEV_JOYSTICK_AXIS,
        DEV_JOYSTICK_BUTTON,
        DEV_JOYSTICK_HAT,
        DEV_WII_REMOTE,
        DEV_WII_CLASSIC,
        DEV_WII_GUITAR,
        DEV_UNKNOWN
    };
    /// SimpleJoy Mappings
    enum SIMPLEJOY_MAP
    {
        SJ_UP,
        SJ_DOWN,
        SJ_LEFT,
        SJ_RIGHT,
        SJ_UPLEFT,
        SJ_UPRIGHT,
        SJ_DOWNLEFT,
        SJ_DOWNRIGHT,
        SJ_A,
        SJ_B,
        SJ_X,
        SJ_Y,
        SJ_L,
        SJ_R,
        SJ_VOLUP,
        SJ_VOLDOWN,
        SJ_START,
        SJ_SELECT,
        SJ_CLICK,
        SJ_LID,
        SJ_LEFTSTICK_X,
        SJ_LEFTSTICK_Y,
        SJ_RIGHTSTICK_X,
        SJ_RIGHTSTICK_Y,
        SJ_MOUSE_X,
        SJ_MOUSE_Y,
        SJ_MOUSE_LEFT,
        SJ_MOUSE_CENTRE,
        SJ_MOUSE_RIGHT,
        SJ_UNMAPPED
    };
}

using namespace KeyMappings;
class KeyMap
{
    public:
        KeyMap();
        virtual ~KeyMap();

        void setDevice(KEY_MAP_DEVICE dev){device = dev;}
        void setDeviceID(CRuchar id){deviceID = id;}
        uchar getDeviceID()const{return deviceID;}
        KEY_MAP_DEVICE getDevice()const{return device;}
        SIMPLEJOY_MAP getTarget()const{return target;}
    protected:
        void setSJMap(string target);
        KEY_MAP_DEVICE device;      //  What type of device are we mapping?
        SIMPLEJOY_MAP target;       //  The target the mapped key will trigger.
        uchar deviceID;
};

#endif // KEYMAP_H
