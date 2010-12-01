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
#ifndef EVENT_H
#define EVENT_H

///------------------------------
/// Achievement Utility namespace
/// by foxblock 10/12/09
///
/// Contains functions, structs and enums for use with the Achievement system
///------------------------------

#include <vector>
#include "PenjinTypes.h"
#include "StringUtility.h"
#include "SpecialProperty.h"

using namespace std;

// logged events don't need this, the action parameter of the achievement will be used
enum Action
{
    acRESET=-2, // resets the count to 0
    acDECREASE, // decreases the count by 1
    acDO_NOTHING, // no effect on achievement count
    acINCREASE, // increases count by 1
    acINCREASE_COUNT // increases count by event count value
};

class Event
{
    public:
        Event(CRstring n, CRint i, CRint c, CRint a) {name = n; special = NULL; count = i; comparison = c; action = a;};
        Event(CRstring n, vector<SpecialProperty>* s, CRint i, CRint c, CRint a) {name = n; special = s; count = i; comparison = c; action = a;};
        ~Event() {delete special;};

        void addSpecial(const SpecialProperty& sp) {special->push_back(sp);};
        void setSpecial(vector<SpecialProperty>* sp) {special = sp;};
        bool check(const Event* const ev) const;
        bool checkSpecial(const vector<SpecialProperty>* const sp) const;

        // checks whether an event is already present in an vector of events
        bool isEvent(const vector<Event*>& events) const;

        string name;
        vector<SpecialProperty>* special;
        int count;
        int comparison;
        int action;
};

#endif // EVENT_H
