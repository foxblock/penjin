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
*/#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "LayerObject.h"
using std::string;

namespace Penjin
{
    class Window : public LayerObject
    {
        public:
            /** Default constructor */
            Window();
            /** Default destructor */
            virtual ~Window();

            virtual void render();
            virtual void onClick();     /**< When window is clicked, this function is called */

            void focus();               /**< Brings window to foregrand, i.e. sets to layer 0 */
            void refresh();             /**< Refreshes the window display */

            void setFullscreen(const bool& fs);
            void setTitle(const string& t);

            bool getFullscreen();
            string getTitle();

        protected:
            bool fullscreen;    //  Does it takeup fullscreen
            string* title;
    };
}
#endif // WINDOW_H
