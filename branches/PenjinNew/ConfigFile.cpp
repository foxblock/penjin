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
*/

#include "ConfigFile.h"

#include <string>
using Penjin::ConfigFile;
using std::string;

ConfigFile::ConfigFile()
{
    //ctor
    ini = NULL;
    ini = new CSimpleIniA;
}

ConfigFile::~ConfigFile()
{
    //dtor
    delete ini;
}

Penjin::ERRORS ConfigFile::load(const string& fileName)
{
    return getError(ini->LoadFile(fileName.c_str()));
}

Penjin::ERRORS ConfigFile::save(const string& fileName)
{
    return getError(ini->SaveFile(fileName.c_str()));
}

string ConfigFile::getValue(const string& section, const string& key)
{
    return (string)ini->GetValue(section.c_str(),key.c_str(),NULL);
}

Penjin::ERRORS ConfigFile::getError(const int& error)
{
    /*    SI_FAIL     = -1,   //!< Generic failure
    SI_NOMEM    = -2,   //!< Out of memory error
    SI_FILE     = -3    //!< File error (see errno for detail error)*/
    if(error<0)
    {
        if(error==-1)
            return PENJIN_ERROR;
        else if(error==-2)
            return PENJIN_ERROR;
        else
            return PENJIN_FILE_NOT_FOUND;
    }
    return PENJIN_OK;
}
