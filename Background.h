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
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Image.h"

class Background
{
public:
	Background();
	~Background();

	PENJIN_ERRORS loadBackground(CRstring file);
	template <class T>
	void setPosition(const T& pos){position.x = pos.x;position.y = pos.y;}
    #ifdef PENJIN_SDL
        void render(SDL_Surface *screen);	//	The destination surface the animation should be rendered to
        void render(){render(screen);}
    #else
        void render();
    #endif
        PENJIN_ERRORS setTransparentColour(const Colour& c){return img.setTransparentColour(c);}
        PENJIN_ERRORS setTransparentColour(const PENJIN_COLOURS& c){return setTransparentColour(Colour(c));}
        void disableTransparentColour(){img.disableTransparentColour();}
        void setBG(CRuint bg);	                //	Assigns a background ID
        uint getBG()const;			            //	Returns an assigned background ID
        void toGreyScale();                     //  Permanently convert Background to B&W
        void clear(){img.clear();bg=0;}              //  Clear out all images
        size_t size()const{return img.size();}  //  The number of stored backgrounds.
    private:
        #ifdef PENJIN_SDL
            SDL_Surface* screen;
        #endif
        uint bg;				//	The stored bg ID, used with the image draw function to draw a specific bg.
        Image img;
        Vector2di position;
};

#endif	//	BACKGROUND_H

