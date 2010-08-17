#include "GFX.h"
#include "NumberUtility.h"
namespace GFX
{
    uint bpp = 0;
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
        #ifndef FBIO_WAITFORVSYNC
            #define FBIO_WAITFORVSYNC _IOW('F', 0x20, __u32)
        #endif
    #elif PLATFORM_GP2X
        uint xRes = 320;
        uint yRes = 240;
        bool fullscreen = false;    // Enabling crashes the HWScaler.
        bool useHack = false;
    #elif PLATFORM_DINGOO
        uint xRes = 320;
        uint yRes = 240;
        bool fullscreen = false;
    #else // Penjin 2D project
        uint xRes = 1024;
        uint yRes = 768;
        bool fullscreen = false;
    #endif
#if defined (PENJIN_SDL) || defined(PENJIN_GL)
    #if defined PENJIN_SDL && PENJIN_SCALE2X
        SDL_Surface* scaled = SDL_GetVideoSurface();
        SDL_Surface* screen = NULL;
    #else
        SDL_Surface* screen = SDL_GetVideoSurface();
    #endif
#elif PENJIN_ASCII

#endif
    vector <ColourVertex> pixBuff;

#if defined(PENJIN_ES) || defined(PENJIN_ES2)
	// X11 variables
	Window				x11Window	= 0;
	Display*			x11Display	= 0;
	long				x11Screen	= 0;
	XVisualInfo*		x11Visual	= 0;
	Colormap			x11Colormap	= 0;

	// EGL variables
	EGLDisplay			eglDisplay	= 0;
	EGLConfig			eglConfig	= 0;
	EGLSurface			eglSurface	= 0;
	EGLContext			eglContext	= 0;
	enum
	{
	_NET_WM_STATE_REMOVE =0,
	_NET_WM_STATE_ADD = 1,
	_NET_WM_STATE_TOGGLE =2
	};

#endif
}

#ifdef PLATFORM_GP2X
    void GFX::useMMUHack(CRbool h){useHack = h;}
#endif

void GFX::setFullscreen(CRbool fs){fullscreen = fs;}

Colour GFX::getClearColour(){return clear;}

// Force to blit to screen now!
void GFX::forceBlit()
{
    renderPixelBuffer();
    #ifdef PLATFORM_GP2X
        //  We do MMUHack BEFORE video flip!
        if(useHack)
            MMUHack::flushCache(screen->pixels, (char*)screen->pixels  + (screen->w * screen->h));
    #elif PLATFORM_PANDORA
        //  vertical sync to prevent tearing
        int fd = open( "/dev/fb0" , O_RDONLY );
		if( 0 < fd )
		{
			int ret = 0;
			ret = ioctl(fd, FBIO_WAITFORVSYNC, &ret );
			/*if ( ret != 0 )
                VSYNC failed
			*/
		}
		close(fd);
    #endif
    #ifdef PENJIN_GL
        SDL_GL_SwapBuffers();
    #elif PENJIN_SDL
        #ifdef PENJIN_SCALE2X
            scale2x(screen,scaled);
            SDL_Flip(scaled);
        #else
            SDL_Flip(screen);
        #endif
    #elif PENJIN_CACA
        /// TODO: Pass display pointer into GFX or create here instead.
        caca_refresh_display(display);
    #endif
    #if defined (PENJIN_ES) || defined (PENJIN_ES2)
        eglSwapBuffers(eglDisplay,eglSurface);
    #endif
}

void GFX::renderPixelBuffer()
{
    if(!pixBuff.empty())
    {
        #if defined (PENJIN_GL) || defined (PENJIN_ES)
            glEnable(GL_BLEND);
            //  Setup vertex pointers
            glEnableClientState(GL_VERTEX_ARRAY);
            #ifdef PENJIN_3D
                glVertexPointer(3, GL_FLOAT, sizeof(ColourVertex), &pixBuff.front().vertex);
            #else
                glVertexPointer(2, GL_FLOAT, sizeof(ColourVertex), &pixBuff.front().vertex);
            #endif
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(4, GL_FLOAT, sizeof(ColourVertex), &pixBuff.front().colour);
                glDrawArrays(GL_POINTS,0,pixBuff.size());
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
            glDisable(GL_BLEND);
        #elif PENJIN_SDL
            SDL_Surface* pixel = SDL_CreateRGBSurface(SDL_SWSURFACE, 1, 1, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);
            for(uint i=0; i < pixBuff.size(); ++i )
            {
                ColourVertex v = pixBuff.at(i);
                //  Blend if necesary
                SDL_SetAlpha(pixel, SDL_SRCALPHA|SDL_RLEACCEL,v.colour.w);
                //  Set the colour
                setPixel(pixel,v.vertex.x,v.vertex.y,Colour(v.colour.x,v.colour.y,v.colour.z,v.colour.w));
                SDL_Rect d;
                d.x = v.vertex.x;
                d.y = v.vertex.y;
                SDL_BlitSurface(pixel, NULL, screen, &d);
            }
            SDL_FreeSurface(pixel);
        #endif
        // After rendering all pixels we should clear out the buffer :P
        pixBuff.clear();
    }

}

