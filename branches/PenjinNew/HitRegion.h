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
//********************************************************************************//
// HitRegion class by Dragons_Slayer                                              //
// ---------------------------------											  //
//																				  //
//	Simple hit detection using rectangle shapes					            	  //
//	For more advanced collision see the CollisionRegion and CollisionMap class    //
//																				  //
//********************************************************************************//

/// -------------------------------------------------------------------------------------
/// DEPRECATED  - please use CollisionRegion instead (it has all the features + some more)
/// -------------------------------------------------------------------------------------

//-----------------------------------------------------
// Defines
//-----------------------------------------------------
#ifndef HitRegion_H
#define HitRegion_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Sprite.h"
#include "Rectangle.h"
#include "CollisionMap.h"

// RECT Struct
struct HRECT
{
    int x, y, w, h;
};

//-----------------------------------------------------
// HitRegion Class
//-----------------------------------------------------
class HitRegion
{
public:
    HitRegion();   //Constructor
    virtual ~HitRegion();  //Destructor

	//-------------------------------------------------
	// Public Methods
	//-------------------------------------------------
    void init(CRint x, CRint y, CRint width, CRint height);
    #ifdef PENJIN_SDL
        void render(SDL_Surface* screen);
    #endif
    void render();

    void move(CRint x, CRint y);
    void moveTo(CRint x, CRint y);

    bool hitTest(const HitRegion* const region) const;
    bool hitTest(CollisionMap* const map, CRint x, CRint y)const;
    Colour colourTest(CollisionMap* const map) const;
    Colour colourTest(CollisionMap* const map, CRint x, CRint y)const;

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

private:
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
    HRECT m_Region;
    Rectangle box;
};

#endif // HitRegion_H
