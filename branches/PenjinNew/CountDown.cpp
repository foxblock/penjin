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
#include "CountDown.h"

CountDown::CountDown() : Timer()
{
    limit = 1000;
    callback = NULL;
    obj = NULL;
    rewind = STOP;
}

void CountDown::init(const int& newLimit, const TimerScalers& newMode, void* object, void (*newCallback)(void*))
{
    limit = newLimit;
    setMode(newMode);
    callback = newCallback;
    obj = object;
    if (callback)
        rewind = STOP_AND_REWIND;
    is_Started = false;
    is_Paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void CountDown::update()
{
    if (limit - getScaledTicks() <= 0 && is_Started)
    {
        if (callback)
            (*callback)(obj);
        if (rewind == STOP_AND_REWIND)
        {
            stop();
        }
        else if (rewind == REWIND)
        {
            start();
        }
        else if (rewind == STOP)
        {
            pause();
        }
    }
}

/**--------------------------------

How to implement:
- Create a static member function of a class with the following implementation
void CLASS::FUNCTIONNAME(void* object)
{
    CLASS* self = (CLASS*) object;
    // do stuff here use self-> to access class datamembers and functions
}

- This usually acts as a wrapper function, you can do stuff in there or make it private and
    redirect the function call to another (public) function

- initialize the countdown like this:
    ctr.init(2000,MILLI_SECONDS,(void*) this, &CLASS::FUNCTIONNAME); // 2000 milliseconds countdown

- The counter has to be updated in order for the callback to take place, so the update() function has
    to be called on a regular basis (in a state update function for example)

--------------------------------**/
