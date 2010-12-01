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
#ifndef COUNTDOWN_H_INCLUDED
#define COUNTDOWN_H_INCLUDED

#include "Timer.h"

enum RewindModes
{
    STOP_AND_REWIND,
    REWIND,
    STOP,
    DONT_REWIND
};

class CountDown : public Timer
{
    public:
        CountDown();
        void init(const int& newLimit, const TimerScalers& newMode=MILLI_SECONDS, void* object=NULL, void (*newCallback)(void*)=NULL);

        int getLimit() const {return limit;}
        int getTimeLeft() const {return limit - getScaledTicks();}
        RewindModes getRewind() const {return rewind;}
        bool hasFinished() const {return getTimeLeft() <= 0;}
        void setCallback(void* object, void (*newCallback)(void*)){obj = object; callback = newCallback;}
        void setLimit(const int& newLimit){limit = newLimit;}
        void setRewind(const RewindModes& rew){rewind = rew;}

        void start(){Timer::start();}
        void start(int newLimit){setLimit(newLimit); start();}
        void update();
    private:
        void (*callback)(void*);
        void* obj;
        int limit;
        RewindModes rewind;
};

#endif // COUNTDOWN_H_INCLUDED
