#include "Glyph.h"

Glyph::Glyph()
{
    //ctor
    fontSize = 0;       // no font.
    position = NULL;
    character = '\0';
}

Glyph::~Glyph()
{
    //dtor
}


#ifdef PENJIN_SDL
void Glyph::render(SDL_Surface* scr)
{
    /*
    if(glyph.size() && position != NULL)
    {
        glyph.renderImage(scr,*position);
    }
    else if((character != '\0') && fontSize > 0)  //  if there is a character to render, render it.
    {
        refresh();
        render(scr);
    }
    */
    glyph.renderImage(scr,*position);
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
    else if((character != '\n') && fontSize > 0)  //  if there is a character to render, render it.
        refresh();
}
