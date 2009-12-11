#include "Glyph.h"

Glyph::Glyph()
{
    //ctor
    fontSize = 0;       // no font.
    #ifdef PENJIN_SDL
        glyph = NULL;
        screen = SDL_GetVideoSurface();
    #endif
}

Glyph::~Glyph()
{
    //dtor
    #ifdef PENJIN_SDL
        if(glyph)
            SDL_FreeSurface(glyph);
        glyph = NULL;
    #endif
}


#ifdef PENJIN_SDL
void Glyph::render(SDL_Surface* scr)
{
    if(glyph)
    {
        SDL_Rect textPos = { position->x, position->y, 0, 0 };
        SDL_BlitSurface(glyph, NULL, scr,&textPos);
    }
    else if((character != NULL) && fontSize > 0)  //  if there is a character to render, render it.
        refresh();
}
#endif

void Glyph::refresh()
{
    #ifdef PENJIN_SDL
        if(position == NULL)        //  No cursor position is invalid usage.
            return;
        if(glyph)
            SDL_FreeSurface(glyph);
        glyph = NULL;
        glyph = TTF_RenderText_Blended(font, &character, colour.getSDL_Colour());
    #endif
}

void Glyph::render()
{
    #ifdef PENJIN_SDL
        render(screen);
    #elif PENJIN_GL

    #endif
}
