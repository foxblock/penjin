#ifndef COLOURHSL_H
#define COLOURHSL_H
#include "Colour.h"

class ColourHSL
{
    public:
        ColourHSL();
        ColourHSL(const Colour& c){setColour(c);}
        ColourHSL(const ColourHSL& c){setColour(c);}
        ColourHSL(CRuchar h,CRuchar s, CRuchar l){setColour(h,s,l);}
        ColourHSL(CRuchar h,CRuchar s, CRuchar l, CRuchar a){setColour(h,s,l,a);}

        ///  set the Colour
        // OpenGL type HSL colour
        void setColour(CRfloat h,CRfloat s,CRfloat l,CRfloat a);
        void setColour(CRfloat h,CRfloat s,CRfloat l){setColour(h,s,l,1.0f);}

        //  Normal HSL colours
        void setColour(const Colour& c); // Convert from RGB colour
        void setColour(const ColourHSL& c);
        void setColour(const uchar& h,const uchar& s,const uchar& l,const uchar& a);
        void setColour(const uchar& h,const uchar& s,const uchar& l){setColour(h,s,l,255);}
        void setColour(const PENJIN_COLOURS& c){setColour(Colour(c));}//	Set the colour using predefines

        // Convert to RGBA Colour object
        Colour getColourRGBA();

        //  ColourHSV data
        uchar hue;
        uchar saturation;
        uchar lightness;
        uchar alpha;
};

#endif // COLOURHSL_H