void GFX::showCursor(CRbool show)
{
    #if defined (PENJIN_SDL) || defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        if(show)
            SDL_ShowCursor(SDL_ENABLE);
        else
            SDL_ShowCursor(SDL_DISABLE);
    #endif
}

void GFX::setPixel(CRint x, CRint y, const Colour& colour)
{
    ColourVertex v;
    v.vertex.x = x;
    v.vertex.y = y;
    v.colour.x = colour.red;
    v.colour.y = colour.green;
    v.colour.z = colour.blue;
    v.colour.w = colour.alpha;
    pixBuff.push_back(v);
}

void GFX::setResolution(uint x,uint y)
{
    xRes = x;
    yRes = y;
    #if defined(PLATFORM_PANDORA) && (defined(PENJIN_ES) || defined(PENJIN_ES2))
    if(x == 0 || y == 0)
    {
        xRes = 800;
        yRes = 480;
    }
    #endif
}

void GFX::setResolution()
{
    // set an automatic(best fit?) resolution.
    setResolution(0,0);
}

void GFX::setBPP(uint b)
{
    //  0 is automatic
    bpp = b;
}

PenjinErrors::PENJIN_ERRORS GFX::resetScreen()
{
#if defined(PENJIN_SDL) || defined(PENJIN_GL) || defined (PENJIN_SOFT)
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
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
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
    #if defined (PLATFORM_GP2X) || defined (PLATFORM_PANDORA)
        flags = SDL_SWSURFACE | SDL_DOUBLEBUF;
    #else
        flags = SDL_SWSURFACE;
    #endif
#endif
#if defined(PENJIN_SDL) || defined(PENJIN_GL) || defined(PENJIN_SOFT)
    if(fullscreen)
        flags = flags | SDL_FULLSCREEN;
    if(bpp == 0 || !(bpp == 8 || bpp == 16 || bpp == 32))
        bpp = info->vfmt->BitsPerPixel;
    #if defined PENJIN_SDL && PENJIN_SCALE2X
        scaled  = SDL_SetVideoMode(2*xRes, 2*yRes, bpp, flags);
        if(scaled  == NULL )
            return PENJIN_SDL_SETVIDEOMODE_FAILED;

        if (scaled == NULL)
        {
            cerr << "Error creating surface: " << SDL_GetError() << endl;
            exit(1);
        }

        screen = SDL_CreateRGBSurface(SDL_SWSURFACE, xRes, yRes, bpp,
        scaled->format->Rmask, scaled->format->Gmask, scaled->format->Bmask, scaled->format->Amask);
        if (screen == NULL)
        {
            cerr << "Error creating surface: " << SDL_GetError() << endl;
            exit(1);
        }
    #else
        screen = SDL_SetVideoMode(xRes, yRes, bpp, flags);
        if(screen  == NULL )
            return PENJIN_SDL_SETVIDEOMODE_FAILED;
        else
        {
            xRes = screen->w;
            yRes = screen->h;
        }
    #endif
    #if defined (PENJIN_GL) || defined(PENJIN_ES) || defined(PENJIN_ES2)
        glEnable(GL_CULL_FACE); // don't render the back of polygons...
    #endif
#endif
#if defined PENJIN_ES || defined (PENJIN_ES2)
    Window                      sRootWindow;
    XSetWindowAttributes        sWA;
        unsigned int            ui32Mask;
        int                     i32Depth;

        // Initializes the display and screen
        x11Display = XOpenDisplay(":0");
        if (!x11Display)
        {
            printf("Error: Unable to open X display\n");
            //goto cleanup;
        }
        x11Screen = XDefaultScreen( x11Display );

        // Gets the window parameters
        sRootWindow = RootWindow(x11Display, x11Screen);
        i32Depth = DefaultDepth(x11Display, x11Screen);
        x11Visual = new XVisualInfo;
        XMatchVisualInfo( x11Display, x11Screen, i32Depth, TrueColor, x11Visual);
        if (!x11Visual)
        {
            printf("Error: Unable to acquire visual\n");
            //goto cleanup;
        }
    x11Colormap = XCreateColormap( x11Display, sRootWindow, x11Visual->visual, AllocNone );
    sWA.colormap = x11Colormap;

    // Add to these for handling other events
    sWA.event_mask = StructureNotifyMask | ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask;
    ui32Mask = CWBackPixel | CWBorderPixel | CWEventMask | CWColormap;

        // Creates the X11 window
    x11Window = XCreateWindow( x11Display, RootWindow(x11Display, x11Screen), 0, 0, xRes, yRes,
                0, CopyFromParent, InputOutput, CopyFromParent, ui32Mask, &sWA);

    XMapWindow(x11Display, x11Window);
    XFlush(x11Display);

    // Make it fullscreen
    if(fullscreen)
    {
		// Make the window fullscreen
		unsigned char fullScreen = 1;
		Atom wmState = XInternAtom(x11Display, "_NET_WM_STATE", False);
		Atom wmFullScreen = XInternAtom(x11Display,"_NET_WM_STATE_FULLSCREEN", False);

		XEvent xev;
		xev.xclient.type		= ClientMessage;
		xev.xclient.serial		= 0;
		xev.xclient.send_event		= True;
		xev.xclient.window		= x11Window;
		xev.xclient.message_type	= wmState;
		xev.xclient.format		= 32;
		xev.xclient.data.l[0]		= (fullScreen ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE);
		xev.xclient.data.l[1]		= wmFullScreen;
		xev.xclient.data.l[2]		= 0;

		XSendEvent(x11Display, DefaultRootWindow(x11Display), False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
    }


    eglDisplay = eglGetDisplay((EGLNativeDisplayType)x11Display);
    if(eglDisplay == EGL_NO_DISPLAY)
        return PENJIN_EGL_NO_DISPLAY;
    EGLint iMajorVersion, iMinorVersion;
    if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
    {
            return PENJIN_EGL_INIT_FAILED;
    }
    eglBindAPI(EGL_OPENGL_ES_API);

    EGLint attributes[] =
    {
        EGL_BUFFER_SIZE, 16,
        EGL_RED_SIZE, 5,
        EGL_GREEN_SIZE, 6,
        EGL_BLUE_SIZE, 5,
        EGL_ALPHA_SIZE, 0,
        EGL_DEPTH_SIZE, EGL_DONT_CARE,
        EGL_STENCIL_SIZE, EGL_DONT_CARE,
        EGL_CONFIG_CAVEAT, EGL_NONE,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    #ifdef PENJIN_ES
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
    #elif PENJIN_ES2
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    #endif
        EGL_NONE
    };
    EGLint numConfigs;
    if(!eglChooseConfig(eglDisplay,attributes, &eglConfig, 1, &numConfigs))
        return PENJIN_EGL_INIT_FAILED;
    const EGLint contextAttribs[] =
    {
        #ifdef PENJIN_ES
        EGL_CONTEXT_CLIENT_VERSION, 1,
        #elif PENJIN_ES2
        EGL_CONTEXT_CLIENT_VERSION, 2,
        #endif
        EGL_NONE
    };
    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
    if(eglContext == EGL_NO_CONTEXT)
        return PENJIN_EGL_NO_CONTEXT;
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)x11Window, NULL);
    eglMakeCurrent(eglDisplay,eglSurface,eglSurface,eglContext);
