/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "SimpleJoy.h"

#include "StringUtility.h"
#include "ErrorHandler.h"

SimpleJoy::~SimpleJoy()
{
#if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
// && (defined(PENJIN_ES) || defined(PENJIN_ES2))
	if( fd_nubL > 0 )
		close(fd_nubL );
	if( fd_nubR > 0 )
		close(fd_nubR );
	if( fd_keys > 0 )
		close(fd_keys );
	if( fd_gpio > 0 )
		close(fd_gpio );
    if(fd_touch > 0)
        close(fd_touch);
#else
    if(Joy)
    {
    	int i = 0;
        SDL_Joystick **temp = Joy;
        while (*temp) {
            SDL_JoystickClose(*temp);
            ++i;
            ++temp;
        }
        Joy = NULL;
    }
#endif
    delete [] players;
}

SimpleJoy::SimpleJoy()
{
    #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
    // && (defined(PENJIN_ES) || defined(PENJIN_ES2))
        // Open Pandora analog nub's
        fd_nubL = PND_OpenEventDeviceByName(PND_NUBL);
        fd_nubR = PND_OpenEventDeviceByName(PND_NUBR);
        fd_keys = PND_OpenEventDeviceByName(PND_KEYS);
        fd_gpio = PND_OpenEventDeviceByName(PND_GPIO);
        fd_touch = PND_OpenEventDeviceByName(PND_TOUCH);
        currentEvent = 0;
        //  open pointercal file
        ifstream ifile("/etc/pointercal");//load infile
        if(!ifile.is_open())
        {
            ErrorHandler().killApp(PENJIN_FILE_NOT_FOUND);
        }
        //  extract values
        for(uint i = 0; i<7; ++i)
        {
            ifile >> pointercal[i];
            cout << "i:" << i << "Pcal:" << pointercal[i] << endl;

            //  hack
            if(pointercal[i] == 0)
            {
                cout << "Hacked Values used!" << endl;
                if(i == 0)
                    pointercal[0] = -13868;
                else if(i == 1)
                    pointercal[1] = 53;
                else if(i == 2)
                    pointercal[2] = 54178276;
                else if(i == 3)
                    pointercal[3] = 43;
                else if(i == 4)
                    pointercal[4] = -8681;
                else if(i == 5)
                    pointercal[5] = 32884616;
                else if(i == 6)
                    pointercal[6] = 65536;
            }
        }

        if(ifile.is_open())
        {
            ifile.close();
        }
    #else
        SDL_JoystickEventState(SDL_ENABLE);

       /* Check and open joystick device */
       // New code magic opens multiple joysticks.  Unlock multiple simultaneous players, or dual stick single player
        int i = SDL_NumJoysticks();
        Joy = new SDL_Joystick*[i+1];
        Joy[i] = NULL;
        for (int count = 0; count < i; ++count) {
            Joy[count] = SDL_JoystickOpen(count);
            if(!Joy[count]) {
                //cout << ErrorHandler().getErrorString();
            }
        }
    #endif

    //deadZone.x = 0;
    //deadZone.y = 0;
    //scaler = 1.0f;
    //mapLoaded = false;
    player = 0;
    players = NULL;
    numPlayers = 0;
    setNumPlayers(player+1);
    resetKeys();
#ifdef _DEBUG
    joystickStatus();
#endif
#if !defined(PLATFORM_PANDORA) || defined(PENJIN_SDL_INPUT)
	keyboardBuffer = NULL;
	keyboardMask = "";
#endif
}

