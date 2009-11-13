#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED

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
        Colour(const PENJIN_COLOURS& colour){setColour(colour);}
        Colour(const Colour& colour)                    // Create a colour using another colour
        {
			red = colour.red;
			green = colour.green;
			blue = colour.blue;
			alpha = colour.alpha;
        }
        Colour (CRint rgb){setColour(rgb);}

        // OpenGL type colour
        void setColour(CRfloat r,CRfloat g,CRfloat b,CRfloat a);
        void setColour(CRfloat r,CRfloat g,CRfloat b){setColour(r,g,b,1.0f);}

        //  Normal colours
        void setColour(const Colour& c){setColour(c.red,c.green,c.blue,c.alpha);}
        void setColour(const uchar& r,const uchar& g,const uchar& b,const uchar& a);	//	Set the colour using RGBA
        void setColour(const uchar& r,const uchar& g,const uchar& b){setColour(r,g,b,255);}            // Set the colour using RGB
        void setColour(const PENJIN_COLOURS& colour);						//	Set the colour using predefines
        void setColour(CRint rgb);                                          // Set the colour using a Delphi int (red + green * 256 + blue * 256 * 256)

        SDL_Color getSDL_Colour();		            //	Converts the stored colour to an SDL_Color object
        Uint32 getSDL_Uint32Colour(const SDL_Surface* dst)const;
        Uint32 getSDL_Uint32Colour(){return getSDL_Uint32Colour(SDL_GetVideoSurface());}
        void convertColour(Uint32 colour);      //  Converts an SDL Uint32 colour to a Colour object

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
            #ifdef PENJIN_GL
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
            #ifdef PENJIN_GL
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
            #ifdef PENJIN_GL
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
        Colour operator*(const uchar& c)
        {
            return (*this *Colour(c,c,c));
        }
        Colour operator/(const Colour& c)
        {
            Colour b = *this;
            #ifdef PENJIN_GL
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
            return (*this /Colour(c,c,c));
        }
        //  Less Than Equal
        bool operator<=(const Colour& c){return lessThanEqual(c.red,c.green,c.blue,c.alpha);}
        bool operator<=(const PENJIN_COLOURS& colour){return operator<=(Colour(colour));}
        bool lessThanEqual(const uchar& r,const uchar& g,const uchar& b){return lessThanEqual(r,g,b,255);}
        bool lessThanEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a){return (isEqual(r,g,b,a) || lessThan(r,g,b,a));}
        //  Less Than
        bool operator<(const Colour& c){return lessThan(c.red,c.green,c.blue,c.alpha);}
        bool operator<(const PENJIN_COLOURS& colour){return operator<(Colour(colour));}
        bool lessThan(const uchar& r,const uchar& g,const uchar& b){return lessThan(r,g,b,255);}
        bool lessThan(const uchar& r,const uchar& g,const uchar& b,const uchar& a);
        //  More Than Equal
        bool operator>=(const Colour& c){return moreThanEqual(c.red,c.green,c.blue,c.alpha);}
        bool operator>=(const PENJIN_COLOURS& colour){return operator>=(Colour(colour));}
        bool moreThanEqual(const uchar& r,const uchar& g,const uchar& b){return moreThanEqual(r,g,b,255);}
        bool moreThanEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a){return (isEqual(r,g,b,a) || moreThan(r,g,b,a));}
        //  More Than
        bool operator>(const Colour& c){return !operator<(c);}
        bool operator>(const PENJIN_COLOURS& colour){return !operator<(Colour(colour));}
        bool moreThan(const uchar& r,const uchar& g,const uchar& b){return !lessThan(r,g,b,255);}
        bool moreThan(const uchar& r,const uchar& g,const uchar& b,const uchar& a){return !lessThan(r,g,b,a);}

        //  Equivalency
        bool operator==(const Colour& c){return isEqual(c.red,c.green,c.blue,c.alpha);}
        bool operator==(const PENJIN_COLOURS& colour){return operator==(Colour(colour));}
        bool isEqual(const uchar& r,const uchar& g,const uchar& b){return isEqual(r,g,b,255);}
        bool isEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a);

        //  Inequality
        bool operator!=(const Colour& colour){return !operator==(colour);}
        bool operator!=(const PENJIN_COLOURS& colour){return !operator==(colour);}
        bool notEqual(const uchar& r,const uchar& g,const uchar& b){return !isEqual(r,g,b);}
        bool notEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a){return !isEqual(r,g,b,a);}

        //  Negation - Provides the inverse colour
        Colour operator- ()const{return (Colour(WHITE) - *this);}

        //  Channel ops - swap colour channels around
        void swapRG();
        void swapGB();
        void swapRB();

        // Colour data
        #ifdef PENJIN_GL
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
