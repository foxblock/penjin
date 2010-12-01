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
#ifndef IMAGEMENUITEM_H_INCLUDED
#define IMAGEMENUITEM_H_INCLUDED

#include "MenuItem.h"
#include "Image.h"

class ImageMenuItem : public MenuItem
{
    public:
        ImageMenuItem(){init();}
        ImageMenuItem(CRstring fileName){init(); menuImage.loadImage(fileName);}
        virtual ~ImageMenuItem();

        virtual Vector2di getDimensions();
        virtual void render();
        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
        #else
            #ifdef PENJIN_3D
                virtual void update();
            #endif
        #endif


        PENJIN_ERRORS loadImage(CRstring fileName){return menuImage.loadImage(fileName);}
        PENJIN_ERRORS loadSelection(CRstring fileName);
        #ifdef PENJIN_SDL
            void setUseHardware(CRbool shouldUse){menuImage.setUseHardware(shouldUse);}
        #endif


    protected:
         virtual void init();

    private:
        Image menuImage;
        Image* selected;        //  pointer to a shared selection image
};
#endif // IMAGEMENUITEM_H_INCLUDED
