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
#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED

#include <map>

#include "PenjinTypes.h"
#include <SDL/SDL.h>
#include <algorithm>
using namespace std;
/**
  * Colour class allows manipulation of colours
  *
  * @author Kevin Winfield-Pantoja
  */


enum PENJIN_COLOURS
{
    BLACK=0,
	RED,
	LIGHT_RED,
	GREEN,
	LIGHT_GREEN,
	BLUE,
	LIGHT_BLUE,
	YELLOW,
	PURPLE,
	MAGENTA,
	CYAN,
	ORANGE,
	BROWN,
	DARK_GREY,
	GREY,
	LIGHT_GREY,
	WHITE
};

class Colour
{
    public:
        Colour(){setColour(WHITE);}
        Colour(const SDL_Color& c){setColour(c.r,c.g,c.b);}
        Colour(const uchar& r,const uchar& g,const uchar& b){setColour(r,g,b);}
        Colour(const uchar& r,const uchar& g,const uchar& b,const uchar& a){setColour(r,g,b,a);}
        // the following two are necessary, because gcc does not know whether to convert int to uchar or float
        Colour(CRint r,CRint g,CRint b){setColour(r,g,b);}
        Colour(CRint r,CRint g,CRint b,CRint a){setColour(r,g,b,a);}
        Colour(const PENJIN_COLOURS& colour){setColour(colour);}
        Colour(const Colour& colour)                    // Create a colour using another colour
        {
			red = colour.red;
			green = colour.green;
			blue = colour.blue;
			alpha = colour.alpha;
        }
        Colour (CRint rgb){setColour(rgb);}
        Colour (CRstring ident){setColour(ident);}

        // OpenGL type colour
        Colour(CRfloat r,CRfloat g,CRfloat b,CRfloat a){setOGLColour(r,g,b,a);}
        Colour(CRfloat r,CRfloat g,CRfloat b){setOGLColour(r,g,b,1.0f);}
        void setOGLColour(CRfloat r,CRfloat g,CRfloat b,CRfloat a);
        void setOGLColour(CRfloat r,CRfloat g,CRfloat b){setOGLColour(r,g,b,1.0f);}

        //  Normal colours
        void setColour(const Colour& c){setColour(c.red,c.green,c.blue,c.alpha);}
        void setColour(const uchar& r,const uchar& g,const uchar& b,const uchar& a);	//	Set the colour using RGBA
        void setColour(const uchar& r,const uchar& g,const uchar& b){setColour(r,g,b,255);}            // Set the colour using RGB
        void setColour(const PENJIN_COLOURS& colour);						//	Set the colour using predefines
        // Set the colour using an int (red * 256 * 256 + green * 256 + blue)
        // Use with a hex-based colour code converted to an int (StringUtility::hexToInt)
        void setColour(CRint rgb);
        void setColour(CRstring ident); // set the colour using a written version of the PENJIN_COLOURS

        SDL_Color getSDL_Colour();		            //	Converts the stored colour to an SDL_Color object
        Uint32 getSDL_Uint32Colour(const SDL_Surface* dst)const;
        Uint32 getSDL_Uint32Colour(){return getSDL_Uint32Colour(SDL_GetVideoSurface());}
        int getIntColour() const;
        void convertColour(Uint32 colour,SDL_PixelFormat *format);      //  Converts an SDL Uint32 colour to a Colour object
        // sends the colour through the video surface and thereby adjusts it
        // to precision loss if the display has a bit depth of 16 or lower
        // will only waste CPU time if bpp is 24 or higher
        void adjustToDisplayColour() { convertColour( getSDL_Uint32Colour(), SDL_GetVideoSurface()->format ); }

        Colour getGreyScale();  //  Get this colour as a grayscale colour.
        void toGreyScale(){*this = getGreyScale();}     //  Convert this colour to grayscale


