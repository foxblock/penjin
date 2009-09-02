#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED

#include "PenjinTypes.h"
#include <SDL/SDL.h>

 /**
  * Colour class allows manipulation of colours
  *
  * @author Kevin Winfield-Pantoja
  */


enum PENJIN_COLOURS
{
    BLACK=0,
	RED,
	GREEN,
	BLUE,
	WHITE,
	YELLOW,
	PURPLE,
	MAGENTA,
	ORANGE,
	BROWN
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

        void setColour(const Colour& c){setColour(c.red,c.green,c.blue,c.alpha);}
        void setColour(const uchar& r,const uchar& g,const uchar& b);            // Set the colour using RGB
        void setColour(const uchar& r,const uchar& g,const uchar& b,const uchar& a);	//	Set the colour using RGBA
        void setColour(const PENJIN_COLOURS& colour);						//	Set the colour using predefines
        void setColour(CRint rgb);                                          // Set the colour using a Delphi int (red + green * 256 + blue * 256 * 256)

        SDL_Color getSDL_Colour();		            //	Converts the stored colour to an SDL_Color object
        Uint32 getSDL_Uint32Colour(const SDL_Surface* dst)const;
        Uint32 getSDL_Uint32Colour(){return getSDL_Uint32Colour(SDL_GetVideoSurface());}
        void convertColour(Uint32 colour);      //  Converts an SDL Uint32 colour to a Colour object


        // Operators
        Colour operator+(const uchar& c)
        {
            Colour b;
            b.setColour(c+red,c+green,c+blue,alpha);
            return b;
        }
        Colour operator+(const Colour& c)
        {
            Colour b = *this;
            b.red+=c.red;
            b.green+=c.green;
            b.blue+=c.blue;
            b.alpha+=c.alpha;
            return b;
        }
        Colour operator-(const Colour& c)
        {
            Colour b = *this;
            b.red-=c.red;
            b.green-=c.green;
            b.blue-=c.blue;
            b.alpha-=c.alpha;
            return b;
        }
        Colour operator-(const uchar& c)
        {
            Colour b;
            b.setColour(red-c,green-c,blue-c,alpha);
            return b;
        }
        Colour operator*(const Colour& c)
        {
            Colour b = *this;
            b.red*=c.red;
            b.green*=c.green;
            b.blue*=c.blue;
            b.alpha*=c.alpha;
            return b;
        }
        Colour operator*(const uchar& c)
        {
            Colour b;
            b.setColour(c*red,c*green,c*blue,alpha);
            return b;
        }
        Colour operator/(const Colour& c)
        {
            Colour b = *this;
            b.red/=c.red;
            b.green/=c.green;
            b.blue/=c.blue;
            b.alpha/=c.alpha;
            return b;
        }
        Colour operator/(const uchar& c)
        {
            Colour b;
            b.setColour(red/c,green/c,blue/c,alpha);
            return b;
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

        // Colour data
        uchar red;
        uchar green;
        uchar blue;
        uchar alpha;
};

#endif // COLOUR_H_INCLUDED
