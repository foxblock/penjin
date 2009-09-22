#include "GFX.h"

namespace GFX
{
#ifdef PENJIN_SDL
    Colour clear;
    SDL_Surface* screen;
#endif
}



#ifdef PENJIN_SDL
    void GFX::initVideoSurface(SDL_Surface* scr){screen = scr;}
    void GFX::setClearColour(const Colour& c){clear = c;}
    void GFX::borderColouring(CRint x,CRint y,CRint w,CRint h,CRint thick,Colour baseColour){borderColouring(screen,x,y,w,h,thick,baseColour);}
    void GFX::borderColouring(SDL_Surface* screen,CRint x,CRint y,CRint w,CRint h,CRint thick,Colour baseColour)
    {
        lockSurface(screen);
        Pixel t;
        //	within the box specified
        if(thick!= -1)
        {
            for(int i = w-1; i >= x; --i)
            {
                for(int j = h-1; j >= y; --j)
                {
                    //	check if the coord is within the border else continue
                    if((j<= y+thick || j>=y+h-thick) || (i <= x+thick || i>=x+w-thick))
                    {
                        baseColour.setColour((uchar)(baseColour.red-i+j),baseColour.green-i+j,baseColour.blue+baseColour.red-baseColour.green);
                        //baseColour.setColour(baseColour.red+ ,baseColour.green+lut.Lsin(j).intValue >> 16,baseColour.blue+lut.Lsin(j).intValue >> 16);
                        t.setPosition(i,j);
                        t.setColour(baseColour);
                        t.render(screen);
                    }
                }
            }
        }
        else
        {
            for(int i = w-1; i >= x; --i)
            {
                for(int j = h-1; j >= y; --j)
                {
                    baseColour.setColour((uchar)(baseColour.red-i+j),baseColour.green-i+j,baseColour.blue+baseColour.red-baseColour.green);
                    //baseColour.setColour(baseColour.red+ ,baseColour.green+lut.Lsin(j).intValue >> 16,baseColour.blue+lut.Lsin(j).intValue >> 16);
                    t.setPosition(i,j);
                    t.setColour(baseColour);
                    t.render(screen);
                }
            }
        }
        unlockSurface(screen);
    }
    void GFX::renderStatic(CRint xStart,CRint yStart,CRint w,CRint h,CRint spacing, CRint thickness){renderStatic(screen,xStart,yStart,w,h,spacing,thickness);}
    void GFX::renderStatic(SDL_Surface* screen,CRint x,CRint y,CRint w,CRint h,CRint spacing, CRint thick)
    {
        Pixel pixel;
        lockSurface(screen);
        //	Setup random numbers for 5 colours (white, black and 3 grays)
        Random::setLimits(0,2);
        //	Now randomly run through the entire screen buffer and place a randompiece of static
        if(thick == -1)
        {
            for(int i = w-1; i >= x-1; i-=spacing)
            {
                for(int j = h-1; j >= y-1; j-=spacing)
                {
                    uint colour = Random::nextInt();
                    if(colour == 0)
                        pixel.setColour(BLACK);
                    else if(colour == 1)
                        pixel.setColour(128,128,128);
                    else if(colour == 2)
                        pixel.setColour(WHITE);

                    pixel.setPosition(i,j);
                    pixel.render(screen);
                }
            }
        }
        else
        {
            for(int i = w-1; i >= x-1; i-=spacing)
            {
                for(int j = h-1; j >= y-1; j-=spacing)
                {
                    //	check if the coord is within the border else continue
                    if((j<= y+thick || j>=y+h-thick) || (i <= x+thick || i>=x+w-thick))
                    {
                        uint colour = Random::nextInt();
                        if(colour == 0)
                            pixel.setColour(BLACK);
                        else if(colour == 1)
                            pixel.setColour(64,64,64);
                        else if(colour == 2)
                            pixel.setColour(128,128,128);
                        else if(colour == 3)
                            pixel.setColour(196,196,196);
                        else if(colour == 4)
                            pixel.setColour(WHITE);
                        pixel.setPosition(i,j);
                        pixel.render(screen);
                    }
                }
            }
        }
        unlockSurface(screen);
    }

    void GFX::lockSurface(SDL_Surface* scr)
    {
        // Check and lock the surface if necessary.
        if (SDL_MUSTLOCK(scr))
            if (SDL_LockSurface(scr) < 0 )
                return;
    }

    void GFX::lockSurface(){lockSurface(screen);}


    void GFX::unlockSurface(SDL_Surface* scr)
    {
        // Check and unlock the durface if necessary
        if ( SDL_MUSTLOCK(scr) )
            SDL_UnlockSurface(scr);
    }
    void GFX::unlockSurface(){unlockSurface(screen);}
    void GFX::clearScreen(SDL_Surface* scr)
    {
        SDL_FillRect(scr,NULL,clear.getSDL_Uint32Colour());
        SDL_BlitSurface(NULL,NULL,scr,NULL);
    }
    void GFX::clearScreen(){clearScreen(screen);}
    void GFX::setPixel(SDL_Surface* scr, CRint x, CRint y, Colour c)
    {
        SDL_Rect r;
        r.x=x;
        r.y=y;
        r.w=r.h=1;
        SDL_FillRect(scr,&r,c.getSDL_Uint32Colour());
    }
    void GFX::setPixel(CRint x, CRint y, const Colour& c){setPixel(screen,x,y,c);}
    SDL_Surface* GFX::cropSurface(SDL_Surface* in, SDL_Rect* c)
    {
        SDL_Surface *cropped = NULL;
        //  Cropped surface
        cropped = SDL_CreateRGBSurface(in->flags,c->w, c->h,in->format->BitsPerPixel, 0, 0, 0, 0);
        Colour col = getPixel(cropped,0,0);
        SDL_SetColorKey(cropped, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(cropped->format,col.red,col.green,col.blue));
        SDL_BlitSurface(in,c,cropped,NULL);
        return cropped;
    }
