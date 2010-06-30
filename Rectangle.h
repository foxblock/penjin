#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "PenjinTypes.h"
#include "Colour.h"
#include "GFX.h"

#ifdef PENJIN_GL
#include <SDL/SDL_opengl.h>
#elif PENJIN_ES || PENJIN_ES2
    #include <GLES/gl.h>
    #include <GLES/egl.h>
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
        Rectangle(const T& w, const T& h)
        {
            position.x = position.y = 0;
            dimensions.x = w;
            dimensions.y = h;
            thickness = 0;
            #ifdef PENJIN3D
                scale.x = scale.y = scale.z = 1.0f;
                rotation.x = rotation.y = rotation.z = 0.0f;
            #else
                scale.x = scale.y = 1.0f;
                angle = 0.0f;
            #endif
            colour = WHITE;
            #ifdef PENJIN_SDL
                screen = SDL_GetVideoSurface();
                rectangle = NULL;
                init();
            #endif
        }

        template <class T>
        void setPosition(const T& x, const T& y){position.x = x; position.y=y;}

        template <class T>
        void setPosition(const T& pos) {position.x = pos.x; position.y = pos.y;};

        template <class T>
        void setDimensions(const T& w, const T& h)
        {
            dimensions.x = w; dimensions.y = h;
            #ifdef PENJIN_SDL
                resize();
                setRectangle();
            #endif
        }

        template <class T, class S>
        void setDimensions(const T& w, const S& h)
        {
            dimensions.x = w; dimensions.y = h;
            #ifdef PENJIN_SDL
                resize();
                setRectangle();
            #endif
        }

        template <class T>
        void setDimensions(const T& size)
        {
            dimensions.x = size.x;
	    dimensions.y = size.y;
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
        void setAlpha(CRuchar a)
        {
            colour.alpha=a;
            #ifdef PENJIN_SDL
                SDL_SetAlpha(rectangle, SDL_SRCALPHA|SDL_RLEACCEL, colour.alpha);
            #endif
        }
#ifdef PENJIN_SDL
    void setThickness(CRuint t)
    {
        thickness = t;
        setRectangle();
    }
#else
    void setThickness(CRfloat t){thickness = t;}
#endif
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
        float thickness;
    #else
        Vector2df position;
        Vector2df scale;
        float angle;
        uint thickness;
    #endif

    #ifdef PENJIN_SDL
        SDL_Surface* rectangle;
        SDL_Surface* screen;
        void resize();          //  enlarges the surface if needed.
        void setRectangle();    //  blits the rect to the surface.
    #endif
};
#endif // RECTANGLE_H
