#ifndef PIXEL_H
#define PIXEL_H

#include "PenjinTypes.h"
#include "Colour.h"
#include "GFX.h"

class Pixel
{
    public:
        Pixel();

        template <class T>
        Pixel(const T& x, const T& y)
        {
            setPosition(x,y);
            init();
            setPixel();
        }

        template <class T>
        Pixel(const T& x,  const T& y, const Colour& c)
        {
            setPosition(x,y);
            init();
            setColour(c);
            setPixel();
        }

        template <class S,class T>
        Pixel(const S& x, const T& y)
        {
            setPosition(x,y);
            init();
            setPixel();
        }

        template <class S,class T>
        Pixel(const S& x,  const T& y, const Colour& c)
        {
            setPosition(x,y);
            init();
            setColour(c);
            setPixel();
        }

        template <class T>
        Pixel(const T& p)
        {
            setPosition(p);
            init();
            setPixel();
        }

        template <class T>
        Pixel(const T& p, const Colour& c)
        {
            setPixel(p,c);
        }
        template <class T>
        void setPixel(const T& p, const Colour& c)
        {
            setPosition(p);
            init();
            setColour(c);
            setPixel();
        }
        void setColour(const Colour& c);
        void setColour(CRuchar r, CRuchar g, CRuchar b, CRuchar a);
        void setColour(CRuchar r, CRuchar g, CRuchar b);
        Colour getColour()const{return colour;}
        uchar getRed()const{return colour.red;}
        uchar getGreen()const{return colour.green;}
        uchar getBlue()const{return colour.blue;}
        uchar getAlpha()const{return colour.alpha;}
        void setRed(CRuchar r){colour.red=r;}
        void setGreen(CRuchar g){colour.green=g;}
        void setBlue(CRuchar b){colour.blue=b;}
        void setAlpha(CRuchar a)
        {
            colour.alpha=a;
            #ifdef PENJIN_SDL
                SDL_SetAlpha(pixel, SDL_SRCALPHA|SDL_RLEACCEL, colour.alpha);
            #endif
        }
        template <class T>
        void setPosition(const T& x, const T& y){position.x=x;position.y=y;}
    #ifdef PENJIN_FIXED
        void setPosition(CRFixed x, CRFixed y)
        {
            position.x=fixedpoint::fix2int(x+0.5f);
            position.y=fixedpoint::fix2int(y+0.5f);
        }
    #else
        void setPosition(CRfloat x, CRfloat y){position.x=x+0.5f;position.y=y+0.5f;}
    #endif
        template <class T>
        void setPosition(const T& p){position.x = p.x;position.y=p.y;}

    #ifdef PENJIN_SDL
        void render(SDL_Surface* screen);   //  Blit to a specific surface
        void render(){render(screen);}      //  Blit to screen surface
    #else
        void render();
    #endif



        ~Pixel();
    private:
        void init();
        void setPixel();
        Vector2di position;
        Colour colour;
    #ifdef PENJIN_SDL
        SDL_Surface* pixel;     //  Pixel to blit to the screen
        SDL_Surface* screen;    //  pointer to screen surface
    #endif
};

#endif // PIXEL_H