void SimpleJoy::update()
{
    if(!players[player].mapLoaded)
    {
        players[player].mapper.loadDefaultMap();
        players[player].mapLoaded = true;
    }
	if (players[player].Start == sjPRESSED)
		players[player].Start = sjHELD;
	if (players[player].Select == sjPRESSED)
		players[player].Select = sjHELD;
	if (players[player].Up == sjPRESSED)
		players[player].Up = sjHELD;
	if (players[player].Down == sjPRESSED)
		players[player].Down = sjHELD;
	if (players[player].Left == sjPRESSED)
		players[player].Left = sjHELD;
	if (players[player].Right == sjPRESSED)
		players[player].Right = sjHELD;
	if (players[player].A == sjPRESSED)
		players[player].A = sjHELD;
	if (players[player].B == sjPRESSED)
		players[player].B = sjHELD;
	if (players[player].X == sjPRESSED)
		players[player].X = sjHELD;
	if (players[player].Y == sjPRESSED)
		players[player].Y = sjHELD;
	if (players[player].L == sjPRESSED)
		players[player].L = sjHELD;
	if (players[player].R == sjPRESSED)
		players[player].R = sjHELD;
	if (players[player].Quit == sjPRESSED)
		players[player].Quit = sjHELD;
	if (players[player].leftClick == sjPRESSED)
		players[player].leftClick = sjHELD;
	if (players[player].rightClick == sjPRESSED)
		players[player].rightClick = sjHELD;
	for (vector<tKey>::iterator I = players[player].storeKeys.begin(); I != players[player].storeKeys.end(); ++I)
		if (I->status == sjPRESSED)
			I->status = sjHELD;
#if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
	if (players[player].Click == sjPRESSED)
		players[player].Click = sjHELD;
	if (players[player].VolumeUp == sjPRESSED)
		players[player].VolumeUp = sjHELD;
	if (players[player].VolumeDown == sjPRESSED)
		players[player].VolumeDown = sjHELD;
	if (players[player].UpLeft == sjPRESSED)
		players[player].UpLeft = sjHELD;
	if (players[player].UpRight == sjPRESSED)
		players[player].UpRight = sjHELD;
	if (players[player].DownLeft == sjPRESSED)
		players[player].DownLeft = sjHELD;
	if (players[player].DownRight == sjPRESSED)
		players[player].DownRight = sjHELD;
#endif
#if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
// && (defined(PENJIN_ES) || defined(PENJIN_ES2))
	/// Read Pandora inputs
	PND_ReadEvents( fd_keys, DEV_KEYS );
	PND_ReadEvents( fd_gpio, DEV_GPIO );
	PND_ReadEvents( fd_nubL, DEV_NUBL );
	PND_ReadEvents( fd_nubR, DEV_NUBR );
	PND_ReadEvents( fd_touch,DEV_TOUCH);
#else
	while (SDL_PollEvent(&Event))
	{
		if(Event.type == SDL_QUIT)
		{
			if(players[player].Quit == sjRELEASED)
				players[player].Quit = sjPRESSED;
			else
				players[player].Quit = sjHELD;
		}
		if(Event.type == SDL_KEYDOWN)
		{
			KeyMapKey t(Event.key.keysym.sym);
			tKey k;
			k.key = t;
			k.status = sjPRESSED;
			players[player].storeKeys.push_back(k);
			if (keyboardBuffer && Event.key.keysym.unicode < 0x80)
			{
				if (Event.key.keysym.sym == SDLK_BACKSPACE && !keyboardBuffer->empty())
				{
					(*keyboardBuffer).erase(keyboardBuffer->end()-1);
					keyboardBufferChanged = true;
				}
				else if ((Event.key.keysym.unicode == 0x0A || Event.key.keysym.unicode >= 0x20) && (keyboardMask[0] == 0 || keyboardMask.find((char)Event.key.keysym.unicode) != string::npos))
				{
					*keyboardBuffer += (char)Event.key.keysym.unicode;
					keyboardBufferChanged = true;
				}
			}
		}
		else if(Event.type == SDL_KEYUP)
		{
			for (vector<tKey>::iterator I = players[player].storeKeys.begin(); I != players[player].storeKeys.end(); ++I)
			{
				if (I->key.getKey() == Event.key.keysym.sym)
				{
					players[player].storeKeys.erase(I);
					break;
				}
			}
		}
		for(int b = players[player].mapper.size()-1; b>=0;--b)
		{
			KEY_MAP_DEVICE device = players[player].mapper.keys[b]->getDevice();
			if(device == DEV_KEYBOARD)
			{
				if(((KeyMapKey*)players[player].mapper.keys[b])->getKey() == Event.key.keysym.sym)
				{
					if(Event.type == SDL_KEYDOWN)
						mappedDown(players[player].mapper.keys[b]->getTarget());
					else if(Event.type == SDL_KEYUP)
						mappedUp(players[player].mapper.keys[b]->getTarget());
				}
			}
			else if(device == DEV_MOUSE_AXIS)
			{
				// Axis may be changed
				if(Event.type == SDL_MOUSEMOTION)
					mappedMouseAxes(((KeyMapMouseAxis*)players[player].mapper.keys[b])->getTarget(),((KeyMapMouseAxis*)players[player].mapper.keys[b])->getAxis());
			}
			else if(device == DEV_MOUSE_BUTTON)
			{
				MouseButtons::SDL_MOUSE_BUTTONS button = ((KeyMapMouseButton*)players[player].mapper.keys[b])->getButton();
				if(button == Event.button.button)
				{
					//oldMouse = mouse;
					// Buttons may have been pressed
					if(Event.type == SDL_MOUSEBUTTONDOWN)
						mappedDown(players[player].mapper.keys[b]->getTarget());
					else if(Event.type == SDL_MOUSEBUTTONUP)
						mappedUp(players[player].mapper.keys[b]->getTarget());
				}
			}
			else if(device == DEV_JOYSTICK_AXIS)
			{
				// Assume 2 axis per stick
				// TODO: never assume...
				int axis = Event.jaxis.which*2 + Event.jaxis.axis;
				#if defined(PLATFORM_PANDORA)
				axis -= 2; // The game buttons are technically joystick 0, even though they don't count as one...
				#endif
				// Axis may be changed
				if(((KeyMapJoyAxis*)players[player].mapper.keys[b])->getAxis() == axis)
				{
					if(Event.type == SDL_JOYAXISMOTION) {
						mappedJoyAxes(((KeyMapJoyAxis*)players[player].mapper.keys[b])->getTarget());
					}
				}
			}
			else if (device == DEV_JOYSTICK_HAT)
			{
				if(Event.type == SDL_JOYHATMOTION)
				{
					if(((KeyMapHat*)players[player].mapper.keys[b])->getDirection() & Event.jhat.value)
						mappedDown(((KeyMapHat*)players[player].mapper.keys[b])->getTarget());
					else
						mappedUp(((KeyMapHat*)players[player].mapper.keys[b])->getTarget());
				}
			}
			else if (device == DEV_DIGITAL_JOYSTICK_AXIS)
			{
				// Assume 2 axis per stick
				// TODO: never assume...
				int axis = Event.jaxis.which*2 + Event.jaxis.axis;
				#if defined(PLATFORM_PANDORA)
				axis -= 2; // The game buttons are technically joystick 0, even though they don't count as one...
				#endif
				if(((KeyMapDigitalJoyAxis*)players[player].mapper.keys[b])->getAxis() == axis)
				{
					#ifdef _DEBUG
					cout << "DAXIS: " << (Event.jaxis.value >> 8) << "  " << ((KeyMapDigitalJoyAxis*)players[player].mapper.keys[b])->getTrigger() << endl;
					#endif
					if(Event.type == SDL_JOYAXISMOTION)
					{

						if((Event.jaxis.value >> 8) == ((KeyMapDigitalJoyAxis*)players[player].mapper.keys[b])->getTrigger())
							mappedDown(((KeyMapDigitalJoyAxis*)players[player].mapper.keys[b])->getTarget());
						else
							mappedUp(((KeyMapDigitalJoyAxis*)players[player].mapper.keys[b])->getTarget());
					}
				}
			}
			else if(device == DEV_JOYSTICK_BUTTON)
			{
				// Assume 16 buttons per joystick
				// TODO: never assume...
				int button = Event.jbutton.which*16+Event.jbutton.button;
				if(((KeyMapJoyButton*)players[player].mapper.keys[b])->getButton() == button)
				{
					// Buttons may have been pressed
					if(Event.type == SDL_JOYBUTTONDOWN)
						mappedDown(players[player].mapper.keys[b]->getTarget());
					else if(Event.type == SDL_JOYBUTTONUP)
						mappedUp(players[player].mapper.keys[b]->getTarget());
				}
			}
		}
	}
#endif
}

