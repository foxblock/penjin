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
#include "AchievementBoolean.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementBoolean::AchievementBoolean() : Achievement()
{
    type = atBOOLEAN;
    showProgress = false;
}

///------------------------------
/// Public
///------------------------------


///------------------------------
/// Private
///------------------------------

void AchievementBoolean::changeCount(const vector<Event*>& changeEvents)
{
    // reset counter
    if (counter.getLimit() > 0)
    {
        if (not counter.isStarted())
            counter.start();
        else if (counter.hasFinished())
        {
            counter.start();
            count = 0;
        }
    }

    if (changeEvents.size() == events.size())
        count++;
}
