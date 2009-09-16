#include "Rectangle.h"

Rectangle::Rectangle()
{
    //ctor
    position.x = position.y;
    dimensions.x = dimensions.y = 1;
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
    #endif
}

#ifdef PENJIN_SDL
    Rectangle::Rectangle(const SDL_Rect& r)
    {
        position.x = r.x;
        position.y = r.y;
        dimensions.x = r.w;
        dimensions.y = r.h;
        scale.x = scale.y = 1.0f;
        angle = 0.0f;
        #ifdef PENJIN_SDL
            screen = SDL_GetVideoSurface();
            rectangle = NULL;
        #endif
    }
#endif

void Rectangle::init()
{
#ifdef PENJIN_SDL
    rectangle = NULL;
    rectangle = SDL_CreateRGBSurface(SDL_SWSURFACE, dimensions.x, dimensions.y, screen->format->BitsPerPixel, NULL, NULL, NULL, NULL);
#endif
}

Rectangle::~Rectangle()
{
    //dtor
#ifdef PENJIN_SDL
    if(rectangle)
        SDL_FreeSurface(rectangle);
    rectangle = NULL;
#endif
}

#ifdef PENJIN_SDL
void Rectangle::render(SDL_Surface* scr)
{
    SDL_Rect dst;
    dst.x = position.x;
    dst.y = position.y;
    dst.w = dimensions.x;
    dst.h = dimensions.y;
    SDL_BlitSurface(rectangle, NULL, scr, &dst);
}
#else
void Rectangle::render()
{
    // Scale and rotate
    glPushMatrix();

    #ifdef PENJIN3D
        glScalef(scale.x, scale.y, scale.z);
        glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    #else
        glScalef(scale.x,scale.y,1.0f);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    #endif
    //Setup model view
    //glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glAlphaFunc(GL_GREATER,0.1f);
        glEnable(GL_ALPHA_TEST);
            //glEnable(GL_BLEND);
            //  Set OpenGL alpha and colour
                glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
                glBegin(GL_QUADS);
                    #ifdef PENJIN3D
                        glVertex3f(position.x, position.y,  position.z);
                    #else
                        glVertex2f(position.x,position.y);
                    #endif
                    #ifdef PENJIN3D
                        glVertex3f(position.x + dimensions.x, position.y, position.z);
                    #else
                        glVertex2f(position.x + dimensions.x, position.y);
                    #endif
                    #ifdef PENJIN3D
                        glVertex3f(position.x + dimensions.x, position.y + dimensions.y, position.z);
                    #else
                        glVertex2f(position.x + dimensions.x, position.y + dimensions.y);
                    #endif
                    #ifdef PENJIN3D
                        glVertex3f(position.x, position.y + dimensions.y, position.z);
                    #else
                        glVertex2f(position.x, position.y + dimensions.y);
                    #endif
                glEnd();
            //glDisable(GL_BLEND);
        glDisable(GL_ALPHA_TEST);
    glPopMatrix();
}
#endif

#ifdef PENJIN_SDL
    void Rectangle::resize()
    {
        if(!rectangle)
        {
            // If the requested dimensions are larger than what is available we need a larger surface
            init();
        }
        else if(dimensions.x > rectangle->w || dimensions.y > rectangle->h)
        {
            SDL_FreeSurface(rectangle);
            init();
        }
        // Surface should now be big enough
    }

    void Rectangle::setRectangle()
    {
        SDL_Rect t;
        t.x=t.y=0;
        t.w = dimensions.x;
        t.h = dimensions.y;
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format,colour.red+1,colour.green+1,colour.blue+1));
        SDL_SetColorKey(rectangle, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(rectangle->format,colour.red+1,colour.green+1,colour.blue+1));
        SDL_FillRect(rectangle, &t, SDL_MapRGB(rectangle->format,colour.red,colour.green,colour.blue));
        if(colour.alpha != SDL_ALPHA_OPAQUE)
            SDL_SetAlpha(rectangle, SDL_SRCALPHA|SDL_RLEACCEL, colour.alpha);
    }
#endif
