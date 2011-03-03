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
*/#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "Errors.h"
#include "Singleton.h"
#include "LocalisedStringManager.h"
using Penjin::LocalisedStringManager;
using Penjin::Singleton;


class ApplicationState;


/**
*   \file Application is a base class to create certain application types.
*/
namespace Penjin
{
    typedef Singleton<LocalisedStringManager> LocaleMan;

    class Application : public Window
    {
        public:
            /** Default constructor */
            Application();
            /** Default destructor */
            virtual ~Application();

            /** \brief Processes commandline arguements
             *
             * \param argc an int of the number of commands
             * \param argv the actual char** string data
             * \return Penjin::Errors the error code.
             *
             */
            virtual Penjin::Errors argHandler(int argc, char** argv);

            //void setNextState(StateID next);

            virtual void quit();

        protected:
            void createDefaultSettings();
            void stateManagement();

            // StateID next;
            ApplicationState* state;
    };
}
#endif // APPLICATION_H
