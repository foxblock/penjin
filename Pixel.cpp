#include "Pixel.h"

Pixel::Pixel()
{
    position.x = position.y = -1;
    init();
    setPixel();
}

void Pixel::init()
{
#ifdef PENJIN_SDL
    pixel = NULL;
    pixel = SDL_CreateRGBSurface(SDL_SWSURFACE, 1, 1, SDL_GetVideoSurface()->format->BitsPerPixel, NULL, NULL, NULL, NULL);
    screen = SDL_GetVideoSurface();
#endif
}

void Pixel::setColour(const Colour& c)
{
    colour.setColour(c);
    setPixel();
}

void Pixel::setColour(CRuchar r, CRuchar g, CRuchar b, CRuchar a)
{
    colour.setColour(r,g,b,a);
    SDL_SetAlpha(pixel, SDL_SRCALPHA|SDL_RLEACCEL, colour.alpha);
    setPixel();
}

void Pixel::setColour(CRuchar r, CRuchar g, CRuchar b)
{
    colour.setColour(r,g,b);
    SDL_SetAlpha(pixel, SDL_SRCALPHA|SDL_RLEACCEL, 255);
    setPixel();
}

void Pixel::setPixel()
{
    GFX::setPixel(pixel,0,0,colour);
}

Pixel::~Pixel()
{
    //dtor
#ifdef PENJIN_SDL
    if(pixel)
        SDL_FreeSurface(pixel);
    pixel = NULL;
#endif
}

#ifdef PENJIN_SDL
    void Pixel::render(SDL_Surface* scr)
    {
        SDL_Rect d;
        d.x = position.x;
        d.y = position.y;
        SDL_BlitSurface(pixel, NULL, scr, &d);
    }
#else
    void Pixel::render()
    {

    }
#endif
