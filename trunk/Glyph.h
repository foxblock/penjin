#ifndef GLYPH_H
#define GLYPH_H

#include "Image.h"
#include <SDL/SDL_ttf.h>
#include "PenjinTypes.h"
#include "Colour.h"
#include <ctype.h>
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
        uint getWidth()const{return glyph.getWidth();}      //  return character width
        uint getHeight()const{return glyph.getHeight();}    //  return chracter height.

    private:
        // Disabled to prevent double freed pointers.
        Glyph(const Glyph& noCopy);
        Glyph& operator=(const Glyph& noCopy);

        Image glyph;

        //  We can check the below params to see if glyph needs to be recreated.
        char character;
        uint fontSize;
        Colour colour;
        TTF_Font* font;

        //  This is just a position we move around
        Vector2di* position;
};

#endif // GLYPH_H
