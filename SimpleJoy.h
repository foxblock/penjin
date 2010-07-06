#ifndef SIMPLEJOY_H
#define SIMPLEJOY_H

#include "PenjinTypes.h"
#include "KeyMapper.h"
#include <iostream>
using std::cout;
/*
TODO: Add Wii Controls/GBA/NDS etc
*/
class SimpleJoy
{
    public:
        enum sjSTATUS
        {
            sjRELEASED = 0,
            sjPRESSED = 1,
            sjHELD = 2
        };
        SimpleJoy();
        ~SimpleJoy();

        PENJIN_ERRORS loadControlMap(CRstring filename)
        {
            PENJIN_ERRORS t = mapper.loadControlMap(filename);
            if(t == PENJIN_OK)
                mapLoaded = true;
            return t;
        }

        PENJIN_ERRORS saveControlMap(CRstring filename)
        {
            return mapper.saveControlMap(filename);
        }

        void update();					//	Get current status of keyboard

        // Check button states
        bool isHeld(const sjSTATUS& bstat)const{return (bstat == sjHELD);}
        bool isPressed(const sjSTATUS& bstat)const{return (bstat == sjPRESSED);}
        bool isReleased(const sjSTATUS& bstat)const{return (bstat == sjRELEASED);}

        sjSTATUS isStart()const{return Start;}
        sjSTATUS isSelect()const{return Select;}
        sjSTATUS isUp()const{return Up;}
        sjSTATUS isDown()const{return Down;}
        sjSTATUS isLeft()const{return Left;}
        sjSTATUS isRight()const{return Right;}
        sjSTATUS isA()const{return A;}
        sjSTATUS isB()const{return B;}
        sjSTATUS isX()const{return X;}
        sjSTATUS isY()const{return Y;}
        sjSTATUS isL()const{return L;}
        sjSTATUS isR()const{return R;}
        /// The fabled ANY button.
        sjSTATUS isAny()const
        {
            if((A || B || X || Y || L || R || Start || Select) == sjPRESSED)
                return sjPRESSED;
            else if((A || B || X || Y || L || R || Start || Select) == sjHELD)
                return sjHELD;
            return sjRELEASED;
        }
    #ifndef PLATFORM_GP2X
        sjSTATUS isQuit()const{return Quit;}
    #endif
    #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
        /// GP2X Buttons
        sjSTATUS isClick()const{return Click;}
        sjSTATUS isVolumeUp()const{return VolumeUp;}
        sjSTATUS isVolumeDown()const{return VolumeDown;}
        sjSTATUS isUpLeft()const{return UpLeft;}
        sjSTATUS isUpRight()const{return UpRight;}
        sjSTATUS isDownLeft()const{return DownLeft;}
        sjSTATUS isDownRight()const{return DownRight;}
    #else
        sjSTATUS isUpLeft()const{return sjRELEASED;}
        sjSTATUS isUpRight()const{return sjRELEASED;}
        sjSTATUS isDownLeft()const{return sjRELEASED;}
        sjSTATUS isDownRight()const{return sjRELEASED;}
    #endif

        /// Keyboard passthrough
        sjSTATUS isKey(CRstring k)
        {
            KeyMapKey t(k);
            for(int i = storeKeys.size()-1; i>=0;--i)
            {
                if(t.getKey() == storeKeys.at(i).key.getKey())
                    return storeKeys.at(i).status;
            }
        }
        string isKeyLetter();

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
        sjSTATUS isLeftStick()const
        {
            if((isLeftStickDown() || isLeftStickLeft() || isLeftStickRight() || isLeftStickUp())==sjHELD)
                return sjHELD;
            else if((isLeftStickDown() || isLeftStickLeft() || isLeftStickRight() || isLeftStickUp())==sjPRESSED)
                return sjPRESSED;
            return sjRELEASED;
        }
        sjSTATUS isLeftStickUp()const
        {
            if(getLeftStickY() < -deadZone.y)
                return sjHELD;
            return sjRELEASED;
        }
        sjSTATUS isLeftStickDown()const
        {
            if(getLeftStickY() > deadZone.y)
                return sjHELD;
            return sjRELEASED;
        }
        sjSTATUS isLeftStickLeft()const
        {
            if(getLeftStickX() < -deadZone.x)
                return sjHELD;
            return sjRELEASED;
        }
        sjSTATUS isLeftStickRight()const
        {
            if(getLeftStickX() > deadZone.x)
                return sjHELD;
            return sjRELEASED;
        }

