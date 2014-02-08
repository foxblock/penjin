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
#ifndef GFX_H_INCLUDED
#define GFX_H_INCLUDED

//  This is a class which will contain functions to do nice GFX effects.

#include "PenjinTypes.h"
#include "Random.h"
#include "StringUtility.h"
#include "Colour.h"
#include "ErrorHandler.h"
#ifdef PENJIN_GL
    #include <SDL/SDL_opengl.h>
#elif defined (PENJIN_SDL) || defined (PENJIN_SOFT) || defined (PENJIN_ES) || defined (PENJIN_ES2)
    #include <SDL/SDL.h>
#endif
#if defined (PENJIN_ES) || defined (PENJIN_ES2)
    #ifdef PENJIN_ES
        #include <GLES/gl.h>
    #elif PENJIN_ES2
        #include <GLES2/gl2.h>
    #endif
    #include <EGL/egl.h>
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xatom.h>
#endif
#ifdef PLATFORM_GP2X
    #include "MMUHack.h"
#elif PLATFORM_PANDORA
    #include <linux/fb.h>
    #include <sys/ioctl.h>
    #include <fcntl.h>
    //#include <unistd.h>
#endif
//#include "LUT.h"
#include <vector>
using std::vector;

namespace GFX
{
    /// Get display setting info
    void showVideoInfo();
    void setResolution();    // set an automatic resolution
    void setResolution(uint xRes,uint yRes);
    void setFullscreen(CRbool full);
    void setBPP(uint bpp);
    PenjinErrors::PENJIN_ERRORS resetScreen();            // Applies the current settings to the screen.

    uint getXResolution();
    uint getYResolution();
    uint getBPP();

    // Force to blit to screen now!
    void forceBlit();

    // PLATFORM SPECIFIC FUNCTIONS
    #ifdef PLATFORM_GP2X
        void useMMUHack(CRbool useHack);
    #endif
    void showCursor(CRbool show);
    //SPECIAL EFFECTS
    #if defined(PENJIN_SDL) || defined(PENJIN_GL) || defined(PENJIN_SOFT)
        SDL_Surface* getVideoSurface();
    #endif
    #ifdef PENJIN_SDL
        #ifdef PENJIN_SCALE2X
        void scale2x(SDL_Surface* input, SDL_Surface* output);

        #endif
        void borderColouring(SDL_Surface* screen,CRint x,CRint y,CRint w,CRint h,CRint thick,Colour baseColour);
        void borderColouring(CRint x, CRint y,CRint w,CRint h,CRint thick,Colour baseColour);
    #else
        void borderColouring(CRint x, CRint y,CRint w,CRint h,CRint thick,Colour baseColour);
    #endif
    /*ABOUT: renders a colourful border to screen.
    int x & int y are the start coords and int w & int h are the end coords.
    int thick is the border thickness -1 means a full rectangle is rendered
    Colour baseColour is the start colour that all the other colours are worked from
    */
    #ifdef PENJIN_SDL
        void renderStatic(SDL_Surface* screen,CRint xStart,CRint yStart,CRint w,CRint h,CRint spacing, CRint thickness);
        void renderStatic(CRint xStart,CRint yStart,CRint w,CRint h,CRint spacing, CRint thickness);
    #else
        void renderStatic(CRint xStart,CRint yStart,CRint w,CRint h,CRint spacing, CRint thickness);
    #endif
    /*ABOUT: render a static effect to screen.
    int xStart, yStart are the start coords
    int w, h are the end coords.
    int spacing is the number of pixels to space. A value of one means every pixel is filled
    two means every second pixel is filled
    three every third... etc
    thickness of -1 renders a full rectangle
    */
        void setPixel(CRint x, CRint y, const Colour& c);
        template <class T>
        void setPixel(const T& p, const Colour& c){setPixel(p.x,p.y,c);}
        Colour getPixel(CRint x, CRint y);
        Colour getPixel(SDL_Surface* screen,CRint x, CRint y);
        void renderPixelBuffer();   //  Renders all pixels stored in the buffer
        void clearScreen();
        void setClearColour(const Colour& c);
        Colour getClearColour();
    #ifdef PENJIN_SDL
        void setPixel(SDL_Surface* screen, CRint x, CRint y, Colour c);

        void lockSurface(SDL_Surface* screen);      //  lock the passed surface
        void lockSurface();                         //  lock the screen
        void unlockSurface(SDL_Surface* screen);    //  unlock the passed surface
        void unlockSurface();                       //  unlock the screen
        SDL_Surface* cropSurface(SDL_Surface* in, SDL_Rect* crop);    //  crop a surface
        void clearScreen(SDL_Surface* screen);      //  blank the surface
    #elif defined (PENJIN_GL) || defined (PENJIN_SOFT) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        void init2DRendering();   //  Setup a 2D rendering mode.
                                //  Also enables blending.
        #ifdef PENJIN_3D
            void init3DRendering();                     //  Setup a standard 3D rendering mode
            void perspective(CRfloat fov,CRfloat aspect,CRfloat znear,CRfloat zfar);    //  setup a perspective view
        #endif
        void loadIdentity();    // load the identity matrix
    #endif

    #if defined (PENJIN_ES) || defined (PENJIN_ES2) || defined (PENJIN_SCALE2X)
        void shutdown();
    #endif
}
#endif // GFX_H_INCLUDED