#if !defined(PLATFORM_PANDORA) || defined(PENJIN_SDL_INPUT)
string SimpleJoy::isKeyLetter()
{
    for(int i = players[player].storeKeys.size()-1; i>=0;--i)
    {
        if(players[player].storeKeys.at(i).status != sjRELEASED && StringUtility::isLetter(players[player].storeKeys.at(i).key.getKey()))
        {
            string t;
            t.push_back(players[player].storeKeys.at(i).key.getKey());
            return t;
        }
    }
    return "NULL";
}

void SimpleJoy::pollKeyboardInput(string *buffer, CRstring mask)
{
	SDL_EnableUNICODE(1);
	keyboardBuffer = buffer;
	keyboardMask = mask;
	keyboardBufferChanged = false;
}

void SimpleJoy::stopKeyboardInput()
{
	SDL_EnableUNICODE(0);
	keyboardBuffer = NULL;
}

bool SimpleJoy::isPollingKeyboard()
{
	return keyboardBuffer != NULL;
}

bool SimpleJoy::keyboardBufferHasChanged()
{
	if (keyboardBufferChanged)
	{
		keyboardBufferChanged = false;
		return true;
	}
	return false;
}
#endif

void SimpleJoy::mappedJoyAxes(const SIMPLEJOY_MAP& map)
{
    switch(map)
    {
        #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
        // && (defined(PENJIN_ES) || defined(PENJIN_ES2))
                case SJ_LEFTSTICK_X:    players[player].leftStick.x = (ev[currentEvent].value >> 1) * players[player].scaler;break;
                case SJ_LEFTSTICK_Y:    players[player].leftStick.y = (ev[currentEvent].value >> 1) * players[player].scaler;break;
                case SJ_RIGHTSTICK_X:   players[player].rightStick.x = (ev[currentEvent].value >> 1) * players[player].scaler;break;
                case SJ_RIGHTSTICK_Y:   players[player].rightStick.y = (ev[currentEvent].value >> 1) * players[player].scaler;break;
//                case SJ_MOUSE_X:        players[player].oldMouse.x = players[player].mouse.x;players[player].mouse.x += Event.jaxis.value * players[player].scaler;break;
//                case SJ_MOUSE_Y:        players[player].oldMouse.y = players[player].mouse.y;players[player].mouse.y += Event.jaxis.value * players[player].scaler;break;

        #else
            #ifdef PENJIN_FIXED
                case SJ_LEFTSTICK_X:    players[player].leftStick.x = fixedpoint::fix2int((Event.jaxis.value >> 8) * players[player].scaler);break;
                case SJ_LEFTSTICK_Y:    players[player].leftStick.y = fixedpoint::fix2int((Event.jaxis.value >> 8) * players[player].scaler);break;
                case SJ_RIGHTSTICK_X:   players[player].rightStick.x = fixedpoint::fix2int((Event.jaxis.value >> 8) * players[player].scaler);break;
                case SJ_RIGHTSTICK_Y:   players[player].rightStick.y = fixedpoint::fix2int((Event.jaxis.value >> 8) * players[player].scaler);break;
                case SJ_MOUSE_X:        players[player].oldMouse.x = players[player].mouse.x;players[player].mouse.x += fixedpoint::fix2int((Event.jaxis.value >> 8) * players[player].scaler);break;
                case SJ_MOUSE_Y:        players[player].oldMouse.y = players[player].mouse.y;players[player].mouse.y += fixedpoint::fix2int((Event.jaxis.value >> 8) * players[player].scaler);break;

            #else
                case SJ_LEFTSTICK_X:    players[player].leftStick.x = (Event.jaxis.value >> 8) * players[player].scaler;break;
                case SJ_LEFTSTICK_Y:    players[player].leftStick.y = (Event.jaxis.value >> 8) * players[player].scaler;break;
                case SJ_RIGHTSTICK_X:   players[player].rightStick.x = (Event.jaxis.value >> 8) * players[player].scaler;break;
                case SJ_RIGHTSTICK_Y:   players[player].rightStick.y = (Event.jaxis.value >> 8) * players[player].scaler;break;
                case SJ_MOUSE_X:        players[player].oldMouse.x = players[player].mouse.x;players[player].mouse.x += (Event.jaxis.value >> 8) * players[player].scaler;break;
                case SJ_MOUSE_Y:        players[player].oldMouse.y = players[player].mouse.y;players[player].mouse.y += (Event.jaxis.value >> 8) * players[player].scaler;break;
            #endif
        #endif
        default: cout << "Unknown joystick mapping: " << map << endl; break;
    }
}

