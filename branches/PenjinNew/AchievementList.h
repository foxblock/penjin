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
#ifndef ACHIEVEMENTRESETTWO_H
#define ACHIEVEMENTRESETTWO_H

///------------------------------
/// List Achievement class
/// by foxblock 15/12/09
///
/// Mix of Boolean, Reset and Time Achievements
/// Several events, must be completed in no particular order and without time constraint
/// Reset-events, reset count and completed events
///------------------------------

#include "Achievement.h"
using namespace std;

class AchievementList : public Achievement
{
    public:
        AchievementList();

        void addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count, CRint comparison, CRint action);

        virtual int getTimeLimit() const {return -1;};
        virtual void setTimeLimit(CRint value);

        virtual void load(CRstring);
        virtual string save() const;

        #ifdef PENJIN_SDL
        virtual void renderProgress(SDL_Surface* screen);
        #else
        virtual void renderProgress();
        #endif

    protected:
        // increase or decrease achievement count
        virtual void changeCount(const vector<Event*>& changeEvents);

        void resetDone();

        vector<bool> doneEvents;
        int doneCount;
        int eCount;
};

#endif // ACHIEVEMENTRESETTWO_H


