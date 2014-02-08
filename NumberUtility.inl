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
//----------------------
// template functions implementation
//----------------------
///----------------------
/// Sign
///----------------------

template <class T>
int NumberUtility::sign(const T& value)
{
    return (value > 0) - (0 > value);
}

template <class T>
T NumberUtility::signMax(const T& a, const T& b)
{
    return max(abs(a),abs(b)) * sign(a);
}

template <class T>
T NumberUtility::signMin(const T& a, const T& b)
{
    return min(abs(a),abs(b)) * sign(a);
}

template <class T>
T NumberUtility::closestToZero(const T& a, const T& b)
{
    if (abs(a) < abs(b))
        return a;
    else
        return b;
}

template <class T>
T NumberUtility::furthestFromZero(const T& a, const T& b)
{
    if (abs(a) > abs(b))
        return a;
    else
        return b;
}
