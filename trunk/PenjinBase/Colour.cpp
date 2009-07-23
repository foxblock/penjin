#include "Colour.h"

void Colour::setColour(const uchar& r,const uchar& g,const uchar& b,const uchar& a)
{
   red = r;
   green = g;
   blue = b;
   alpha = a;
}

void Colour::setColour(const uchar& r,const uchar& g,const uchar& b){setColour(r,g,b,255);}

void Colour::setColour(const PENJIN_COLOURS& c)
{
    if(c == RED)
	{
		red = 255;
		green = 0;
		blue = 0;
	}
	else if(c == GREEN)
	{
		red = 0;
		green = 255;
		blue = 0;
	}
	else if(c == BLUE)
	{
		red = 0;
		green = 0;
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
}

bool Colour::lessThan(CRuchar r, CRuchar g, CRuchar b, CRuchar a)
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

bool Colour::isEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a)
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
	SDL_Color tempCol;
	tempCol.r = red;
	tempCol.g = green;
	tempCol.b = blue;
	return tempCol;
}

Uint32 Colour::getSDL_Uint32Colour(const SDL_Surface* dst)const{return SDL_MapRGBA(dst->format,red,green,blue,alpha);}

void Colour::convertColour(Uint32 c)
{
    //Change from an "int color" to an SDL_Color
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        alpha = (c & 0xff000000)/0x1000000;
        red = (c & 0x00ff0000)/0x10000;
        green = (c &0x0000ff00)/0x100;
        blue =  (c & 0x000000ff);
    #else
        red = (c & 0x000000ff);
        green = (c &0x0000ff00)/0x100;
        blue = (c & 0x00ff0000)/0x10000;
        alpha = (c & 0xff000000)/0x1000000;
    #endif
}
