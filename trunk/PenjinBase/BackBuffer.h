#ifndef BACKBUFFER_H
#define BACKBUFFER_H
#include "GFX.h"
#include "Pixel.h"

class BackBuffer
{
    public:
        BackBuffer();
        #ifdef PENJIN_SDL
            BackBuffer(SDL_Surface* src);   //  create backbuffer from src surface
        #endif
        ~BackBuffer();

        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);    // Render to specific surface
            void render(){render(screen);}       // Render to the screen
            void update(SDL_Surface* screen);    // Update from specific surface
            void update(){update(screen);}       // Update from screen contents
            void setAlpha(CRuchar alpha){SDL_SetAlpha(buffer, SDL_SRCALPHA, alpha);}
            void setPixel(Pixel p){p.render(buffer);}
        #else
            void render();
            void update(){;}
            void setAlpha(CRuchar a){alpha = a * 0.003921569f;}
            void setAlpah(CRfloat a){alpha = a;}
        #endif



    private:
        #ifdef PENJIN_SDL
            SDL_Surface* buffer;    //  The back buffer
            SDL_Surface* screen;    //  The pointer to the screen.
        #else
            float alpha;
        #endif
};

#endif // BACKBUFFER_H