void SimpleJoy::mappedMouseAxes(const SIMPLEJOY_MAP& map,CRuchar axis)
{
    #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
    // && (defined(PENJIN_ES) || defined(PENJIN_ES2))
/*  -13868 53 54178276 43 -8681 32884616 65536
    This implementation is a linear transformation using 7 parameters (a, b, c, d, e, f and s)
    to transform the device coordinates (Xd, Yd) into screen coordinates (Xs, Ys) using the following equations:
    s*Xs = a*Xd + b*Yd + c
    s*Ys = d*Xd + e*Yd + f
 */
    #ifdef _DEBUG
        cout << "a:" << pointercal[0] << " b:" << pointercal[1] << " c:" << pointercal[2] << endl;
        cout << "d:" << pointercal[3] << " e:" << pointercal[4] << " f:" << pointercal[5] << endl;
        cout << "s:" << pointercal[6] << endl;
    #endif
        if(axis == 0 && ev[currentEvent].code == ABS_X)
        {
            int val = ((pointercal[0]*rawTS.x) + (pointercal[1]*rawTS.y) + pointercal[2])/pointercal[6];
            #ifdef PENJIN_SCALE2X
				val *= 0.5f;
            #endif
            #ifdef _DEBUG
            cout << "Calc_X:" << val << endl;
            #endif
            switch(map)
            {
                case SJ_LEFTSTICK_X:    players[player].leftStick.x = val;break;
                case SJ_LEFTSTICK_Y:    players[player].leftStick.y = val;break;
                case SJ_RIGHTSTICK_X:   players[player].rightStick.x = val;break;
                case SJ_RIGHTSTICK_Y:   players[player].rightStick.y = val;break;
                case SJ_MOUSE_X:        players[player].oldMouse.x = players[player].mouse.x;players[player].mouse.x = val;break;
                case SJ_MOUSE_Y:        players[player].oldMouse.y = players[player].mouse.y;players[player].mouse.y = val;break;
                default:                break;
            }
        }
        else if(axis == 1 && ev[currentEvent].code == ABS_Y)
        {
            int val = ((pointercal[3]*rawTS.x) + (pointercal[4]*rawTS.y) + pointercal[5])/pointercal[6];
            #ifdef PENJIN_SCALE2X
				val *= 0.5f;
            #endif
            #ifdef _DEBUG
            cout << "Calc_Y:" << val << endl;
            #endif
            switch(map)
            {
                case SJ_LEFTSTICK_X:    players[player].leftStick.x = val;break;
                case SJ_LEFTSTICK_Y:    players[player].leftStick.y = val;break;
                case SJ_RIGHTSTICK_X:   players[player].rightStick.x = val;break;
                case SJ_RIGHTSTICK_Y:   players[player].rightStick.y = val;break;
                case SJ_MOUSE_X:        players[player].oldMouse.x = players[player].mouse.x;players[player].mouse.x = val;break;
                case SJ_MOUSE_Y:        players[player].oldMouse.y = players[player].mouse.y;players[player].mouse.y = val;break;
                default:                break;
            }
        }
    #else
        if(axis == 0 && Event.motion.xrel != 0)
            switch(map)
            {
                case SJ_LEFTSTICK_X:
					players[player].leftStick.x = Event.motion.xrel;
					#ifdef PENJIN_SCALE2X
					players[player].leftStick.x *= 0.5f;
					#endif
					break;
                case SJ_LEFTSTICK_Y:
                	players[player].leftStick.y = Event.motion.xrel;
					#ifdef PENJIN_SCALE2X
					players[player].leftStick.y *= 0.5f;
					#endif
                	break;
                case SJ_RIGHTSTICK_X:
                	players[player].rightStick.x = Event.motion.xrel;
					#ifdef PENJIN_SCALE2X
					players[player].rightStick.x *= 0.5f;
					#endif
                	break;
                case SJ_RIGHTSTICK_Y:
                	players[player].rightStick.y = Event.motion.xrel;
					#ifdef PENJIN_SCALE2X
					players[player].rightStick.y *= 0.5f;
					#endif
                	break;
                case SJ_MOUSE_X:
                	players[player].oldMouse.x = players[player].mouse.x;
                	players[player].mouse.x = Event.motion.x;
					#ifdef PENJIN_SCALE2X
					players[player].mouse.x *= 0.5f;
					#endif
                	break;
                case SJ_MOUSE_Y:
                	players[player].oldMouse.y = players[player].mouse.y;
                	players[player].mouse.y = Event.motion.x;
					#ifdef PENJIN_SCALE2X
					players[player].mouse.y *= 0.5f;
					#endif
                	break;
                default:
                	break;
            }
        if(axis == 1 && Event.motion.yrel != 0)
            switch(map)
            {
                case SJ_LEFTSTICK_X:
					players[player].leftStick.x = Event.motion.yrel;
					#ifdef PENJIN_SCALE2X
					players[player].leftStick.x *= 0.5f;
					#endif
					break;
                case SJ_LEFTSTICK_Y:
                	players[player].leftStick.y = Event.motion.yrel;
					#ifdef PENJIN_SCALE2X
					players[player].leftStick.y *= 0.5f;
					#endif
                	break;
                case SJ_RIGHTSTICK_X:
                	players[player].rightStick.x = Event.motion.yrel;
					#ifdef PENJIN_SCALE2X
					players[player].rightStick.x *= 0.5f;
					#endif
                	break;
                case SJ_RIGHTSTICK_Y:
                	players[player].rightStick.y = Event.motion.yrel;
					#ifdef PENJIN_SCALE2X
					players[player].rightStick.y *= 0.5f;
					#endif
                	break;
                case SJ_MOUSE_X:
                	players[player].oldMouse.x = players[player].mouse.x;
                	players[player].mouse.x = Event.motion.y;
					#ifdef PENJIN_SCALE2X
					players[player].mouse.x *= 0.5f;
					#endif
                	break;
                case SJ_MOUSE_Y:
                	players[player].oldMouse.y = players[player].mouse.y;
                	players[player].mouse.y = Event.motion.y;
					#ifdef PENJIN_SCALE2X
					players[player].mouse.y *= 0.5f;
					#endif
                	break;
                default:
                	break;
            }
    #endif
}

