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
#include <string>
#include "Application.h"
using Penjin::Application;
using std::string;

Application::Application()
{
    //ctor
    //  We load the settings file for the app
    Penjin::ConfigFile conf;
    Errors error = conf.load("config/settings.ini");

    //  If settings.ini not found create a default
    if(error == PENJIN_FILE_NOT_FOUND)
        createDefaultSettings();

    // Find out the current language
    Penjin::LocaleMan::getInstance()->setLanguageFolder(conf.getValue("Locale","LanguageFolder"));
    Penjin::LocaleMan::getInstance()->setLanguage(conf.getValue("Locale","Language"));
    error = Penjin::LocaleMan::getInstance()->load();
    if(error == PENJIN_FILE_NOT_FOUND)
    {
        // TODO handle error properly
        //cout << "ERROR" << endl;
    }
    //  Set localised title
    this->setTitle( (string)Penjin::LocaleMan::getInstance()->getValue("Application","Title") );

    // TODO: Setup video properties from settings file.
    //setWidth();
    //setHeight();
    //setFullscreen();
}

Application::~Application()
{
    //dtor
}
