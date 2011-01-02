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
#include "Variable.h"

void Variable::setValue(Variable value)
{
    if(value.hasInt())
        setInt(value.getInt());
	if(value.hasFloat())
        setFloat(value.getFloat());
	if(value.hasString())
        setString(value.getString());
	if(value.hasDouble())
        setDouble(value.getDouble());
}

bool Variable::operator ==(Variable value)
{
    return equals(value);
}

bool Variable::operator !=(Variable value)
{
	return !equals(value);
}

bool Variable::equals(Variable value) {
	if(value.hasFloat() && hasFloat())
	{
	    if(floatValue == value.getFloat())
            return true;
    }
	if(value.hasInt() && hasInt())
	{
	    if(intValue == value.getInt())
            return true;
    }
    if(value.hasDouble() && hasDouble())
	{
	    if(doubleValue == value.getDouble())
            return true;
    }
    if(value.hasString() && hasString())
    {
 	    if(stringValue == value.getString())
            return true;
    }
	return false;
}