void SimpleJoy::mappedDown(const SIMPLEJOY_MAP& map)
{
    switch(map)
    {
        case SJ_UP:             players[player].Up = sjPRESSED; break;
        case SJ_DOWN:           players[player].Down = sjPRESSED; break;
        case SJ_LEFT:           players[player].Left = sjPRESSED; break;
        case SJ_RIGHT:          players[player].Right = sjPRESSED; break;
        #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
        case SJ_UPLEFT:         players[player].UpLeft = sjPRESSED; break;
        case SJ_UPRIGHT:        players[player].UpRight = sjPRESSED; break;
        case SJ_DOWNLEFT:       players[player].DownLeft = sjPRESSED; break;
        case SJ_DOWNRIGHT:      players[player].DownRight = sjPRESSED; break;
        case SJ_VOLUP:          players[player].VolumeUp = sjPRESSED; break;
        case SJ_VOLDOWN:        players[player].VolumeDown = sjPRESSED; break;
        case SJ_CLICK:          players[player].Click = sjPRESSED; break;
        #endif
        case SJ_A:              players[player].A = sjPRESSED; break;
        case SJ_B:              players[player].B = sjPRESSED; break;
        case SJ_X:              players[player].X = sjPRESSED; break;
        case SJ_Y:              players[player].Y = sjPRESSED; break;
        case SJ_L:              players[player].L = sjPRESSED; break;
        case SJ_R:              players[player].R = sjPRESSED; break;
        case SJ_START:          players[player].Start = sjPRESSED; break;
        case SJ_SELECT:         players[player].Select = sjPRESSED; break;

        /*case SJ_LID:          Lid = true;break;
        case SJ_LEFTSTICK_X:    = true;break;
        case SJ_LEFTSTICK_Y:    = true;break;
        case SJ_RIGHTSTICK_X:   = true;break;
        case SJ_RIGHTSTICK_Y:   = true;break;
        case SJ_MOUSE_X:         = true;break;
        case SJ_MOUSE_Y:         = true;break;*/
        case SJ_MOUSE_LEFT:     players[player].leftClick = sjPRESSED; break;
        //case SJ_MOUSE_CENTRE: = true;break;
        case SJ_MOUSE_RIGHT:    players[player].rightClick = sjPRESSED; break;
		case SJ_MOUSE_WHEELDOWN:--players[player].wheel; break;
        case SJ_MOUSE_WHEELUP:	++players[player].wheel; break;

        default:                break;
    }
}

