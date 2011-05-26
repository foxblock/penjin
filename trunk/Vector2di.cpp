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
#include "Vector2di.h"

#ifdef PENJIN_SDL
#include <SDL/SDL.h>
#endif

void Vector2di::normalise()
{
    float temp = 1/length();
	if (temp <= std::numeric_limits<float>::max())
	{
		x *= temp;
		y *= temp;
	}
	else
	{
		x = 0;
		y = 1;
	}
}

#ifdef PENJIN_SDL
bool Vector2di::inRect(const SDL_Rect& rect) const
{
    if (x < rect.x || y < rect.y || x >= rect.x + rect.w || y >= rect.y + rect.h)
        return false;
    return true;
}
#endif

bool Vector2di::inRect(CRint x, CRint y, CRuint w, CRuint h) const
{
    if (this->x < x || this->y < y || this->x >= x + w || this->y >= y + h)
        return false;
    return true;
}
