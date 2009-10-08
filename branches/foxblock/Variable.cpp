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