void SimpleJoy::mappedUp(const SIMPLEJOY_MAP& map)
{
    switch(map)
    {
        case SJ_UP:             players[player].Up = sjRELEASED;break;
        case SJ_DOWN:           players[player].Down = sjRELEASED;break;
        case SJ_LEFT:           players[player].Left = sjRELEASED;break;
        case SJ_RIGHT:          players[player].Right = sjRELEASED;break;
        #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
        case SJ_UPLEFT:         players[player].UpLeft = sjRELEASED;break;
        case SJ_UPRIGHT:        players[player].UpRight = sjRELEASED;break;
        case SJ_DOWNLEFT:       players[player].DownLeft = sjRELEASED;break;
        case SJ_DOWNRIGHT:      players[player].DownRight = sjRELEASED;break;
        case SJ_VOLUP:          players[player].VolumeUp = sjRELEASED;break;
        case SJ_VOLDOWN:        players[player].VolumeDown = sjRELEASED;break;
        case SJ_CLICK:          players[player].Click = sjRELEASED;break;
        #endif
        case SJ_A:              players[player].A = sjRELEASED;break;
        case SJ_B:              players[player].B = sjRELEASED;break;
        case SJ_X:              players[player].X = sjRELEASED;break;
        case SJ_Y:              players[player].Y = sjRELEASED;break;
        case SJ_L:              players[player].L = sjRELEASED;break;
        case SJ_R:              players[player].R = sjRELEASED;break;
        case SJ_START:          players[player].Start = sjRELEASED;break;
        case SJ_SELECT:         players[player].Select = sjRELEASED;break;

        /*case SJ_LID:          Lid = sjRELEASED;break;
        case SJ_LEFTSTICK_X:    = sjRELEASED;break;
        case SJ_LEFTSTICK_Y:    = sjRELEASED;break;
        case SJ_RIGHTSTICK_X:   = sjRELEASED;break;
        case SJ_RIGHTSTICK_Y:   = sjRELEASED;break;
        case SJ_MOUSE_X:         = sjRELEASED;break;
        case SJ_MOUSE_Y:         = sjRELEASED;break;*/
        case SJ_MOUSE_LEFT:     players[player].leftClick = sjRELEASED;
        #ifdef PENJIN_PANDORA_TOUCHSCREEN_FIX
        						players[player].leftClickNeedsRelease = false;
        #endif // PENJIN_PANDORA_TOUCHSCREEN_FIX
								break;
        //case SJ_MOUSE_CENTRE: = sjRELEASED;break;
        case SJ_MOUSE_RIGHT:    players[player].rightClick = sjRELEASED;break;
        default:                break;
    }
}

void SimpleJoy::clearEventQueue()
{
    #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
    // && (defined(PENJIN_ES) || defined(PENJIN_ES2))

    #else
        SDL_Event event;
        while(SDL_PollEvent(&event));	//  Clears the event queue
    #endif
}
void SimpleJoy::resetKeys()
{
	clearEventQueue();

    players[player].Start=players[player].Select=players[player].Up=players[player].Down=players[player].Left=players[player].Right
		=players[player].A=players[player].B=players[player].X=players[player].Y=players[player].L=players[player].R=sjRELEASED;
    players[player].Quit = sjRELEASED;
    #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
        players[player].VolumeUp=players[player].VolumeDown=players[player].Click=players[player].UpLeft=players[player].UpRight
        =players[player].DownLeft=players[player].DownRight=sjRELEASED;
    #endif
	players[player].leftStick.x = 0;
	players[player].leftStick.y = 0;
	players[player].rightStick.x = 0;
	players[player].rightStick.y = 0;
	#ifdef PENJIN_PANDORA_TOUCHSCREEN_FIX
	if (players[player].leftClick != sjRELEASED)
		players[player].leftClickNeedsRelease = true;
	#endif // PENJIN_PANDORA_TOUCHSCREEN_FIX
	players[player].leftClick=players[player].rightClick=sjRELEASED;
	players[player].wheel = 0;
	players[player].storeKeys.clear();
}
void SimpleJoy::resetKey(CRstring k)
{
	clearEventQueue();
	KeyMapKey t(k);
	for (vector<tKey>::iterator I = players[player].storeKeys.begin(); I != players[player].storeKeys.end(); ++I)
	{
		if (I->key.getKey() == t.getKey())
		{
			players[player].storeKeys.erase(I);
			return;
		}
	}
}
#if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
void SimpleJoy::resetKey(__u16 k)
#else
void SimpleJoy::resetKey(SDLKey k)
#endif
{
	clearEventQueue();
	for (vector<tKey>::iterator I = players[player].storeKeys.begin(); I != players[player].storeKeys.end(); ++I)
	{
		if (I->key.getKey() == k)
		{
			players[player].storeKeys.erase(I);
			return;
		}
	}
}
void SimpleJoy::resetMousePosition()
{
    clearEventQueue();
	players[player].mouse.x = 0;
	players[player].mouse.y = 0;
}
void SimpleJoy::resetMouseButtons()
{
    clearEventQueue();
	#ifdef PENJIN_PANDORA_TOUCHSCREEN_FIX
	if (players[player].leftClick != sjRELEASED)
		players[player].leftClickNeedsRelease = true;
	#endif // PENJIN_PANDORA_TOUCHSCREEN_FIX
    players[player].leftClick=players[player].rightClick=sjRELEASED;
}
void SimpleJoy::resetMouseWheel()
{
	clearEventQueue();
	players[player].wheel = 0;
}