        // Operators
        Colour operator+(const uchar& c)
        {
            return (*this +Colour(c,c,c));
        }
        Colour operator+(const Colour& c)
        {
            Colour b = *this;
            #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                b.red = min(b.red + c.red,1.0f);
                b.green = min(b.green + c.green,1.0f);
                b.blue = min(b.blue + c.blue,1.0f);
            #else
                b.red = min((uint)b.red + c.red,(uint)255);
                b.green = min((uint)b.green + c.green,(uint)255);
                b.blue = min((uint)b.blue + c.blue,(uint)255);
            #endif
            return b;
        }
        Colour operator-(const Colour& c)
        {
            Colour b = *this;
            #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                b.red = max(b.red - c.red,0.0f);
                b.green = max(b.green - c.green,0.0f);
                b.blue = max(b.blue - c.blue,0.0f);
            #else
                b.red = max(b.red - c.red,0);
                b.green = max(b.green - c.green,0);
                b.blue = max(b.blue - c.blue,0);
            #endif
            return b;
        }
        Colour operator-(const uchar& c)
        {
            return (*this -Colour(c,c,c));
        }
        Colour operator*(const Colour& c)
        {
            Colour b = *this;
            #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                b.red = min(b.red * c.red,1.0f);
                b.green = min(b.green * c.green,1.0f);
                b.blue = min(b.blue * c.blue,1.0f);
            #else
                b.red = min((uint)b.red * c.red,(uint)255);
                b.green = min((uint)b.green * c.green,(uint)255);
                b.blue = min((uint)b.blue * c.blue,(uint)255);
            #endif
            return b;
        }
        template <class T>
        Colour operator*(const T& c)
        {
            #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                red = red*(float)c;
                green = green*(float)c;
                blue = blue*(float)c;
                return *this;
            #else
                return (*this *Colour(c,c,c));
            #endif
        }
        Colour operator/(const Colour& c)
        {
            Colour b = *this;
            #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                b.red = max(b.red / c.red,0.0f);
                b.green = max(b.green / c.green,0.0f);
                b.blue = max(b.blue / c.blue,0.0f);
            #else
                b.red = max(b.red / c.red,0);
                b.green = max(b.green / c.green,0);
                b.blue = max(b.blue / c.blue,0);
            #endif
            return b;
        }
        Colour operator/(const uchar& c)
        {
            #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                float f = 1/(float)c;
                red = red*f;
                green = green*f;
                blue = blue*f;
                return *this;
            #else
                return (*this /Colour(c,c,c));
            #endif
        }
        //Colour operator/(const float& c){return Colour(red/c,green/c,blue/c,alpha);}
        //  Less Than Equal
        bool operator<=(const Colour& c)const{return lessThanEqual(c.red,c.green,c.blue,c.alpha);}
        bool operator<=(const PENJIN_COLOURS& colour)const{return operator<=(Colour(colour));}
        bool lessThanEqual(const uchar& r,const uchar& g,const uchar& b)const{return lessThanEqual(r,g,b,255);}
        bool lessThanEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const{return (isEqual(r,g,b,a) || lessThan(r,g,b,a));}
        //  Less Than
        bool operator<(const Colour& c)const{return lessThan(c.red,c.green,c.blue,c.alpha);}
        bool operator<(const PENJIN_COLOURS& colour)const{return operator<(Colour(colour));}
        bool lessThan(const uchar& r,const uchar& g,const uchar& b)const{return lessThan(r,g,b,255);}
        bool lessThan(const uchar& r,const uchar& g,const uchar& b,const uchar& a) const;
        //  More Than Equal
        bool operator>=(const Colour& c)const{return moreThanEqual(c.red,c.green,c.blue,c.alpha);}
        bool operator>=(const PENJIN_COLOURS& colour)const{return operator>=(Colour(colour));}
        bool moreThanEqual(const uchar& r,const uchar& g,const uchar& b)const{return moreThanEqual(r,g,b,255);}
        bool moreThanEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const{return (isEqual(r,g,b,a) || moreThan(r,g,b,a));}
        //  More Than
        bool operator>(const Colour& c)const{return !operator<(c);}
        bool operator>(const PENJIN_COLOURS& colour)const{return !operator<(Colour(colour));}
        bool moreThan(const uchar& r,const uchar& g,const uchar& b)const{return !lessThan(r,g,b,255);}
        bool moreThan(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const{return !lessThan(r,g,b,a);}

        //  Equivalency
        bool operator==(const Colour& c)const{return isEqual(c.red,c.green,c.blue,c.alpha);}
        bool operator==(const PENJIN_COLOURS& colour)const{return operator==(Colour(colour));}
        bool isEqual(const uchar& r,const uchar& g,const uchar& b)const{return isEqual(r,g,b,255);}
        bool isEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const;

        //  Inequality
        bool operator!=(const Colour& colour)const{return !operator==(colour);}
        bool operator!=(const PENJIN_COLOURS& colour)const{return !operator==(colour);}
        bool notEqual(const uchar& r,const uchar& g,const uchar& b)const{return !isEqual(r,g,b);}
        bool notEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const{return !isEqual(r,g,b,a);}

        //  Negation - Provides the inverse colour
        Colour operator- ()const{return (Colour(WHITE) - *this);}

        //  Channel ops - swap colour channels around
        void swapRG();
        void swapGB();
        void swapRB();

        // Colour data
        #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
            float red; // Values stores in range 0.0 - 1.0f
            float green;
            float blue;
            float alpha;

            void toGL();
        #else
            uchar red; // 0 - 256 range
            uchar green;
            uchar blue;
            uchar alpha;

            void toNormal();
        #endif
};

#endif // COLOUR_H_INCLUDED
