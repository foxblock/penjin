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
#ifndef ACHIEVEMENTTIME_H
#define ACHIEVEMENTTIME_H

///------------------------------
/// Time Achievement class
/// by foxblock 11/12/09
///
/// Timed Achievement, first event triggers the timer, all events have to occur
/// in the given time for the count to be increased
///------------------------------

#include "Achievement.h"
using namespace std;

class AchievementTime : public Achievement
{
    public:
        AchievementTime();

        void addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count=1, CRint comparison=0, CRint action=0);

    protected:
        // increase or decrease achievement count
        void changeCount(const vector<Event*>& changeEvents);

        vector<bool> doneEvents;
};

#endif // ACHIEVEMENTTIME_H


