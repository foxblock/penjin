#include "SimpleJoy.h"


SimpleJoy::~SimpleJoy()
{
    if(Joy)
        SDL_JoystickClose(0);
}

SimpleJoy::SimpleJoy()
{
    mapLoaded = false;
   /* Check and open joystick device */
	if (SDL_NumJoysticks() > 0) {
		Joy = SDL_JoystickOpen(0);
		if(!Joy) {
			//cout << ErrorHandler().getErrorString();
		}
	}
    deadZone.x = 3200;
    deadZone.y = 3200;
    scaler = 0.0001f;

    resetKeys();
#ifdef _DEBUG
    joystickStatus();
#endif

}

void SimpleJoy::update()
{
    if(!mapLoaded)
    {
        mapper.loadDefaultMap();
        mapLoaded = true;
    }
    while (SDL_PollEvent(&Event))
    {
        #ifdef PLATFORM_PC
        if(Event.type == SDL_QUIT)
           Quit = true;
        #endif
        for(int b = mapper.size()-1; b>=0;--b)
        {
            KEY_MAP_DEVICE device = mapper.keys[b]->getDevice();
            if(device == DEV_KEYBOARD)
            {
                if(((KeyMapSDLKey*)mapper.keys[b])->getkey() == Event.key.keysym.sym)
                {
                    if(Event.type == SDL_KEYDOWN)
                        mappedDown(mapper.keys[b]->getTarget());
                    else if(Event.type == SDL_KEYUP)
                        mappedUp(mapper.keys[b]->getTarget());
                }
            }
            else if(device == DEV_MOUSE_AXIS)
            {
                // Axis may be changed
                if(Event.type == SDL_MOUSEMOTION)
                    mappedMouseAxes(((KeyMapMouseAxis*)mapper.keys[b])->getTarget(),((KeyMapMouseAxis*)mapper.keys[b])->getAxis());
            }
            else if(device == DEV_MOUSE_BUTTON)
            {
                MouseButtons::SDL_MOUSE_BUTTONS button = ((KeyMapMouseButton*)mapper.keys[b])->getButton();
                if(button == Event.button.button)
                {
                    //oldMouse = mouse;
                    // Buttons may have been pressed
                    if(Event.type == SDL_MOUSEBUTTONDOWN)
                        mappedDown(mapper.keys[b]->getTarget());
                    else if(Event.type == SDL_MOUSEBUTTONUP)
                        mappedUp(mapper.keys[b]->getTarget());
                }
            }
            else if(device == DEV_JOYSTICK_AXIS)
            {
                // Axis may be changed
                if(((KeyMapJoyAxis*)mapper.keys[b])->getAxis() == Event.jaxis.axis)
                {
                    if(Event.type == SDL_JOYAXISMOTION)
                        mappedJoyAxes(((KeyMapJoyAxis*)mapper.keys[b])->getTarget());
                }

            }
            else if (device == DEV_JOYSTICK_HAT)
            {
                if(Event.type == SDL_JOYHATMOTION)
                {
                    if(((KeyMapHat*)mapper.keys[b])->getDirection() & Event.jhat.value)
                        mappedDown(((KeyMapHat*)mapper.keys[b])->getTarget());
                    else
                        mappedUp(((KeyMapHat*)mapper.keys[b])->getTarget());
                }
            }
            else if (device == DEV_DIGITAL_JOYSTICK_AXIS)
            {
                if(((KeyMapDigitalJoyAxis*)mapper.keys[b])->getAxis() == Event.jaxis.axis)
                {
                    #ifdef _DEBUG
                    cout << "DAXIS: " << Event.jaxis.value << "  " << ((KeyMapDigitalJoyAxis*)mapper.keys[b])->getTrigger() << endl;
                    #endif
                    if(Event.type == SDL_JOYAXISMOTION)
                    {

                        if(Event.jaxis.value == ((KeyMapDigitalJoyAxis*)mapper.keys[b])->getTrigger())
                            mappedDown(((KeyMapDigitalJoyAxis*)mapper.keys[b])->getTarget());
                        else
                            mappedUp(((KeyMapDigitalJoyAxis*)mapper.keys[b])->getTarget());
                    }
                }
            }
            else if(device == DEV_JOYSTICK_BUTTON)
            {
                if(((KeyMapJoyButton*)mapper.keys[b])->getButton() == Event.jbutton.button)
                {
                    // Buttons may have been pressed
                    if(Event.type == SDL_JOYBUTTONDOWN)
                        mappedDown(mapper.keys[b]->getTarget());
                    else if(Event.type == SDL_JOYBUTTONUP)
                        mappedUp(mapper.keys[b]->getTarget());
                }
            }
        }
 /*       switch(Event.type)
        {
            case SDL_JOYBUTTONDOWN:     joyDown(Event.jbutton.button); break;
            case SDL_JOYBUTTONUP:       joyUp(Event.jbutton.button); break;
            case SDL_JOYAXISMOTION:     joyAxisMotion(Event.jaxis); break;
            case SDL_MOUSEBUTTONDOWN:   mouseButtonDown(Event.button.x, Event.button.y);break;
            case SDL_MOUSEBUTTONUP:     mouseButtonUp(Event.button.x, Event.button.y);break;
            case SDL_MOUSEMOTION:       mouseMotion(Event.motion.x, Event.motion.y);break;
        }*/
    }
}

