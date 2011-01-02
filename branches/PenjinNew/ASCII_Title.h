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
#ifndef ASCII_TITLE_H
#define ASCII_TITLE_H

/* ABOUT:
console application title Class written by Kevin Winfield-Pantoja
11.10.2005
*/
#include <string>
using std::string;
#include "PenjinTypes.h"
#include "Penjin.h"
#include "version.h"

class ASCII_Title
{
    public:
        ASCII_Title();
        ~ASCII_Title();
        void setTitle(CRstring appTitle);				//	Stores a title for the application
        void setVersion(CRstring appVersion);			//	stores a version number for the app
        void setDescription(CRstring appDescription){description = appDescription;}	//	stores a short description for the app
        void render();							        //	displays the title information

    private:
        string title;
        string version;
        string description;
};

#endif // ASCII_TITLE_H
