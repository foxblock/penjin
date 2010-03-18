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
#elif PENJIN_SDL
    #include <SDL/SDL.h>
#endif
#ifdef PLATFORM_GP2X
    #include "MMUHack.h"
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
    PenjinErrors::PENJIN_ERRORS resetScreen();            // Applies the current settings to the screen.

    uint getXResolution();
    uint getYResolution();

    // Force to blit to screen now!
    void forceBlit();

    // PLATFORM SPECIFIC FUNCTIONS
    #ifdef PLATFORM_GP2X
        void useMMUHack(CRbool useHack);
    #endif

    //SPECIAL EFFECTS
    #if defined(PENJIN_SDL) || defined(PENJIN_GL)
        SDL_Surface* getVideoSurface();
        void showCursor(CRbool show);
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
    #elif PENJIN_GL
        void init2DRendering();   //  Setup a 2D rendering mode.
                                //  Also enables blending.
        #ifdef PENJIN3D
            void init3DRendering();                     //  Setup a standard 3D rendering mode
        #endif
    #endif
}
#endif // GFX_H_INCLUDED