#endif
#ifdef PENJIN_3D
    init3DRendering();
#else
    #if defined PENJIN_GL || defined PENJIN_ES || defined PENJIN_ES2
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
#if defined(PENJIN_SDL) || defined(PENJIN_GL) || defined(PENJIN_SOFT)
SDL_Surface* GFX::getVideoSurface()
{
    if(screen == NULL)
        screen = SDL_GetVideoSurface();
    return screen;
}
#endif
#ifdef PENJIN_SDL
    #ifdef PENJIN_SCALE2X
        #ifndef MAX
        #define MAX(a,b)    (((a) > (b)) ? (a) : (b))
        #define MIN(a,b)    (((a) < (b)) ? (a) : (b))
        #endif


        #define READINT24(x)      ((x)[0]<<16 | (x)[1]<<8 | (x)[2])
        #define WRITEINT24(x, i)  {(x)[0]=i>>16; (x)[1]=(i>>8)&0xff; x[2]=i&0xff; }
        void GFX::scale2x(SDL_Surface* src, SDL_Surface* dst)
        {
            int looph, loopw;

            Uint8* srcpix = (Uint8*)src->pixels;
            Uint8* dstpix = (Uint8*)dst->pixels;

            const int srcpitch = src->pitch;
            const int dstpitch = dst->pitch;
            const int width = src->w;
            const int height = src->h;

            switch(src->format->BytesPerPixel)
            {
            case 1: {
                    Uint8 E0, E1, E2, E3, B, D, E, F, H;
                for(looph = 0; looph < height; ++looph)
                {
                    for(loopw = 0; loopw < width; ++ loopw)
                    {
                            B = *(Uint8*)(srcpix + (MAX(0,looph-1)*srcpitch) + (1*loopw));
                            D = *(Uint8*)(srcpix + (looph*srcpitch) + (1*MAX(0,loopw-1)));
                            E = *(Uint8*)(srcpix + (looph*srcpitch) + (1*loopw));
                            F = *(Uint8*)(srcpix + (looph*srcpitch) + (1*MIN(width-1,loopw+1)));
                            H = *(Uint8*)(srcpix + (MIN(height-1,looph+1)*srcpitch) + (1*loopw));

                        E0 = D == B && B != F && D != H ? D : E;
                                        E1 = B == F && B != D && F != H ? F : E;
                        E2 = D == H && D != B && H != F ? D : E;
                        E3 = H == F && D != H && B != F ? F : E;

                        *(Uint8*)(dstpix + looph*2*dstpitch + loopw*2*1) = E0;
                        *(Uint8*)(dstpix + looph*2*dstpitch + (loopw*2+1)*1) = E1;
                        *(Uint8*)(dstpix + (looph*2+1)*dstpitch + loopw*2*1) = E2;
                        *(Uint8*)(dstpix + (looph*2+1)*dstpitch + (loopw*2+1)*1) = E3;
                    }
                }break;}
            case 2: {
                    Uint16 E0, E1, E2, E3, B, D, E, F, H;
                for(looph = 0; looph < height; ++looph)
                {
                    for(loopw = 0; loopw < width; ++ loopw)
                    {
                            B = *(Uint16*)(srcpix + (MAX(0,looph-1)*srcpitch) + (2*loopw));
                            D = *(Uint16*)(srcpix + (looph*srcpitch) + (2*MAX(0,loopw-1)));
                            E = *(Uint16*)(srcpix + (looph*srcpitch) + (2*loopw));
                            F = *(Uint16*)(srcpix + (looph*srcpitch) + (2*MIN(width-1,loopw+1)));
                            H = *(Uint16*)(srcpix + (MIN(height-1,looph+1)*srcpitch) + (2*loopw));

                        E0 = D == B && B != F && D != H ? D : E;
                                        E1 = B == F && B != D && F != H ? F : E;
                        E2 = D == H && D != B && H != F ? D : E;
                        E3 = H == F && D != H && B != F ? F : E;

                        *(Uint16*)(dstpix + looph*2*dstpitch + loopw*2*2) = E0;
                        *(Uint16*)(dstpix + looph*2*dstpitch + (loopw*2+1)*2) = E1;
                        *(Uint16*)(dstpix + (looph*2+1)*dstpitch + loopw*2*2) = E2;
                        *(Uint16*)(dstpix + (looph*2+1)*dstpitch + (loopw*2+1)*2) = E3;
                    }
                }break;}
            case 3: {
                    int E0, E1, E2, E3, B, D, E, F, H;
                for(looph = 0; looph < height; ++looph)
                {
                    for(loopw = 0; loopw < width; ++ loopw)
                    {
                            B = READINT24(srcpix + (MAX(0,looph-1)*srcpitch) + (3*loopw));
                            D = READINT24(srcpix + (looph*srcpitch) + (3*MAX(0,loopw-1)));
                            E = READINT24(srcpix + (looph*srcpitch) + (3*loopw));
                            F = READINT24(srcpix + (looph*srcpitch) + (3*MIN(width-1,loopw+1)));
                            H = READINT24(srcpix + (MIN(height-1,looph+1)*srcpitch) + (3*loopw));

                        E0 = D == B && B != F && D != H ? D : E;
                                        E1 = B == F && B != D && F != H ? F : E;
                        E2 = D == H && D != B && H != F ? D : E;
                        E3 = H == F && D != H && B != F ? F : E;

                        WRITEINT24((dstpix + looph*2*dstpitch + loopw*2*3), E0);
                        WRITEINT24((dstpix + looph*2*dstpitch + (loopw*2+1)*3), E1);
                        WRITEINT24((dstpix + (looph*2+1)*dstpitch + loopw*2*3), E2);
                        WRITEINT24((dstpix + (looph*2+1)*dstpitch + (loopw*2+1)*3), E3);
                    }
                }break;}
            default: { /*case 4:*/
                    Uint32 E0, E1, E2, E3, B, D, E, F, H;
                for(looph = 0; looph < height; ++looph)
                {
                    for(loopw = 0; loopw < width; ++ loopw)
                    {
                            B = *(Uint32*)(srcpix + (MAX(0,looph-1)*srcpitch) + (4*loopw));
                            D = *(Uint32*)(srcpix + (looph*srcpitch) + (4*MAX(0,loopw-1)));
                            E = *(Uint32*)(srcpix + (looph*srcpitch) + (4*loopw));
                            F = *(Uint32*)(srcpix + (looph*srcpitch) + (4*MIN(width-1,loopw+1)));
                            H = *(Uint32*)(srcpix + (MIN(height-1,looph+1)*srcpitch) + (4*loopw));

                        E0 = D == B && B != F && D != H ? D : E;
                                        E1 = B == F && B != D && F != H ? F : E;
                        E2 = D == H && D != B && H != F ? D : E;
                        E3 = H == F && D != H && B != F ? F : E;

                        *(Uint32*)(dstpix + looph*2*dstpitch + loopw*2*4) = E0;
                        *(Uint32*)(dstpix + looph*2*dstpitch + (loopw*2+1)*4) = E1;
                        *(Uint32*)(dstpix + (looph*2+1)*dstpitch + loopw*2*4) = E2;
                        *(Uint32*)(dstpix + (looph*2+1)*dstpitch + (loopw*2+1)*4) = E3;
                    }
                }break;}
            }
        }
    #endif
    void GFX::setClearColour(const Colour& c){clear = c;}
    void GFX::borderColouring(CRint x,CRint y,CRint w,CRint h,CRint thick,Colour baseColour){borderColouring(screen,x,y,w,h,thick,baseColour);}
    void GFX::borderColouring(SDL_Surface* screen,CRint x,CRint y,CRint w,CRint h,CRint thick,Colour baseColour)
    {
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
                        setPixel(screen,i,j,baseColour);
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
                    setPixel(screen,i,j,baseColour);
                }
            }
        }
    }
    void GFX::renderStatic(CRint xStart,CRint yStart,CRint w,CRint h,CRint spacing, CRint thickness){renderStatic(screen,xStart,yStart,w,h,spacing,thickness);}
    void GFX::renderStatic(SDL_Surface* screen,CRint x,CRint y,CRint w,CRint h,CRint spacing, CRint thick)
    {
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
                        setPixel(screen,i,j,BLACK);
                    else if(colour == 1)
                        setPixel(screen,i,j,Colour(64,64,64));
                    else if(colour == 2)
                        setPixel(screen,i,j,Colour(128,128,128));
                    else if(colour == 3)
                        setPixel(screen,i,j,Colour(196,196,196));
                    else if(colour == 4)
                        setPixel(screen,i,j,WHITE);
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
                            setPixel(screen,i,j,BLACK);
                        else if(colour == 1)
                            setPixel(screen,i,j,Colour(64,64,64));
                        else if(colour == 2)
                            setPixel(screen,i,j,Colour(128,128,128));
                        else if(colour == 3)
                            setPixel(screen,i,j,Colour(196,196,196));
                        else if(colour == 4)
                            setPixel(screen,i,j,WHITE);
                    }
                }
            }
        }
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
#elif PENJIN_GL || defined (PENJIN_ES) || defined (PENJIN_ES2)
    Colour GFX::getPixel(CRint x, CRint y)
    {
        cout << ErrorHandler().getErrorString(PenjinErrors::PENJIN_FUNCTION_IS_STUB) << " GFX::getPixel(CRint x, CRint y)"<< endl;
        return MAGENTA;
    }
    void GFX::setClearColour(const Colour& c){glClearColor(c.red,c.green,c.blue,c.alpha);}
    void GFX::init2DRendering()
    {
        // Setup OpenGL
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glShadeModel(GL_SMOOTH);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        //Setup viewport
        glViewport(0, 0, xRes, yRes);

        //Setup world view
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        #ifdef PENJIN_GL
        glOrtho(0, xRes, yRes, 0, 0, 1);
        #else
        glOrthof(0, xRes, yRes, 0, 0, 1);
        #endif

        //glMatrixMode(GL_TEXTURE);
        //glRotated(90,0,0,1);
        //glLoadIdentity();
        //Setup modelview matrix
        glMatrixMode( GL_MODELVIEW );
        //glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glColor4f(1.0f,1.0f,1.0f,1.0f);
        //glCullFace(GL_FRONT);   // we have inverted the Y to mic drawing like SDL so we have to cull the front face
    }

    void GFX::clearScreen()
    {
        glClear(GL_COLOR_BUFFER_BIT
            #ifdef PENJIN_3D
                | GL_DEPTH_BUFFER_BIT
            #endif
        );
        glLoadIdentity();
    }
    #ifdef PENJIN_3D
        void GFX::init3DRendering()
        {
            //  Depth testing setup
            //glClearDepth(1);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc( GL_LEQUAL );

            //  default lighting setup
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_COLOR_MATERIAL);
            //  blending
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            // shading
            glShadeModel(GL_SMOOTH);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

            //  window size
            glViewport(0, 0, xRes, yRes);
            //glLoadIdentity();
            //  align textures
            glMatrixMode(GL_TEXTURE);
            glRotatef(180,0,0,1);
            glRotatef(180,0,1,0);
            //  setup perspective
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            perspective(60.0f,(float)xRes/(float)yRes, 1.0f, 1000.0f);

            //Setup model view
            glMatrixMode( GL_MODELVIEW );
            glLoadIdentity();
            glColor4f(1.0f,1.0f,1.0f,1.0f);
        }
    #endif