#elif PENJIN_GL
    void GFX::setPixel(CRint x, CRint y, const Colour& colour)
    {
        glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
        glVertex2i(x,y);
    }
    Colour GFX::getPixel(CRint x, CRint y)
    {

    }
    void GFX::setClearColour(const Colour& c){glClearColor(c.red,c.green,c.blue,c.alpha);}
    void GFX::init2DRendering(CRint x, CRint y)
    {
        // Setup OpenGL
        //glDisable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        //Setup viewport
        glViewport(0, 0, x, y);

        //Setup world view
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, x, y, 0, 0, 1);

        //Setup texture matrix
        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glColor3f(1.0f,1.0f,1.0f);

        // flip textures
        //glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
        //glScalef(-1.0f, 1.0f, 1.0f);
    }

    void GFX::clearScreen(){glClear(GL_COLOR_BUFFER_BIT
    #ifdef PENJIN3D
        | GL_DEPTH_BUFFER_BIT
    #endif
    );}
    #ifdef PENJIN3D
        void GFX::init3DRendering(CRint x, CRint y)
        {
            glShadeModel(GL_SMOOTH);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glViewport(0, 0, x, y);
            //Setup world view
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60.0f, (float)x/(float)y, 1.0f, x);
            //Setup model view
            glMatrixMode( GL_MODELVIEW );
            glColor3f(1.0f,1.0f,1.0f);
        }
    #endif
#endif

void GFX::showVideoInfo()
{
    SDL_Surface* screen = SDL_GetVideoSurface();
    cout << "Screen Info" << endl;
    cout << screen->w << "x" << screen->h << " " << screen->format->BitsPerPixel << "BPP" << endl;
    #ifdef PENJIN_GL
        printf("GL Info\n");
        printf("Vendor:     %s\n",glGetString(GL_VENDOR));
        printf("Renderer:   %s\n",glGetString(GL_RENDERER));
        printf("Version:    %s\n",glGetString(GL_VERSION));
        printf("Extensions: %s\n\n",glGetString(GL_EXTENSIONS));
        int value;
        SDL_GL_GetAttribute( SDL_GL_RED_SIZE, &value );
        cout << "SDL_GL_RED_SIZE:     " << value << endl;
        SDL_GL_GetAttribute( SDL_GL_GREEN_SIZE, &value );
        cout << "SDL_GL_GREEN_SIZE:   " << value << endl;
        SDL_GL_GetAttribute( SDL_GL_BLUE_SIZE, &value );
        cout << "SDL_GL_BLUE_SIZE:    " << value << endl;
        SDL_GL_GetAttribute( SDL_GL_DEPTH_SIZE, &value );
        cout << "SDL_GL_DEPTH_SIZE:   " << value << endl;
        SDL_GL_GetAttribute( SDL_GL_DOUBLEBUFFER, &value );
        cout << "SDL_GL_DOUBLEBUFFER: " << value << endl;
    #endif
}

Colour GFX::getPixel(SDL_Surface* src, CRint x, CRint y)
{
        if(x > src->w || y > src->h)
            return Colour(255,255,255,255);
        Uint32 colour;
        //determine position
        char* pPosition = ( char* ) src->pixels ;

        //offset by y
        pPosition += ( src->pitch * y ) ;

        //offset by x
        pPosition += ( src->format->BytesPerPixel * x ) ;

        //copy pixel data
        memcpy (&colour , pPosition, src->format->BytesPerPixel );
        Colour c;
        c.convertColour(colour);
        return c;
}
