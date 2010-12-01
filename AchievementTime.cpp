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
#include "AchievementTime.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementTime::AchievementTime() : Achievement()
{
    type = atTIME;
    showProgress = false;
}

///------------------------------
/// Public
///------------------------------

// the actual addEvent function, which all wrapper functions use
void AchievementTime::addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count, CRint comparison, CRint action)
{
    // check whether event was already added to prevent duplicates
    Event* ev = new Event(name,special,count,comparison,action);
	if (not ev->isEvent(events))
	{
		events.push_back(ev);
		doneEvents.push_back(false);
	}
    else
    {
        delete ev;
    #ifdef _DEBUG
        cout << "[Achievements] Error: Duplicate event " << name << " on achievement " << this->name << " - ignored!" << endl;
    #endif
    }
}

///------------------------------
/// Private
///------------------------------

void AchievementTime::changeCount(const vector<Event*>& changeEvents)
{
    if (not counter.isStarted())
        counter.start();

    vector<Event*>::const_iterator I;
    for (I = changeEvents.begin(); I < changeEvents.end(); ++I)
    {
        vector<Event*>::const_iterator K;
        vector<bool>::iterator L = doneEvents.begin();
        for (K = events.begin(); K < events.end(); ++K)
        {
            if ((*K)->name == (*I)->name)
                *L = true;
            ++L;
        }
    }

    bool done = true;
    vector<bool>::iterator K;
    for (K = doneEvents.begin(); K < doneEvents.end(); ++K)
        if (*K == false)
            done = false;
    if (done)
        count++;

    if (counter.hasFinished() || done)
    {
        counter.stop();
        vector<bool>::iterator L;
        for (L = doneEvents.begin(); L < doneEvents.end(); ++L)
            *K = false;
    }
}

