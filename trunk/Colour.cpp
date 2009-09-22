#include "Colour.h"

void Colour::setColour(const uchar& r,const uchar& g,const uchar& b,const uchar& a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
    #ifdef PENJIN_GL
        toGL();
    #endif
}

void Colour::setColour(CRfloat r, CRfloat g, CRfloat b, CRfloat a)
{

    red = r;
    green = g;
    blue = b;
    alpha = a;
    #ifndef PENJIN_GL
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

    #ifdef PENJIN_GL
        toGL();
    #endif
}

void Colour::setColour(CRint rgb)
{
    alpha = 255;
    red = (rgb & 0x0000ff);
    green = (rgb & 0x00ff00)/0x100;
    blue = (rgb & 0xff0000)/0x10000;
    #ifdef PENJIN_GL
        toGL();
    #endif
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
	#ifdef PENJIN_GL
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

void Colour::convertColour(Uint32 c)
{
    //Change from an "int color" to a Colour
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
    #ifdef PENJIN_GL
        toGL();
    #endif
}

#ifdef PENJIN_GL
    void Colour::toGL()
    {
        const float DIV_255 = 0.003921569f;
        red = red * DIV_255;
        green = green * DIV_255;
        blue = blue * DIV_255;
        alpha = alpha * DIV_255;
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
#endif
