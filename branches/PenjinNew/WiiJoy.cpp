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
#include "WiiJoy.h"

WiiJoy::WiiJoy()
{
    //ctor
    Up = Down = Left = Right = A = B = One = Two = Plus = Minus = Home = 0;
}

WiiJoy::~WiiJoy()
{
    //dtor
}

void WiiJoy::update()
{
    resetKeys();
    // update wii pads
    #ifdef PLATFORM_WII
        WPAD_ScanPads();
        //  Check which are pressed
        checkPressed();
        //  Check which are held
        checkHeld();
    #endif
}

void WiiJoy::resetKeys()
{
    Up = Down = Left = Right = A = B = One = Two = Plus = Minus = Home = 0;
}

#ifdef PLATFORM_WII
    void WiiJoy::checkPressed()
    {
        u32 pressed = WPAD_ButtonsDown(0);
		const int PRESSED = 1;
		if ( pressed & WPAD_BUTTON_1){One = PRESSED;}
		if ( pressed & WPAD_BUTTON_2){Two = PRESSED;}
		if ( pressed & WPAD_BUTTON_A){A = PRESSED;}
		if ( pressed & WPAD_BUTTON_B){B = PRESSED;}
		if ( pressed & WPAD_BUTTON_PLUS){Plus = PRESSED;}
		if ( pressed & WPAD_BUTTON_MINUS){Minus = PRESSED;}
		if ( pressed & WPAD_BUTTON_UP){Up = PRESSED;}
		if ( pressed & WPAD_BUTTON_DOWN){Down = PRESSED;}
		if ( pressed & WPAD_BUTTON_LEFT){Left = PRESSED;}
		if ( pressed & WPAD_BUTTON_RIGHT){Right = PRESSED;}
		if ( pressed & WPAD_BUTTON_HOME){Home = PRESSED;}
    }

    void WiiJoy::checkHeld()
    {
        u32 pressed = WPAD_ButtonsHeld(0);
		const int HELD = 2;
		if ( pressed & WPAD_BUTTON_1){One = HELD;}
		if ( pressed & WPAD_BUTTON_2){Two = HELD;}
		if ( pressed & WPAD_BUTTON_A){A = HELD;}
		if ( pressed & WPAD_BUTTON_B){B = HELD;}
		if ( pressed & WPAD_BUTTON_PLUS){Plus = HELD;}
		if ( pressed & WPAD_BUTTON_MINUS){Minus = HELD;}
		if ( pressed & WPAD_BUTTON_UP){Up = HELD;}
		if ( pressed & WPAD_BUTTON_DOWN){Down = HELD;}
		if ( pressed & WPAD_BUTTON_LEFT){Left = HELD;}
		if ( pressed & WPAD_BUTTON_RIGHT){Right = HELD;}
		if ( pressed & WPAD_BUTTON_HOME){Home = HELD;}
    }
#endif