        sjSTATUS isRightStick()const
        {
            if((isRightStickDown() || isRightStickLeft() || isRightStickRight() || isRightStickUp())==sjHELD)
                return sjHELD;
            else if((isRightStickDown() || isRightStickLeft() || isRightStickRight() || isRightStickUp())==sjPRESSED)
                return sjPRESSED;
            return sjRELEASED;
        }
        sjSTATUS isRightStickUp()const
        {
            if(getRightStickY() < -deadZone.y)
                return sjHELD;
            return sjRELEASED;
        }
        sjSTATUS isRightStickDown()const
        {
            if(getRightStickY() > deadZone.y)
                return sjHELD;
            return sjRELEASED;
        }
        sjSTATUS isRightStickLeft()const
        {
            if(getRightStickX() < -deadZone.x)
                return sjHELD;
            return sjRELEASED;
        }
        sjSTATUS isRightStickRight()const
        {
            if(getRightStickX() > deadZone.x)
                return sjHELD;
            return sjRELEASED;
        }

        /// Mouse
        Vector2di getMouse()const{return mouse;}
        int getMouseX()const{return mouse.x;}
        int getMouseY()const{return mouse.y;}
        sjSTATUS isLeftClick()const{return leftClick;}
        sjSTATUS isRightClick()const{return rightClick;}
        /// TouchScreen - Just a wrapper to mouse
        Vector2di getTouch()const{return mouse;}
        int getTouchX()const{return mouse.x;}
        int getTouchY()const{return mouse.y;}
        sjSTATUS isTouch()const{return leftClick;}

		void clearEventQueue();
        void resetKeys();
        void resetDpad();
        void resetA();
        void resetB();
        void resetX();
        void resetY();
        void resetL();
        void resetR();

        /// Status
        void joystickStatus();

    private:
        void mappedDown(const SIMPLEJOY_MAP& map);
        void mappedUp(const SIMPLEJOY_MAP& map);
        void mappedMouseAxes(const SIMPLEJOY_MAP& map,CRuchar axis);
        void mappedJoyAxes(const SIMPLEJOY_MAP& map);

        sjSTATUS Start, Select, Up, Down, Left, Right, A, B, X, Y, L, R;
        struct tKey
        {
            KeyMapKey key;
            sjSTATUS status;
        };
        vector <tKey> storeKeys;
    #ifndef PLATFORM_GP2X
        sjSTATUS Quit;
    #endif
        Vector2di deadZone;
        float scaler;
        Vector2di leftStick;
        Vector2di rightStick;
        Vector2di mouse;
        Vector2di oldMouse;
        sjSTATUS leftClick, rightClick;

    #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
        sjSTATUS Click, VolumeUp, VolumeDown,UpLeft, UpRight, DownLeft, DownRight;
    #endif
        KeyMapper mapper;
        bool mapLoaded;

    #if defined(PLATFORM_PANDORA) && (defined(PENJIN_ES) || defined(PENJIN_ES2))
        #define DEV_NUBL 0
        #define DEV_NUBR 1
        #define DEV_KEYS 2
        #define DEV_GPIO 3
        #define DEV_TOUCH 4
        #define PND_NUBL "vsense66"
        #define PND_NUBR "vsense67"
        #define PND_KEYS "omap_twl4030keypad"
        #define PND_GPIO "gpio-keys"
        #define PND_TOUCH "touchscreen"
        #define NUB_CUTOFF 5
        #define NUB_SCALE  10

        int PND_OpenEventDeviceByName( const char device_name[] );
        void PND_ReadEvents( int fd, int device );
        void PND_CheckEvent( struct input_event *event, int device );

        int fd_nubL, fd_nubR, fd_keys, fd_gpio, fd_touch;
        int rd, version, i;
        struct input_event ev[64];
        uint currentEvent;          //  stores the currently checked event for mapping purposes.
        char event_name[30];
        char dev_name[256]; //= "Unknown";
        unsigned short id[4];
        //Vector2di nubL, nubR;
        // KEV nub code
        //void MappedNubAxes(const SIMPLEJOY_MAP& map, CRint axis);
    #else
        SDL_Joystick *Joy;		//	SDL joystick
        SDL_Event Event;
    #endif
};

#endif // SIMPLEJOY_H
