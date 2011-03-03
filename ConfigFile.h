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
*/#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include "FileObject.h"
#include <vector>
using std::vector;
class CSimpleIniA;


namespace Penjin
{
    class ConfigFile : public FileObject
    {
        public:
            /** Default constructor */
            ConfigFile();
            /** Default destructor */
            virtual ~ConfigFile();

            virtual Penjin::Errors load(const string& fileName);
            virtual Penjin::Errors save(const string& fileName);
            virtual Penjin::Errors load();
            virtual Penjin::Errors save();


            void setValue(const string& section, const string& key, const string& value);
            string getValue(const string& section, const string& key);
            vector<string> getValues(const string& section, const string& key);
            void removeValue(const string& section, const string& key);
            void removeSection(const string& section);

        protected:
            CSimpleIniA* ini;
    };
}
#endif // CONFIGFILE_H
