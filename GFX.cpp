#include "GFX.h"
namespace GFX
{
    Colour clear(BLACK);
	#ifdef PLATFORM_PC
        uint xRes = 1024;
        uint yRes = 768;
        bool fullscreen = false;
    #elif PLATFORM_WII
        uint xRes = 640;
        uint yRes = 480;
        bool fullscreen = true;
    #elif PLATFORM_PANDORA
        uint xRes = 800;
        uint yRes = 480;
        bool fullscreen = true;
    #elif PLATFORM_GP2X
        uint xRes = 320;
        uint yRes = 240;
        bool fullscreen = false;    // Enabling crashes the HWScaler.
        bool useHack = false;
    #else // Penjin 2D project
        uint xRes = 1024;
        uint yRes = 768;
        bool fullscreen = false;
    #endif
#if defined (PENJIN_SDL) || defined(PENJIN_GL)
    SDL_Surface* screen = SDL_GetVideoSurface();
#elif PENJIN_ASCII

#endif
}

#ifdef PLATFORM_GP2X
void GFX::useMMUHack(CRbool h)
{
    useHack = h;
}
#endif

void GFX::setFullscreen(CRbool fs)
{
    fullscreen = fs;
}

Colour GFX::getClearColour()
{
    return clear;
}

// Force to blit to screen now!
void GFX::forceBlit()
{
    #ifdef PLATFORM_GP2X
        //  We do MMUHack BEFORE video flip!
        if(useHack)
            MMUHack::flushCache(screen->pixels, (char*)screen->pixels  + (screen->w * screen->h));
    #endif
    #ifdef PENJIN_GL
        SDL_GL_SwapBuffers();
    #elif PENJIN_SDL
        SDL_Flip(screen);
    #elif PENJIN_CACA
        /// TODO: Pass display pointer into GFX or create here instead.
        caca_refresh_display(display);
    #endif
}

void GFX::setResolution(uint x,uint y)
{
    xRes = x;
    yRes = y;
}

void GFX::setResolution()
{
    // set an automatic(best fit?) resolution.
    setResolution(0,0);
}

PenjinErrors::PENJIN_ERRORS GFX::resetScreen()
{
    /*
    #ifdef PLATFORM_GP2X
    if(xRes == 0)
        xRes = 320;
    if(yRes == 0)
        yRes = 240;
    #endif
    */
#if defined(PENJIN_SDL) || defined(PENJIN_GL)
	const SDL_VideoInfo* info = NULL;	//Information about the current video settings
    int flags = 0;						//Flags for SDL_SetVideoMode
    //Get some video information
    info = SDL_GetVideoInfo();
    if(!info)
	{
		return PENJIN_SDL_VIDEO_QUERY_FAILED;
    }
#elif PENJIN_CACA
    canvas = cucul_create_canvas(xRes, yRes);
    display = caca_create_display(canvas);
#elif PENJIN_ASCII
    initscr();
#endif
#ifdef PENJIN_GL
        //Setup OpenGL window attributes
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    #ifdef __linux__
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    #else
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 16);
    #endif
        flags = SDL_OPENGL;
        SDL_Surface* screen = NULL;
#elif PENJIN_SDL
    #ifdef PLATFORM_GP2X
        flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
    #endif
#endif
#if defined(PENJIN_SDL) || defined(PENJIN_GL)
    if(fullscreen)
        flags = flags | SDL_FULLSCREEN;
    screen = SDL_SetVideoMode(xRes, yRes, info->vfmt->BitsPerPixel, flags);
	if(screen  == NULL )
	{
		return PENJIN_SDL_SETVIDEOMODE_FAILED;
    }
    else
    {
        xRes = screen->w;
        yRes = screen->h;
    }
#endif
#ifdef PENJIN3D
    init3DRendering();
#else
    #ifdef PENJIN_GL
        init2DRendering();
    #endif
#endif
    #ifdef PLATFORM_GP2X
        PENJIN_ERRORS e = MMUHack::init();
        if(e == PENJIN_OK)
            GFX::useMMUHack(true);
    #endif
    return PENJIN_OK;
}
#if defined(PENJIN_SDL) || defined(PENJIN_GL)
SDL_Surface* GFX::getVideoSurface(){return screen;}
void GFX::showCursor(CRbool show)
{
    if(show)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
}
#endif
#ifdef PENJIN_SDL
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
            SDL_LockSurface(scr);
    }

    void GFX::lockSurface(){lockSurface(screen);}


    void GFX::unlockSurface(SDL_Surface* scr)
    {
        // Check and unlock the surface if necessary
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

    Colour GFX::getPixel(CRint x, CRint y)
    {
        return getPixel(screen,x,y);
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
    void GFX::init2DRendering()
    {
        // Setup OpenGL
        //glDisable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        //Setup viewport
        glViewport(0, 0, xRes, yRes);

        //Setup world view
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, xRes, yRes, 0, 0, 1);

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
        void GFX::init3DRendering()
        {
            glShadeModel(GL_SMOOTH);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glViewport(0, 0, x, y);
            //Setup world view
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60.0f, (float)xRes/(float)yRes, 1.0f, xRes);
            //Setup model view
            glMatrixMode( GL_MODELVIEW );
            glColor3f(1.0f,1.0f,1.0f);
        }
    #endif
#endif

void GFX::showVideoInfo()
{
    /*SDL_Surface* screen = SDL_GetVideoSurface();*/
    cout << "Screen Info" << endl;
    cout << screen->w << "x" << screen->h << " " << StringUtility::intToString(screen->format->BitsPerPixel) << "BPP" << endl;
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
    if(src == NULL)
        return Colour(MAGENTA);
    int bpp = src->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)src->pixels + y * src->pitch + x * bpp;
    Colour c;
    switch(bpp) {
    case 1:
        c.convertColour(*p,src->format);break;

    case 2:
        c.convertColour(*(Uint16 *)p,src->format);break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            c.convertColour(p[0] << 16 | p[1] << 8 | p[2],src->format);
        else
            c.convertColour(p[0] | p[1] << 8 | p[2] << 16,src->format);
        break;
    case 4:
        c.convertColour( *(Uint32 *)p,src->format);break;

    default:
        c.setColour(MAGENTA);       /* shouldn't happen, but avoids warnings */
    }
    return c;
}

uint GFX::getXResolution()
{
    return xRes;
}

uint GFX::getYResolution()
{
    return yRes;
}

