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
#include "Pixel.h"

Pixel::Pixel()
{
    position.x = position.y = -1;
    init();
    setPixel();
}

void Pixel::init()
{
#ifdef PENJIN_SDL
    screen = GFX::getVideoSurface();
    pixel = NULL;
    pixel = SDL_CreateRGBSurface(SDL_SWSURFACE, 1, 1, screen->format->BitsPerPixel, NULL, NULL, NULL, NULL);
#endif
}

void Pixel::setColour(const Colour& c)
{
    colour.setColour(c);
    setPixel();
}

void Pixel::setColour(CRuchar r, CRuchar g, CRuchar b, CRuchar a)
{
    colour.setColour(r,g,b,a);
    #ifdef PENJIN_SDL
        SDL_SetAlpha(pixel, SDL_SRCALPHA|SDL_RLEACCEL, colour.alpha);
    #endif
    setPixel();
}

void Pixel::setColour(CRuchar r, CRuchar g, CRuchar b)
{
    colour.setColour(r,g,b);
    #ifdef PENJIN_SDL
        SDL_SetAlpha(pixel, SDL_SRCALPHA|SDL_RLEACCEL, 255);
    #endif
    setPixel();
}

void Pixel::setPixel()
{
    #ifdef PENJIN_SDL
        GFX::setPixel(pixel,0,0,colour);
    #endif
}

Pixel::~Pixel()
{
    //dtor
#ifdef PENJIN_SDL
    if(pixel)
        SDL_FreeSurface(pixel);
    pixel = NULL;
#endif
}

#ifdef PENJIN_SDL
    void Pixel::render(SDL_Surface* scr)
    {
        SDL_Rect d;
        d.x = position.x;
        d.y = position.y;
        SDL_BlitSurface(pixel, NULL, scr, &d);
    }
#else
    void Pixel::render()
    {
        GFX::setPixel(position.x,position.y,colour);
    }
#endif