void SimpleJoy::resetDpad()
{
    clearEventQueue();
    players[player].Up=players[player].Down=players[player].Left=players[player].Right=sjRELEASED;
    #if defined(PLATFORM_GP2X) || defined(PLATFORM_PC)
        players[player].UpLeft=players[player].UpRight=players[player].DownLeft=players[player].DownRight=sjRELEASED;
    #endif
}
void SimpleJoy::resetA()
{
    clearEventQueue();
    players[player].A=sjRELEASED;
}
void SimpleJoy::resetB()
{
    clearEventQueue();
    players[player].B=sjRELEASED;
}
void SimpleJoy::resetX()
{
	clearEventQueue();
    players[player].X=sjRELEASED;
}
void SimpleJoy::resetY()
{
	clearEventQueue();
    players[player].Y=sjRELEASED;
}
void SimpleJoy::resetL()
{
	clearEventQueue();
    players[player].L=sjRELEASED;
}
void SimpleJoy::resetR()
{
	clearEventQueue();
    players[player].R=sjRELEASED;
}

void SimpleJoy::resetStart()
{
    clearEventQueue();
    players[player].Start=sjRELEASED;
}

void SimpleJoy::resetSelect()
{
    clearEventQueue();
    players[player].Select=sjRELEASED;
}

void SimpleJoy::resetUp()
{
    clearEventQueue();
    players[player].Up=sjRELEASED;
}

void SimpleJoy::resetDown()
{
    clearEventQueue();
    players[player].Down=sjRELEASED;
}

void SimpleJoy::resetLeft()
{
    clearEventQueue();
    players[player].Left=sjRELEASED;
}

void SimpleJoy::resetRight()
{
    clearEventQueue();
    players[player].Right=sjRELEASED;
}

void SimpleJoy::joystickStatus()
{
    #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
    // && (defined(PENJIN_ES) || defined(PENJIN_ES2))

    #else
        std::cout << "Penjin found " << SDL_NumJoysticks() << " joysticks!" << std::endl;
    	int i = 0;
        SDL_Joystick **temp = Joy;
        while (*temp != NULL) {
        	std::cout << "Joystick #" << i << std::endl;
            std::cout << SDL_JoystickName(i) << std::endl;
            std::cout << "Axis:\t\t" << SDL_JoystickNumAxes(*temp) << std::endl;
            std::cout << "Trackballs:\t" << SDL_JoystickNumBalls(*temp) << std::endl;
            std::cout << "Hats:\t\t" << SDL_JoystickNumHats(*temp) << std::endl;
            std::cout << "Buttons:\t" << SDL_JoystickNumButtons(*temp) << std::endl;
            ++i;
            ++temp;
        }
    #endif
}

#if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
// && (defined(PENJIN_ES) || defined(PENJIN_ES2))
int SimpleJoy::PND_OpenEventDeviceByName( const char device_name[] )
{
	int fd;

	for (i = 0; 1; i++)
	{
		snprintf( event_name, sizeof(event_name), "/dev/input/event%d", i );
		//printf( "Device: %s\n", event_name );
		if ((fd = open(event_name, O_RDONLY |  O_NDELAY)) < 0) {
			perror("ERROR: Could not open device");
			return 0;
		}
		if (fd < 0) break; // no more devices

		ioctl(fd, EVIOCGNAME(sizeof(dev_name)), dev_name);
		if (strcmp(dev_name, device_name) == 0)
		{
			if (ioctl(fd, EVIOCGVERSION, &version)) {
				perror("evtest: can't get version");
				return 0;
			}

			printf("Input driver version is %d.%d.%d\n",
				version >> 16, (version >> 8) & 0xff, version & 0xff);

			ioctl(fd, EVIOCGID, id);
			printf("Input device ID: bus 0x%x vendor 0x%x product 0x%x version 0x%x\n",
				id[ID_BUS], id[ID_VENDOR], id[ID_PRODUCT], id[ID_VERSION]);

			ioctl(fd, EVIOCGNAME(sizeof(dev_name)), dev_name);
			printf("Input device name: \"%s\"\n", dev_name);

			return fd;
		}
		close(fd); // we don't need this device
	}
	return 0;
}

void SimpleJoy::PND_ReadEvents( int fd, int device )
{
	if( fd != 0 )
	{
		rd = read(fd, ev, sizeof(struct input_event) * 64);
        haveTSx = false;
        haveTSy = false;
        rawTS.x = 0;
        rawTS.y = 0;
		if (rd >= (int) sizeof(struct input_event))
		{
			for (i = 0; i < rd / (int) sizeof(struct input_event); i++)
			{
			    currentEvent = i;
				PND_CheckEvent( &ev[i], device );
			}
		}
	}
}

