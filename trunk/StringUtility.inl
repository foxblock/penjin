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
template <class T>
string StringUtility::vecToString( const T &value, CRstring separator )
{
	// using doubleToString for maximum compatibility
	return (doubleToString(value.x) + separator + doubleToString(value.y));
}

template <class T>
T StringUtility::stringToVec( CRstring value, CRstring separator )
{
	vector<string> tokens;
	tokenize(value,tokens,separator);
	if (tokens.size() != 2)
		return T(0,0);
	return T(stringToFloat(tokens.front()),stringToFloat(tokens.back()));
}
