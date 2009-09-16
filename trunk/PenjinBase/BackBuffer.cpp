#include "BackBuffer.h"

BackBuffer::BackBuffer()
{
    //ctor
    #ifdef PENJIN_SDL
        buffer = NULL;
        screen = SDL_GetVideoSurface();
    #else
        glClear(GL_ACCUM_BUFFER_BIT);
        alpha = 1.0f;
    #endif
}

BackBuffer::~BackBuffer()
{
    //dtor
    #ifdef PENJIN_SDL
        if(buffer)
            SDL_FreeSurface(buffer);
        buffer = NULL;
    #endif
}

#ifdef PENJIN_SDL
    void BackBuffer::render(SDL_Surface* scr)
    {
        SDL_BlitSurface(buffer, NULL, scr, NULL);
    }

    void BackBuffer::update(SDL_Surface* scr)
    {
        if(buffer == NULL)
            buffer = SDL_CreateRGBSurface(screen->flags,scr->w, scr->h, screen->format->BitsPerPixel, 0, 0, 0, 0);
        SDL_BlitSurface(scr, NULL, buffer, NULL);
    }
#else
    void BackBuffer::render()
    {
        glAccum(GL_MULT, alpha);
        glAccum(GL_ACCUM, 1.0f-alpha);
        glAccum(GL_RETURN, 1.0f);
    }
#endif
