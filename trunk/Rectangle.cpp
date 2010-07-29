#include "Rectangle.h"

Rectangle::Rectangle()
{
    //ctor
    position.x = position.y = 0;
    dimensions.x = dimensions.y = 1;
    thickness = 0;
    #ifdef PENJIN_3D
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

#ifdef PENJIN_SDL
    Rectangle::Rectangle(const SDL_Rect& r)
    {
        position.x = r.x;
        position.y = r.y;
        dimensions.x = r.w;
        dimensions.y = r.h;
        scale.x = scale.y = 1.0f;
        angle = 0.0f;
        thickness = 0;
        #ifdef PENJIN_SDL
            screen = SDL_GetVideoSurface();
            rectangle = NULL;
            init();
        #endif
    }
#endif

void Rectangle::init()
{
#ifdef PENJIN_SDL
    rectangle = NULL;
    rectangle = SDL_CreateRGBSurface(SDL_SWSURFACE, dimensions.x, dimensions.y, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);
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
    // If the domensions are impossible don't draw the rect
    if(dimensions.x <= 0 || dimensions.y <= 0)
        return;
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
    // If the domensions are impossible don't draw the rect
    if(dimensions.x <= 0 || dimensions.y <= 0)
        return;
    // Scale and rotate
    glPushMatrix();

    #ifdef PENJIN_3D
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
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glAlphaFunc(GL_GREATER,0.1f);
        //glEnable(GL_ALPHA_TEST);
            glEnable(GL_BLEND);
            //  Set OpenGL alpha and colour
                glEnableClientState(GL_VERTEX_ARRAY);
                    //  prepare vertices
                    #ifdef PENJIN_3D
                        float verts[] = {   position.x,position.y + dimensions.y,position.z,
                                            position.x + dimensions.x,position.y + dimensions.y,position.z,
                                            position.x + dimensions.x, position.y, position.z,
                                            position.x,position.y,position.z};
                        glVertexPointer(3, GL_FLOAT, 0,verts);
                    #else
                        float verts[] = {   position.x,position.y + dimensions.y,
                                            position.x + dimensions.x,position.y + dimensions.y,
                                            position.x + dimensions.x, position.y,
                                            position.x,position.y};
                        glVertexPointer(2, GL_FLOAT, 0,verts);
                    #endif
                glEnableClientState(GL_COLOR_ARRAY);
                    float c[] = {  colour.red, colour.green, colour.blue, colour.alpha};
                    glColorPointer(1, GL_FLOAT, 0,c);
                    if(thickness>0)
                    {
                        glLineWidth(thickness);
                        glDrawArrays(GL_LINE_LOOP,0,4);
                    }
                    else
                    {
                        glDrawArrays(GL_TRIANGLE_FAN,0,4);
                    }
                glDisableClientState(GL_VERTEX_ARRAY);
                glDisableClientState(GL_COLOR_ARRAY);
            glDisable(GL_BLEND);
        //glDisable(GL_ALPHA_TEST);
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
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(screen->format,colour.red+8,colour.green+8,colour.blue+8));
        SDL_FillRect(rectangle, &t, SDL_MapRGB(screen->format,colour.red,colour.green,colour.blue));
        if(thickness>0)
        {
            t.x+=thickness;
            t.y+=thickness;
            t.w-=thickness*2;
            t.h-=thickness*2;
            //  do some checks to see if the borders are close enough to render a normal rect
            if(t.w < dimensions.x && t.h < dimensions.y)
                SDL_FillRect(rectangle, &t, SDL_MapRGB(screen->format,colour.red+8,colour.green+8,colour.blue+8));
        }
        SDL_SetAlpha(rectangle, SDL_SRCALPHA|SDL_RLEACCEL, colour.alpha);
        SDL_SetColorKey(rectangle, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format,colour.red+8,colour.green+8,colour.blue+8));
    }
#endif
