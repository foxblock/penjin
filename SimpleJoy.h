#ifndef SIMPLEJOY_H
#define SIMPLEJOY_H

//#include "KeyboardDefines.h"
#include "PenjinTypes.h"
#include "KeyMapper.h"

#if defined(PLATFORM_PANDORA)
#include <linux/input.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#endif

/*
TODO: Add Wii Controls/GBA/NDS etc
*/
class SimpleJoy
{
    public:
        SimpleJoy();
        ~SimpleJoy();

        PENJIN_ERRORS loadControlMap(CRstring filename)
        {
            PENJIN_ERRORS t = mapper.loadControlMap(filename);
            if(t == PENJIN_OK)
                mapLoaded = true;
            return t;
        }

        void update();					//	Get current status of keyboard

        bool isStart()const{return Start;}
        bool isSelect()const{return Select;}
        bool isUp()const{return Up;}
        bool isDown()const{return Down;}
        bool isLeft()const{return Left;}
        bool isRight()const{return Right;}
        bool isA()const{return A;}
        bool isB()const{return B;}
        bool isX()const{return X;}
        bool isY()const{return Y;}
        bool isL()const{return L;}
        bool isR()const{return R;}
        /// The fabled ANY button.
        bool isAny()const{return (A || B || X || Y || L || R || Start || Select);}
    #ifdef PLATFORM_PC
        bool isQuit()const{return Quit;}
    #endif
    #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
        /// GP2X Buttons
        bool isClick()const{return Click;}
        bool isVolumeUp()const{return VolumeUp;}
        bool isVolumeDown()const{return VolumeDown;}
        bool isUpLeft()const{return UpLeft;}
        bool isUpRight()const{return UpRight;}
        bool isDownLeft()const{return DownLeft;}
        bool isDownRight()const{return DownRight;}
    #else
        bool isUpLeft()const{return false;}
        bool isUpRight()const{return false;}
        bool isDownLeft()const{return false;}
        bool isDownRight()const{return false;}
    #endif

        /// Joystick
        void setDeadZone(const Vector2di& zone){deadZone = zone;}
        void setDeadZoneX(CRint x){deadZone.x = x;}
        void setDeadZoneY(CRint y){deadZone.y = y;}
        void setScaler(CRfloat s){scaler = s;}
        Vector2di getLeftStick()const{return leftStick;}
        Vector2di getRightStick()const{return rightStick;}
        int getLeftStickX()const{return leftStick.x;}
        int getLeftStickY()const{return leftStick.y;}
        int getRightStickX()const{return rightStick.x;}
        int getRightStickY()const{return rightStick.y;}

        /// Joystick logical
        bool isLeftStick()const{return(isLeftStickDown() || isLeftStickLeft() || isLeftStickRight() || isLeftStickUp());}
        bool isLeftStickUp()const{return (getLeftStickY() < -deadZone.y);}
        bool isLeftStickDown()const{return (getLeftStickY() > deadZone.y);}
        bool isLeftStickLeft()const{return (getLeftStickX() < -deadZone.x);}
        bool isLeftStickRight()const{return (getLeftStickX() > deadZone.x);}
        bool isRightStick()const{return(isRightStickDown() || isRightStickLeft() || isRightStickRight() || isRightStickUp());}
        bool isRightStickUp()const{return (getRightStickY() < -deadZone.y);}
        bool isRightStickDown()const{return (getRightStickY() > deadZone.y);}
        bool isRightStickLeft()const{return (getRightStickX() < -deadZone.x);}
        bool isRightStickRight()const{return (getRightStickX() > deadZone.x);}

        /// Mouse
        Vector2di getMouse()const{return mouse;}
        int getMouseX()const{return mouse.x;}
        int getMouseY()const{return mouse.y;}
        bool isLeftClick()const{return leftClick;}
        bool isRightClick()const{return rightClick;}
        /// TouchScreen - Just a wrapper to mouse
        Vector2di getTouch()const{return mouse;}
        int getTouchX()const{return mouse.x;}
        int getTouchY()const{return mouse.y;}
        bool isTouch()const{return leftClick;}

#if defined(PLATFORM_PANDORA)
        /// Nub's
        Vector2di getNubLeft()const{return nubL;}
        int getNubLeftX()const{return nubL.x;}
        int getNubLeftY()const{return nubL.y;}
        Vector2di getNubRight()const{return nubR;}
        int getNubRightX()const{return nubR.x;}
        int getNubRightY()const{return nubR.y;}
#endif

        void resetKeys();

        /// Status
        void joystickStatus();
    private:
        void mappedDown(const SIMPLEJOY_MAP& map);
        void mappedUp(const SIMPLEJOY_MAP& map);
        void mappedMouseAxes(const SIMPLEJOY_MAP& map,CRuchar axis);
        void mappedJoyAxes(const SIMPLEJOY_MAP& map);

        SDL_Joystick *Joy;		//	SDL joystick
        SDL_Event Event;
        bool Start, Select, Up, Down, Left, Right, A, B, X, Y, L, R;
    #ifdef PLATFORM_PC
        bool Quit;
    #endif
        Vector2di deadZone;
        float scaler;
        Vector2di leftStick;
        Vector2di rightStick;
        Vector2di mouse;
        Vector2di oldMouse;
        bool leftClick, rightClick;

    #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
        bool Click, VolumeUp, VolumeDown,UpLeft, UpRight, DownLeft, DownRight;
    #endif
        KeyMapper mapper;
        bool mapLoaded;

    #if defined(PLATFORM_PANDORA)
        #define DEV_NUBL 1
        #define DEV_NUBR 2
        #define PND_NUBL "vsense66"
        #define PND_NUBR "vsense67"
        #define NUB_CUTOFF 5
        #define NUB_SCALE  10

        int PND_OpenEventDeviceByName( char device_name[] );
        void PND_ReadEvents( int fd, int device );
        void PND_CheckEvent( struct input_event *event, int device );

        int fd_nubL, fd_nubR, rd, version, i;
        struct input_event ev[64];
        char event_name[30];
        char dev_name[256]; //= "Unknown";
        unsigned short id[4];
        Vector2di nubL, nubR;
    #endif
};

#endif // SIMPLEJOY_H
