#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "PenjinTypes.h"
#include "Colour.h"
#ifdef PENJIN_GL
#include <SDL/SDL_opengl.h>
#endif
/*
This class is a strict simple Rectangle.
Use the Quad class for uneven quads
*/

class Rectangle
{
    public:
        Rectangle();
    #ifdef PENJIN_SDL
        Rectangle(const SDL_Rect& r);
    #endif

        template <class T>
        Rectangle(const T& x, const T& y){position.x = x; position.y=y;}

        template <class T>
        void setPosition(const T& x, const T& y){position.x = x; position.y=y;}

        template <class T>
        void setDimensions(const T& w, const T& h)
        {
            dimensions.x = w; dimensions.y = h;
            #ifdef PENJIN_SDL
                resize();
                setRectangle();
            #endif
        }

        void setColour(const Colour& c)
        {
            colour = c;
            #ifdef PENJIN_SDL
                setRectangle();
            #endif
        }

        void init();

        virtual ~Rectangle();
    #ifdef PENJIN_SDL
        virtual void render(SDL_Surface* screen);   //  render to specific surface
        virtual void render(){render(screen);}      //  render to screen surface
    #else
        virtual void render();
    #endif

    protected:

        Vector2di dimensions;
        Colour colour;
    #ifdef PENJIN3D
        Vector3df position;
        Vector3df scale;
        Vector3df rotation;
    #else
        Vector2df position;
        Vector2df scale;
        float angle;
    #endif

    #ifdef PENJIN_SDL
        SDL_Surface* rectangle;
        SDL_Surface* screen;
        void resize();          //  enlarges the surface if needed.
        void setRectangle();    //  blits the rect to the surface.
    #endif
};

#endif // RECTANGLE_H
