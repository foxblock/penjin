#ifndef GLYPH_H
#define GLYPH_H

#include "Image.h"
#include <SDL/SDL_ttf.h>
#include "PenjinTypes.h"
#include "Colour.h"
#include <ctype.h>

namespace GlyphClass
{
    enum RENDER_MODES
    {
        QUICK,  //  fast with colourkey
        BOXED,  //  antialiased against bg box.
        NICE    //  anitaliased fully with alpha channel SLOW
    };
}
using namespace GlyphClass;
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
        #ifdef PENJIN_3D
            void setPosition(Vector3df* p){position = p;}
        #else
            void setPosition(Vector2di* p){position = p;}
        #endif
        void setRenderMode(RENDER_MODES m){renderMode = m;}
        void setCharacter(CRchar c){character = c;}
        void setColour(const Colour& c){colour = c;}
        void setBgColour(const Colour& c){bgColour = c;}
        void setFontSize(CRuint s){fontSize = s;}

        Colour getColour()const{return colour;}
        Colour getBgColour()const{return bgColour;}
        uint getFontSize()const{return fontSize;}
        char getCharacter()const{return character;}
        uint getWidth()const{return glyph.getWidth();}      //  return character width
        uint getHeight()const{return glyph.getHeight();}    //  return chracter height.
        RENDER_MODES getRenderMode()const{return renderMode;}

    private:
        // Disabled to prevent double freed pointers.
        Glyph(const Glyph& noCopy);
        Glyph& operator=(const Glyph& noCopy);

        #ifdef PENJIN_SDL
            Image glyph;
        #else
            Texture glyph;
        #endif
        //  We can check the below params to see if glyph needs to be recreated.
        char character;
        uint fontSize;
        Colour colour;
        Colour  bgColour;
        TTF_Font* font;
        GlyphClass::RENDER_MODES renderMode;
        //  This is just a position we move around
        #ifdef PENJIN_3D
            Vector3df* position;
        #else
            Vector2di* position;
        #endif
};

#endif // GLYPH_H