#endif

void GFX::showVideoInfo()
{
    #if defined (PENJIN_GL) || defined (PENJIN_SDL)
        screen = getVideoSurface();
        if(!screen)
        {
            cout << "Problem getting VideoInfo - screen is NULL." << endl;
            return;
        }
        cout << "Screen Info" << endl;
        cout << screen->w << "x" << screen->h << " " << StringUtility::intToString(screen->format->BitsPerPixel) << "BPP" << endl;
        #ifdef PENJIN_SCALE2X
        cout << "Scale2X Active." << endl;
        #endif
    #endif
    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined(PENJIN_ES2)
        printf("GL Info\n");
        printf("Vendor:     %s\n",glGetString(GL_VENDOR));
        printf("Renderer:   %s\n",glGetString(GL_RENDERER));
        printf("Version:    %s\n",glGetString(GL_VERSION));
        printf("Extensions: %s\n",glGetString(GL_EXTENSIONS));
        #if defined (PENJIN_GL) || defined (PENJIN_ES2)
        printf("GLSL: %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));
        #endif
        #ifdef PENJIN_GL
            cout << endl;
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
#if defined (PENJIN_GL) || defined (PENJIN_SOFT) || defined (PENJIN_ES) || defined (PENJIN_ES2)
    #ifdef PENJIN_3D
        void GFX::perspective(CRfloat fov,CRfloat aspect,CRfloat znear,CRfloat zfar)
        {
            float range = znear*tan(NumberUtility::degToRad(fov*0.5f));
            #ifdef PENJIN_ES
                glFrustumf(-range*aspect,range*aspect,-range,range,znear,zfar);
            #elif PENJIN_ES2
                glFrustumf(-range*aspect,range*aspect,-range,range,znear,zfar);
            #else
                glFrustum(-range*aspect,range*aspect,-range,range,znear,zfar);
            #endif
        }
    #endif
#endif
#if defined(PENJIN_ES) || defined(PENJIN_ES2) || defined(PENJIN_SCALE2X)
void GFX::shutdown()
{
    #ifdef PENJIN_SCALE2X
        SDL_FreeSurface(scaled);
    #else
        eglMakeCurrent( eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
        eglDestroyContext ( eglDisplay, eglContext );
        eglDestroySurface ( eglDisplay, eglSurface );
        eglTerminate ( eglDisplay );
        if (x11Window) XDestroyWindow(x11Display, x11Window);
        if (x11Colormap) XFreeColormap( x11Display, x11Colormap );
        if (x11Display) XCloseDisplay(x11Display);
    #endif
}
#endif

