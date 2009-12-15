#include "ColourHSL.h"

ColourHSL::ColourHSL()
{
    //ctor
    // default to WHITE
    #ifdef PENJIN_GL
        lightness = 1.0f;
        alpha = 1.0f;
    #else
        lightness = 255;
        alpha = 255;
    #endif
    hue = 0;
    saturation = 0;
}

// Colour is already in HSL format
void ColourHSL::setColour(const ColourHSL& c)
{
    hue = c.hue;
    saturation = c.saturation;
    lightness = c.lightness;
    alpha = c.alpha;
}

//  Convert from RGBA Colour object
void ColourHSL::setColour(const Colour& c)
{
    //  if RGB components are equal then it is a greyscale Colour
    if((c.red == c.green) && (c.green == c.blue))
    {
        // grey has no hur or saturation.
        hue = 0;
        saturation = 0;
        lightness = c.red; // all equal so doesn't matter which component is copied.
    }
    else
    {
        #ifdef PENJIN_SDL
            uchar maxC = max(c.red, max(c.green, c.blue));
            uchar minC = min(c.red, min(c.green, c.blue));
            lightness = (minC + maxC) *0.5f;

            if(lightness < 127)
                saturation = (maxC - minC) / float(maxC + minC);
            else
                saturation = (maxC - minC) / float(511 - maxC - minC);

            if(c.red == maxC)
                hue = (c.green - c.blue) / float(maxC - minC);
            else if(c.green == maxC)
                hue = 511 + (c.blue - c.red) / float(maxC - minC);
            else
                hue = 1023 + (c.red - c.green) / float(maxC - minC);

            hue *= 0.666f;   //  Bring the hue within colour range
            if(hue < 0)
                hue+=255;
        #else
            float maxC = max(c.red, max(c.green, c.blue));
            float minC = min(c.red, min(c.green, c.blue));
            lightness = (minC + maxC) *0.5f;

            if(lightness < 0.5f)
                saturation = (maxC - minC) / (maxC + minC);
            else
                saturation = (maxC - minC) / (2.0f - maxC - minC);

            if(c.red == maxC)
                hue = (c.green - c.blue) / (maxC - minC);
            else if(c.green == maxC)
                hue = 2.0f + (c.blue - c.red) / (maxC - minC);
            else
                hue = 4.0f + (c.red - c.green) / (maxC - minC);

            hue *= 0.666f;   //  Bring the hue within colour range
            if(hue < 0)
                ++hue;
        #endif
    }
}

//  HSL components 0-255
void ColourHSL::setColour(CRuchar h, CRuchar s, CRuchar l, CRuchar a)
{
    #ifdef PENJIN_GL
        const float DIV_255 = 0.003921569f;
        hue = h*DIV_255;
        saturation = s*DIV_255;
        lightness = l*DIV_255;
        alpha = a*DIV_255;
    #else
        hue = h;
        saturation = s;
        lightness = l;
        alpha = a;
    #endif
}

// HSL components 0.0f - 1.0f
void ColourHSL::setColour(CRfloat h, CRfloat s, CRfloat l, CRfloat a)
{
    #ifdef PENJIN_GL
        hue = h;
        saturation = s;
        lightness = l;
        alpha = a;
    #else
        hue = h*255;
        saturation = s*255;
        lightness = l*255;
        alpha = a*255;
    #endif
}

Colour ColourHSL::getColourRGBA()
{
    //  Sat of zero means grey so all RGB components are set to lightness
    if(saturation == 0)
        return Colour(lightness,lightness,lightness,alpha);

    //  We need to work out components if this is not the case.
    #ifdef PENJIN_GL
        float t1,t2;
        float tIn[3];
        float tOut[3];
        if(lightness < 0.5f)
            t2 = lightness * (1 + saturation);
        else
            t2 = (lightness + saturation) - (lightness * saturation);
        t1 = 2 * lightness - t2;
        //Red
        tIn[0] = hue + 1.0f*0.333f;
        if(tIn[0] > 1)
            --tIn[0];
        //Green
        tIn[1] = hue;
        tIn[1] = hue - 1.0f*0.333f;
        //Blue
        if(tIn[2] < 0)
            ++tIn[2];

        //  Convert RGB components
        for(int i = 2; i >=0; --i)
        {
            if(tIn[i] < 1.0f*0.666f)
                tOut[i] = t1 + (t2 - t1) * 6.0f * tIn[i];
            else if(tIn[i] < 0.5f)
                tOut[i] = t2;
            else if(tIn[i] < 2.0f *0.333f)
                tOut[i] = t1 + (t2 - t1) * ((2.0f * 0.333f) - tIn[i]) * 6.0f;
            else
                tOut[i] = t1;
        }
    #else
        uchar t1,t2;
        uchar tIn[3];
        uchar tOut[3];
        if(lightness < 127)
            t2 = lightness * (255 + saturation);
        else
            t2 = (lightness + saturation) - (lightness * saturation);
        t1 = 512 * lightness - t2;
        //Red
        tIn[0] = hue + 255*0.333f;
        if(tIn[0] > 255)
            --tIn[0];
        //Green
        tIn[1] = hue;
        tIn[1] = hue - 255*0.333f;
        //Blue
        if(tIn[2] < 0)
            ++tIn[2];

        //  Convert RGB components
        for(int i = 2; i >=0; --i)
        {
            if(tIn[i] < 255*0.666f)
                tOut[i] = t1 + (t2 - t1) * 6.0f * tIn[i];
            else if(tIn[i] < 127)
                tOut[i] = t2;
            else if(tIn[i] < 511 *0.333f)
                tOut[i] = t1 + (t2 - t1) * ((511 * 0.333f) - tIn[i]) * 6.0f;
            else
                tOut[i] = t1;
        }
    #endif
    return Colour(tOut[0],tOut[1],tOut[2],alpha);
}