void SimpleJoy::PND_CheckEvent( struct input_event *event, int dev )
{
    switch( event->type )
    {
        case EV_KEY:
            // Mappings
            for(int b = players[player].mapper.size()-1; b>=0; --b)
            {
                KEY_MAP_DEVICE device = players[player].mapper.keys.at(b)->getDevice();
                if(device == DEV_KEYBOARD)
                {
                    if(event->code == ((KeyMapKey*)players[player].mapper.keys[b])->getKey())
                    {
                        #ifdef _DEBUG
                        cout << "Key:" << event->code << " Pressed!" << endl;
                        #endif
                        if(event->value == 1)
                            mappedDown(players[player].mapper.keys[b]->getTarget());
                        else if(event->value == 0)
                            mappedUp(players[player].mapper.keys[b]->getTarget());
                    }
                }
            }
            //  Keyboard passthrough
            if(event->value == 1)
            {
                KeyMapKey t(event->code);
                tKey k;
                k.key = t;
                k.status = sjPRESSED;
                players[player].storeKeys.push_back(k);
            }
            else if(event->value == 0)
            {
                KeyMapKey t(event->code);
                tKey k;
                k.key = t;
                k.status = sjRELEASED;
                players[player].storeKeys.push_back(k);
            }
        break;
        case EV_ABS:
            // Mappings
            if(dev == DEV_TOUCH)
            {
                if(event->code == ABS_X)
                {
                    rawTS.x = event->value;
                    haveTSx = true;
                }
                else if(event->code == ABS_Y)
                {
                    rawTS.y = event->value;
                    haveTSy = true;
                }
                if(haveTSx && haveTSy)
                {
                    #ifdef _DEBUG
                    cout << "TSRAW_X:" << rawTS.x << endl;
                    cout << "TSRAW_Y:" << rawTS.y << endl;
                    #endif
                    for(int b = players[player].mapper.size()-1; b>=0; --b)
                    {
                        KEY_MAP_DEVICE device = players[player].mapper.keys.at(b)->getDevice();
                        if(device == DEV_MOUSE_AXIS)
                        {
                            if(dev == DEV_TOUCH)
                            {
                                //cout << "Axis: " << event->code << " Moved!" << endl;
                                mappedMouseAxes(((KeyMapMouseAxis*)players[player].mapper.keys[b])->getTarget(),((KeyMapMouseAxis*)players[player].mapper.keys[b])->getAxis());
                            }
                        }
                    }
                }
            }
            for(int b = players[player].mapper.size()-1; b>=0; --b)
            {
                KEY_MAP_DEVICE device = players[player].mapper.keys.at(b)->getDevice();
                if(device == DEV_JOYSTICK_AXIS)
                {
                    switch( dev )
                    {
                        case DEV_NUBL:
                            if( event->code == ABS_X && ((KeyMapJoyAxis*)players[player].mapper.keys[b])->getAxis() == 0)
                                mappedJoyAxes(((KeyMapJoyAxis*)players[player].mapper.keys[b])->getTarget());
                            if( event->code == ABS_Y && ((KeyMapJoyAxis*)players[player].mapper.keys[b])->getAxis() == 1)
                                mappedJoyAxes(((KeyMapJoyAxis*)players[player].mapper.keys[b])->getTarget());
                        break;
                        case DEV_NUBR:
                            if( event->code == ABS_X && ((KeyMapJoyAxis*)players[player].mapper.keys[b])->getAxis() == 2)
                                mappedJoyAxes(((KeyMapJoyAxis*)players[player].mapper.keys[b])->getTarget());
                            if( event->code == ABS_Y && ((KeyMapJoyAxis*)players[player].mapper.keys[b])->getAxis() == 3)
                                mappedJoyAxes(((KeyMapJoyAxis*)players[player].mapper.keys[b])->getTarget());
                        break;
                    }
                }
                else if(device == DEV_MOUSE_BUTTON && dev == DEV_TOUCH)
                {
                    if(event->code == ABS_PRESSURE)
                    {
                        //cout << "Pressure: " << event->value << " Pressed!" << endl;
                        if(event->value)
                            mappedDown(players[player].mapper.keys[b]->getTarget());
                        else
                            mappedUp(players[player].mapper.keys[b]->getTarget());
                    }
                }
            }
        break;
        default:
            break;
    }

}
#endif

void SimpleJoy::setNumPlayers(CRuint p)
{
    //  if we want more players than we have
    Player* tp = NULL;
    if(p > numPlayers)
    {
        //  save pointer to existing Players
        tp = players;
        //  setup new array
        players = new Player[p];

        //  copy existing players accross
        for(int i = 0; i < numPlayers; ++i)
        {
            players[i].deadZone = tp[i].deadZone;
            players[i].scaler = tp[i].scaler;
            players[i].mapLoaded = tp[i].mapLoaded;
        }
        delete [] tp;

        //  setup newest addition
        players[p-1].deadZone.x = 0;
        players[p-1].deadZone.y = 0;
        players[p-1].scaler = 1.0f;
        players[p-1].mapLoaded = false;
        players[p-1].wheel = 0;
	#ifdef PENJIN_PANDORA_TOUCHSCREEN_FIX
        players[p-1].leftClickNeedsRelease = false;
	#endif // PENJIN_PANDORA_TOUCHSCREEN_FIX
        numPlayers = p;
        /*players.push_back(&new Player());
        players.at(p-1).deadZone.x = 0;
        players.at(p-1).deadZone.y = 0;
        players.at(p-1).scaler = 1.0f;
        players.at(p-1).mapLoaded = false;*/
    }
}
