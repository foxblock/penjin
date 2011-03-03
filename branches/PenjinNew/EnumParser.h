/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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
*/#ifndef ENUMPARSER_H
#define ENUMPARSER_H

#include "Object.h"
#include <string>
#include <map>
using std::string;
using std::map;

namespace Penjin
{
    template <typename T>
    class EnumParser : public Object
    {
        public:
            /** Default constructor */
            EnumParser();
            /** Default destructor */
            virtual ~EnumParser();

            T stringToEnum(const string & value)
            {
                map <string, T>::const_iterator iValue = enumMap.find(value);
                if (iValue  == enumMap.end())
                        throw runtime_error("EnumParser Error");
                return iValue->second;
            }

            map <string, T> enumMap;
    };
}
#endif // ENUMPARSER_H
