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
#ifndef SPECIALPROPERTY_H
#define SPECIALPROPERTY_H

#include "PenjinTypes.h"
#include "StringUtility.h"

enum CompareOp // To-do: add SMALLER-EQUAL and GREATER-EQUAL
{
    coSMALLER=-1,
    coEQUAL,
    coGREATER,
    coDONT_CARE
};

// use this for storing many more detailed layers of information about logged events
// e.g. type of weapon, id or name of game won, name of enemy hit, etc.
// logged events don't need the comparison op to be set, the one of the achievement will be used
class SpecialProperty
{
public:
    SpecialProperty(CRstring prop, CRint val, CRint comp)
    {
        property = prop;
        value = val;
        comparison = comp;
    };
    SpecialProperty(CRint prop, CRint val, CRint comp)
    {
        property = StringUtility::intToString(prop);
        value = val;
        comparison = comp;
    };
    ~SpecialProperty() {};

    // compares two special properties or two vectors of special properties
    // returns true if all properties match - more specialized proeprties match simpler ones
    // (= if sp2 has a property sp1 has not, it still matches, but not the other way around)
    bool checkSpecial(const SpecialProperty& sp) const
    {
        if (property != sp.property && not compare(value,sp.value,comparison))
            return false;

        return true;
    }

    // compares a value with a reference value using a comparison operator (CompareOp)
    static bool compare(CRint reference, CRint value, CRint op)
    {
        if (op == coDONT_CARE)
            return true;
        else if (op == coSMALLER)
            return value < reference;
        else if (op == coEQUAL)
            return value == reference;
        else if (op == coGREATER)
            return value > reference;
        else
            return false;
    }

    string property;
    int value;
    int comparison; // 1 - greater, -1 - smaller, 0 - equal, 2 - don't care
};

#endif // SPECIALPROPERTY_H
