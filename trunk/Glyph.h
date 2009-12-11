#ifndef GLYPH_H
#define GLYPH_H

#include <SDL/SDL.h>
#ifdef PENJIN_GL
    #include <SDL/SDL_opengl.h>
    #include <SDL/SDL_ttf.h>
    #include "Texture.h"
#else
    #include <SDL/SDL_ttf.h>
#endif
#include "PenjinTypes.h"
#include "Colour.h"
class Glyph
{
    public:
        Glyph();
        ~Glyph();

        void render();
        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);
        #endif
        void refresh(); //  Updates the glyph

        void setFont(TTF_Font* f){font = f;}            //  Set the pointer to the loaded Font object
        void setPosition(Vector2di* p){position = p;}
        void setCharacter(CRchar c){character = c;}
        void setColour(const Colour& c){colour = c;}
        void setFontSize(CRuint s){fontSize = s;}

        Colour getColour()const{return colour;}
        uint getFontSize()const{return fontSize;}
        char getCharacter()const{return character;}

    private:
        // Disabled to revent double freed pointers.
        Glyph(const Glyph& noCopy);
        Glyph& operator=(const Glyph& noCopy);

        #ifdef PENJIN_SDL
            SDL_Surface* glyph;
            SDL_Surface* screen;
        #else
            Texture glyph;
        #endif
        //  We can check the below params to see if glyph needs to be recreated.
        char character;
        uint fontSize;
        Colour colour;
        TTF_Font* font;

        //  This is just a position we move around
        Vector2di* position;
};

#endif // GLYPH_H
