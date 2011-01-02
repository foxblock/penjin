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
#include "Event.h"

bool Event::check(const Event* const ev) const
{
    if (name == ev->name && SpecialProperty::compare(count,ev->count,comparison) && checkSpecial(ev->special))
        return true;

    return false;
}

bool Event::checkSpecial(const vector<SpecialProperty>* const sp) const
{
    if (special)
    {
        if (!sp)
            return false;
    }
    else
        return true;
    if (special->size() == 0)
        return true;
    if (special->size() > sp->size())
        return false;

    vector<SpecialProperty>::const_iterator I;
    for (I = special->begin(); I < special->end(); I++)
    {
        // checking the property
        bool found = false;
        vector<SpecialProperty>::const_iterator K;
        for (K = sp->begin(); K < sp->end(); K++)
        {
            if (I->property == K->property)
            {
                // if found it compares the values
                if (not SpecialProperty::compare(I->value,K->value,I->comparison))
                {
                    return false;
                }
                else
                {
                    found = true;
                    break;
                }
            }
        }
        // if not found - return missmatch
        if (found == false)
            return false;
    }

    return true;
}

bool Event::isEvent(const vector<Event*>& events) const
{
    bool found = false;
    vector<Event*>::const_iterator I;

    for (I = events.begin(); I < events.end() && not found; ++I)
    {
        if ((*I)->name == name && (*I)->checkSpecial(special))
            found = true;
    }

    return found;
}
