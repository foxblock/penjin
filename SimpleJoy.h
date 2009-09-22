#ifndef SIMPLEJOY_H
#define SIMPLEJOY_H

//#include "KeyboardDefines.h"
#include "PenjinTypes.h"
#include "KeyMapper.h"
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
};

#endif // SIMPLEJOY_H
