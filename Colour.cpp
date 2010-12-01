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
#include "Colour.h"

void Colour::setColour(const uchar& r,const uchar& g,const uchar& b,const uchar& a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        toGL();
    #endif
}

void Colour::setOGLColour(CRfloat r, CRfloat g, CRfloat b, CRfloat a)
{
    #ifdef PENJIN_FIXED
        red = fixedpoint::fix2int(r);
        green = fixedpoint::fix2int(g);
        blue = fixedpoint::fix2int(b);
        alpha = fixedpoint::fix2int(a);
    #else
        red = r;
        green = g;
        blue = b;
        alpha = a;
    #endif
    #if !defined (PENJIN_GL) && !defined (PENJIN_ES) && !defined (PENJIN_ES2)
        toNormal();
    #endif
}

void Colour::setColour(const PENJIN_COLOURS& c)
{
    if(c == RED)
	{
		red = 255;
		green = 0;
		blue = 0;
	}
    else if(c == LIGHT_RED)
	{
		red = 255;
		green = 128;
		blue = 128;
	}
	else if(c == GREEN)
	{
		red = 0;
		green = 255;
		blue = 0;
	}
    else if(c == LIGHT_GREEN)
	{
		red = 128;
		green = 255;
		blue = 128;
	}
	else if(c == BLUE)
	{
		red = 0;
		green = 0;
		blue = 255;
	}
    else if(c == LIGHT_BLUE)
	{
		red = 128;
		green = 128;
		blue = 255;
	}
	else if(c == YELLOW)
	{
		red = 255;
		green = 255;
		blue = 0;
	}
	else if(c == WHITE)
	{
		red = 255;
		green = 255;
		blue = 255;
	}
    else if(c == LIGHT_GREY)
	{
		red = 192;
		green = 192;
		blue = 192;
	}
    else if(c == GREY)
	{
		red = 128;
		green = 128;
		blue = 128;
	}
    else if(c == DARK_GREY)
	{
		red = 64;
		green = 64;
		blue = 64;
	}
	else if(c == BLACK)
	{
		red = 0;
		green = 0;
		blue = 0;
	}
	else if(c == PURPLE)
	{
		red = 128;
		green = 0;
		blue = 128;
	}
	else if(c == MAGENTA)
	{
		red = 255;
		green = 0;
		blue = 255;
	}
	else if (c == CYAN)
	{
	    red = 0;
	    green = 255;
	    blue = 255;
    }
	else if(c == ORANGE)
	{
		red = 255;
		green = 128;
		blue = 0;
	}
	else if (c == BROWN)
	{
		red = 128;
		green = 64;
		blue = 0;
	}
	alpha = 255;

    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        toGL();
    #endif
}

void Colour::setColour(CRint rgb)
{
    alpha = 255;
    red = (rgb & 0x0000ff);
    green = (rgb & 0x00ff00)/0x100;
    blue = (rgb & 0xff0000)/0x10000;
    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        toGL();
    #endif
}

bool Colour::lessThan(CRuchar r, CRuchar g, CRuchar b, CRuchar a)const
{
   if(red >= r)
      return false;
   if(green >= g)
      return false;
   if(blue >= b)
      return false;
   if(alpha >= a)
      return false;
   return true;
}

bool Colour::isEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const
{
   if(red != r)
      return false;
   if(green != g)
      return false;
   if(blue != b)
      return false;
   if(alpha != a)
      return false;
   return true;
}

SDL_Color Colour::getSDL_Colour()
{
    SDL_Color tempCol = {0,0,0,0};
    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        tempCol.r = red * 255;
        tempCol.g = green * 255;
        tempCol.b = blue * 255;
    #else
        tempCol.r = red;
        tempCol.g = green;
        tempCol.b = blue;
	#endif
	return tempCol;
}

Uint32 Colour::getSDL_Uint32Colour(const SDL_Surface* dst)const{return SDL_MapRGBA(dst->format,red,green,blue,alpha);}

void Colour::convertColour(Uint32 pixel,SDL_PixelFormat *format)
{

    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        Uint8 r,g,b,a;
        SDL_GetRGBA(pixel,format,&r,&g,&b,&a);
        red = r;
        green = g;
        blue = b;
        alpha = a;
        toGL();
    #else
        SDL_GetRGBA(pixel,format,&red,&green,&blue,&alpha);
    #endif
}

#if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
    void Colour::toGL()
    {
        const float DIV_255 = 0.003921569f;
        red = red * DIV_255;
        green = green * DIV_255;
        blue = blue * DIV_255;
        alpha = alpha * DIV_255;
    }
    Colour Colour::getGreyScale()
    {
        float t = (red + green + blue)*0.33f;
        return Colour(t,t,t);
    }
    void Colour::swapGB()
    {
        float t = green;
        green = blue;
        blue = t;
    }
    void Colour::swapRG()
    {
        float t = red;
        red = green;
        green = t;
    }
    void Colour::swapRB()
    {
        float t = red;
        red = blue;
        blue = t;
    }
#else
    void Colour::toNormal()
    {
        const uchar t = 255;
        red = red * t;
        green = green * t;
        blue = blue * t;
        alpha = alpha * t;
    }
    Colour Colour::getGreyScale()
    {
        uchar t = (red + green + blue)*0.33f;
        return Colour(t,t,t);
    }
    void Colour::swapGB()
    {
        uchar t = green;
        green = blue;
        blue = t;
    }
    void Colour::swapRG()
    {
        uchar t = red;
        red = green;
        green = t;
    }
    void Colour::swapRB()
    {
        uchar t = red;
        red = blue;
        blue = t;
    }
#endif
