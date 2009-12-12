#include "Glyph.h"

Glyph::Glyph()
{
    //ctor
    fontSize = 0;       // no font.
}

Glyph::~Glyph()
{
    //dtor
}


#ifdef PENJIN_SDL
void Glyph::render(SDL_Surface* scr)
{
    if(glyph.size())
    {
        glyph.renderImage(scr,*position);
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
        if(glyph.size())
            glyph.clear();
        glyph.loadImage( TTF_RenderText_Blended(font, &character, colour.getSDL_Colour()) );
    #endif
}

void Glyph::render()
{
    if(glyph.size())
    {
        glyph.renderImage(*position);
    }
    else if((character != NULL) && fontSize > 0)  //  if there is a character to render, render it.
        refresh();
}
