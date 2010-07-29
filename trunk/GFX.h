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

    #if defined (PENJIN_ES) || defined (PENJIN_ES2)
        void shutdown();
    #endif
}
#endif // GFX_H_INCLUDED
