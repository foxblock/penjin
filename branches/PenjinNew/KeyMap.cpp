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
#include "KeyMap.h"

KeyMap::KeyMap()
{
    //ctor
    device = DEV_UNKNOWN;
    deviceID = 0;
    target = SJ_UNMAPPED;
}

KeyMap::~KeyMap()
{
    //dtor
}

void KeyMap::setSJMap(string t)
{
    if(t == "UP")
        target=SJ_UP;
    else if(t == "DOWN")
        target=SJ_DOWN;
    else if(t == "LEFT")
        target=SJ_LEFT;
    else if(t == "RIGHT")
        target=SJ_RIGHT;
    else if(t == "UPLEFT")
        target=SJ_UPLEFT;
    else if(t == "UPRIGHT")
        target=SJ_UPRIGHT;
    else if(t == "DOWNLEFT")
        target=SJ_DOWNLEFT;
    else if(t == "DOWNRIGHT")
        target=SJ_DOWNRIGHT;
    else if(t == "A")
        target=SJ_A;
    else if(t == "B")
        target=SJ_B;
    else if(t == "X")
        target=SJ_X;
    else if(t == "Y")
        target=SJ_Y;
    else if(t == "L")
        target=SJ_L;
    else if(t == "R")
        target=SJ_R;
    else if(t == "START")
        target=SJ_START;
    else if(t == "SELECT")
        target=SJ_SELECT;
    else if(t == "CLICK")
        target=SJ_CLICK;
    else if(t == "LID")
        target=SJ_LID;
    else if(t == "LEFTSTICK_X")
        target=SJ_LEFTSTICK_X;
    else if(t == "LEFTSTICK_Y")
        target=SJ_LEFTSTICK_Y;
    else if(t == "RIGHTSTICK_X")
        target=SJ_RIGHTSTICK_X;
    else if(t == "RIGHTSTICK_Y")
        target=SJ_RIGHTSTICK_Y;
    else if(t == "MOUSE_X")
        target = SJ_MOUSE_X;
    else if(t == "MOUSE_Y")
        target = SJ_MOUSE_Y;
    else if(t == "MOUSE_LEFT")
        target=SJ_MOUSE_LEFT;
    else if(t == "MOUSE_CENTRE")
        target=SJ_MOUSE_CENTRE;
    else if(t == "MOUSE_RIGHT")
        target=SJ_MOUSE_RIGHT;
    else if(t == "VOLUP")
        target=SJ_VOLUP;
    else if(t == "VOLDOWN")
        target=SJ_VOLDOWN;
    else
        target=SJ_UNMAPPED;
}
