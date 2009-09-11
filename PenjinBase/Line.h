#ifndef LINE_H
#define LINE_H

#include "PenjinTypes.h"
#include "Colour.h"
#ifdef PENJIN_GL
#include <SDL/SDL_opengl.h>
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
            Point3df start;
            Point3df end;
        #else
            Point2df start;
            Point2df end;
        #endif
        float lineWidth;
        Colour colour;
};

#endif // LINE_H
