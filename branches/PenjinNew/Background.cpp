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
#include "Background.h"


Background::Background()
{
	bg = 0;
	position.x = 0;
	position.y = 0;
	#ifdef PENJIN_SDL
        screen = GFX::getVideoSurface();
    #endif
}

Background::~Background(){};

PENJIN_ERRORS Background::loadBackground(CRstring file){return img.loadImageNoKey(file);}
#ifdef PENJIN_SDL
    void Background::render(SDL_Surface *scr){img.renderImage(bg,scr,position.x,position.y);}
#else
    void Background::render(){img.renderImage(bg,position.x,position.y);}
#endif
uint Background::getBG()const{return bg;}

void Background::setBG(CRuint bg){this->bg = bg;}

void Background::toGreyScale()
{
    img.toGreyScale();
}


