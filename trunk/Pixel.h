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
        void setPosition(const T& p)
        {
            position.x = p.x;
            position.y = p.y;
            #ifdef PENJIN_3D
                position.z = p.z;
            #endif
        }

    #ifdef PENJIN_SDL
        Vector2di getPosition()const{return position;}
    #else
        #ifdef PENJIN_3D
            Vector3df getPosition()const{return position;}
        #else
            Vector2df getPosition()const{return position;}
        #endif
    #endif


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

        Colour colour;
    #ifdef PENJIN_SDL
        Vector2di position;
        SDL_Surface* pixel;     //  Pixel to blit to the screen
        SDL_Surface* screen;    //  pointer to screen surface
    #else
        #ifdef PENJIN_3D
            Vector3df position;
        #else
            Vector2df position;
        #endif
    #endif
};

#endif // PIXEL_H
