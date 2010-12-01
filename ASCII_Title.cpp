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
#include "ASCII_Title.h"

ASCII_Title::ASCII_Title()
{
    //ctor
    title = Penjin::getApplicationName();
    version = (string)AutoVersion::FULLVERSION_STRING + (string)AutoVersion::STATUS_SHORT;
    description = "Default Penjin Application.";
}

ASCII_Title::~ASCII_Title()
{
    //dtor
}

void ASCII_Title::render()
{
	for (int i = 0; i < (int)title.length()+2; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "#" << title.c_str() << "#" << endl;
	string versiontext = "Version: ";
	cout << "#";
	for (int i = 0; i < ( ( (int)title.length() - ( (int)versiontext.length() + (int)version.length() ) ) / 2 ); i++)
	{
		cout << '~';
	}
	cout << versiontext.c_str() << version.c_str();
	for (int i = 0; i < ( ( (int)title.length() - ( (int)versiontext.length() + (int)version.length() ) ) / 2); i++)
	{
		cout << "~";
	}
	cout << "#" << endl;
	cout << "#";
	for (int i = 0; i < (int)title.length(); i++)
	{
		cout << "-";
	}
	cout << "#" << endl;
	cout << description.c_str() << endl << endl;
}