void SimpleJoy::mappedJoyAxes(const SIMPLEJOY_MAP& map)
{
    switch(map)
    {
        #ifdef PENJIN_FIXED
            case SJ_LEFTSTICK_X:    leftStick.x = fixedpoint::fix2int(Event.jaxis.value * scaler);break;
            case SJ_LEFTSTICK_Y:    leftStick.y = fixedpoint::fix2int(Event.jaxis.value * scaler);break;
            case SJ_RIGHTSTICK_X:   rightStick.x = fixedpoint::fix2int(Event.jaxis.value * scaler);break;
            case SJ_RIGHTSTICK_Y:   rightStick.y = fixedpoint::fix2int(Event.jaxis.value * scaler);break;
            case SJ_MOUSE_X:        oldMouse.x = mouse.x;mouse.x += fixedpoint::fix2int(Event.jaxis.value * scaler);break;
            case SJ_MOUSE_Y:        oldMouse.y = mouse.y;mouse.y += fixedpoint::fix2int(Event.jaxis.value * scaler);break;

        #else
            case SJ_LEFTSTICK_X:    leftStick.x = Event.jaxis.value * scaler;break;
            case SJ_LEFTSTICK_Y:    leftStick.y = Event.jaxis.value * scaler;break;
            case SJ_RIGHTSTICK_X:   rightStick.x = Event.jaxis.value * scaler;break;
            case SJ_RIGHTSTICK_Y:   rightStick.y = Event.jaxis.value * scaler;break;
            case SJ_MOUSE_X:        oldMouse.x = mouse.x;mouse.x += Event.jaxis.value * scaler;break;
            case SJ_MOUSE_Y:        oldMouse.y = mouse.y;mouse.y += Event.jaxis.value * scaler;break;
        #endif
    }
}

void SimpleJoy::mappedMouseAxes(const SIMPLEJOY_MAP& map,CRuchar axis)
{
    if(axis == 0 && Event.motion.xrel != 0)
        switch(map)
        {
            case SJ_LEFTSTICK_X:    leftStick.x = Event.motion.xrel;break;
            case SJ_LEFTSTICK_Y:    leftStick.y = Event.motion.xrel;break;
            case SJ_RIGHTSTICK_X:   rightStick.x = Event.motion.xrel;break;
            case SJ_RIGHTSTICK_Y:   rightStick.y = Event.motion.xrel;break;
            case SJ_MOUSE_X:        oldMouse.x = mouse.x;mouse.x = Event.motion.x;break;
            case SJ_MOUSE_Y:        oldMouse.y = mouse.y;mouse.y = Event.motion.x;break;
        }
    if(axis == 1 && Event.motion.yrel != 0)
        switch(map)
        {
            case SJ_LEFTSTICK_X:    leftStick.x = Event.motion.yrel;break;
            case SJ_LEFTSTICK_Y:    leftStick.y = Event.motion.yrel;break;
            case SJ_RIGHTSTICK_X:   rightStick.x = Event.motion.yrel;break;
            case SJ_RIGHTSTICK_Y:   rightStick.y = Event.motion.yrel;break;
            case SJ_MOUSE_X:        oldMouse.x = mouse.x;mouse.x = Event.motion.y;break;
            case SJ_MOUSE_Y:        oldMouse.y = mouse.y;mouse.y = Event.motion.y;break;
        }
}

