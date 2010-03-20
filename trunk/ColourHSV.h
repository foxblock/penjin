#ifndef COLOURHSV_H
#define COLOURHSV_H
#include "Colour.h"

class ColourHSV
{
    public:
        ColourHSV();
        ColourHSV(const Colour& c);
        ColourHSV(const ColourHSV& c);
        ColourHSV(CRuchar h,CRuchar s, CRuchar v);
        ColourHSV(CRuchar h,CRuchar s, CRuchar v, CRuchar alpha);
        ~ColourHSV();

        //  set the Colour


        //  ColourHSV data
        uchar hue;
        uchar saturation;
        uchar value;
        uchar alpha;
};

#endif // COLOURHSV_H
