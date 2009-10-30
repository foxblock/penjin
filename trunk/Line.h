#ifndef LINE_H
#define LINE_H

#include "PenjinTypes.h"
#include "Colour.h"
#ifdef PENJIN_GL
#include <SDL/SDL_opengl.h>
#elif PENJIN_SDL
#include <SDL/SDL_gfxPrimitives.h>
#endif
class Line
{
    public:
        Line();

        virtual ~Line();

        template <class T>
        void setStartPosition(const T& pos){start = pos;}
        template <class T>
        void setEndPosition(const T& pos){end = pos;}

        void setColour(const Colour& c){colour = c;}
        void setLineWidth(CRfloat w){lineWidth = w;}

        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);
        #endif
        void render();

    private:
        #ifdef PENJIN3D
            Point3di start;
            Point3di end;
        #else
            Point2di start;
            Point2di end;
        #endif
        float lineWidth;
        Colour colour;
        #ifdef PENJIN_SDL
        SDL_Surface* screen;
        #endif
};

#endif // LINE_H