void SimpleJoy::mappedDown(const SIMPLEJOY_MAP& map)
{
    switch(map)
    {
        case SJ_UP:             Up = true;break;
        case SJ_DOWN:           Down = true;break;
        case SJ_LEFT:           Left = true;break;
        case SJ_RIGHT:          Right = true;break;
        #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
        case SJ_UPLEFT:         UpLeft = true;break;
        case SJ_UPRIGHT:        UpRight = true;break;
        case SJ_DOWNLEFT:       DownLeft = true;break;
        case SJ_DOWNRIGHT:      DownRight = true;break;
        case SJ_VOLUP:          VolumeUp = true;break;
        case SJ_VOLDOWN:        VolumeDown = true;break;
        case SJ_CLICK:          Click = true;break;
        #endif
        case SJ_A:              A = true;break;
        case SJ_B:              B = true;break;
        case SJ_X:              X = true;break;
        case SJ_Y:              Y = true;break;
        case SJ_L:              L = true;break;
        case SJ_R:              R = true;break;
        case SJ_START:          Start = true;break;
        case SJ_SELECT:         Select = true;break;

        /*case SJ_LID:          Lid = true;break;
        case SJ_LEFTSTICK_X:    = true;break;
        case SJ_LEFTSTICK_Y:    = true;break;
        case SJ_RIGHTSTICK_X:   = true;break;
        case SJ_RIGHTSTICK_Y:   = true;break;
        case SJ_MOUSE_X:         = true;break;
        case SJ_MOUSE_Y:         = true;break;*/
        case SJ_MOUSE_LEFT:     leftClick = true;break;
        //case SJ_MOUSE_CENTRE: = true;break;
        case SJ_MOUSE_RIGHT:    rightClick = true;break;
    }
}

void SimpleJoy::mappedUp(const SIMPLEJOY_MAP& map)
{
    switch(map)
    {
        case SJ_UP:             Up = false;break;
        case SJ_DOWN:           Down = false;break;
        case SJ_LEFT:           Left = false;break;
        case SJ_RIGHT:          Right = false;break;
        #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
        case SJ_UPLEFT:         UpLeft = false;break;
        case SJ_UPRIGHT:        UpRight = false;break;
        case SJ_DOWNLEFT:       DownLeft = false;break;
        case SJ_DOWNRIGHT:      DownRight = false;break;
        case SJ_VOLUP:          VolumeUp = false;break;
        case SJ_VOLDOWN:        VolumeDown = false;break;
        case SJ_CLICK:          Click = false;break;
        #endif
        case SJ_A:              A = false;break;
        case SJ_B:              B = false;break;
        case SJ_X:              X = false;break;
        case SJ_Y:              Y = false;break;
        case SJ_L:              L = false;break;
        case SJ_R:              R = false;break;

        case SJ_START:          Start = false;break;
        case SJ_SELECT:         Select = false;break;

        /*case SJ_LID:          Lid = false;break;
        case SJ_LEFTSTICK_X:    = false;break;
        case SJ_LEFTSTICK_Y:    = false;break;
        case SJ_RIGHTSTICK_X:   = false;break;
        case SJ_RIGHTSTICK_Y:   = false;break;
        case SJ_MOUSE_X:         = false;break;
        case SJ_MOUSE_Y:         = false;break;*/
        case SJ_MOUSE_LEFT:     leftClick = false;break;
        //case SJ_MOUSE_CENTRE: = false;break;
        case SJ_MOUSE_RIGHT:    rightClick = false;break;
    }
}


void SimpleJoy::resetKeys()
{
    SDL_Event event;
    while(SDL_PollEvent(&event));   //  Clears the event queue

    Start=Select=Up=Down=Left=Right=A=B=X=Y=L=R=false;
    #ifdef PLATFORM_PC
        Quit = false;
    #endif
    #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
        VolumeUp=VolumeDown=Click=UpLeft=UpRight=DownLeft=DownRight=false;
    #endif
        leftStick.x = 0;
        leftStick.y = 0;
        rightStick.x = 0;
        rightStick.y = 0;
        mouse.x = 0;
        mouse.y = 0;
        leftClick=rightClick=false;
}

void SimpleJoy::joystickStatus()
{
    std::cout << "Penjin found " << SDL_NumJoysticks() << " joysticks!\n";
    for(int i=0 ; i<SDL_NumJoysticks() ; i++)
    {
        std::cout << SDL_JoystickName(i) << "\n";
        std::cout << "Axis:\t\t" << SDL_JoystickNumAxes(Joy) << "\n";
        std::cout << "Trackballs:\t" << SDL_JoystickNumBalls(Joy) << "\n";
        std::cout << "Hats:\t\t" << SDL_JoystickNumHats(Joy) << "\n";
        std::cout << "Buttons:\t" << SDL_JoystickNumButtons(Joy) << "\n";
    }
}
