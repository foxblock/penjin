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

/**
*   \author Kevin Winfield-Pantoja
*   A DisplayEntity is a generic container object that signifies anything that be rendered to the screen.
*/
#ifndef DISPLAYENTITY_H
#define DISPLAYENTITY_H

#include "PenjinTypes.h"
#include <vector>
using std::vector;

// Primitives
class Pixel;
class Line;
class Rectangle;

// Images and Animations
//class Image;
//class Background;
//class Animation;

// Sprites
class Sprite;
class AnimatedSprite;

// Particles
class Emitter;


class DisplayEntity
{
    public:
        /** Default constructor */
        DisplayEntity();
        /** Default destructor */
        virtual ~DisplayEntity();

        void render();
        void update();

        void setPosition(CRint x, CRint y);

    protected:
        Pixel* pix;
        Line* line;
        Rectangle* rect;
        //Image* image;
        //Background* bg;
        //Animation* anim;
        Sprite* sprite;
        AnimatedSprite* animSpr;
        Emitter* emit;
        int references; //  The number of times the DisplayEntity is referenced externally.

    private:
        /** Copy constructor
         *  \param other Object to copy from
         */
        DisplayEntity(const DisplayEntity& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        DisplayEntity& operator=(const DisplayEntity& other);
};

#endif // DISPLAYENTITY_H
