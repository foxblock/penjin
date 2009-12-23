#ifndef TEXT_H
#define TEXT_H

/// TODO:  Finish glyph creation.
#include "Glyph.h"
#include <string>
#include "DoubleVector.h"
#include <ctype.h>
#ifdef PLATFORM_WII
    #include "Penjin.h"
#endif
using namespace std;
#include "PenjinTypes.h"
#include "Colour.h"
#include "StringUtility.h"
#include "NumberUtility.h"
#include "PenjinErrors.h"
using namespace PenjinErrors;
using namespace StringUtility;

///Text will wrap after 58 characters, inc spaces and punctuation. (at size 12 pt) (on a GP2X screen, 320x240)
///The text below shows how many characters can be used before the text will wrap.
////////////////////////////////////////////////////////////////////////////////////
///text.print(screen, "To be or not to be, that is the question Whether tis noble");

namespace TextClass
{
    enum ALIGNMENT
    {
        LEFT_JUSTIFIED,
        CENTRED,
        RIGHT_JUSTIFIED
    };

        PENJIN_ERRORS init();                          //  Must be called once before any Text objects are used.
        void deInit();                        //  Must be called once before program termination.
        bool isInitialised();
}

using namespace TextClass;

class Text
{
    public:
        Text();		//	Initialise font handling
        ~Text();	//	Shutdown font handling

        PENJIN_ERRORS loadFont(CRstring fontName,CRuint fontSize);		//	Loads a TTF
        PENJIN_ERRORS loadFont(CRstring fontName);  // Load a TTF without changing size

        PENJIN_ERRORS setFontSize(CRuint s);
        uint getFontSize()const{return fontSize;}
        //  Sets the starting position of the text
        template <class T>
        void setPosition(const T& pos){position.x = pos.x;position.y = pos.y;startPos = position;}

        #ifndef PENJIN3D

            void setPosition(CRfloat x,CRfloat y);						//	Sets the starting position of the text
        #else
            #ifdef PENJIN_FIXED
                //void setPosition(const Vector3dx& position){this->position = position;}
                //void setPosition(const Vector2dx& position){this->position.x = position.x;this->position.y = position.y;this->position.z = 0.0f;}
                void setPosition(CRFixed x,CRFixed y){setPosition(Vector2dx(x,y));}
                void setPosition(CRFixed x,CRFixed y,CRFixed z);
            #else
                //void setPosition(const Vector3df& position){this->position = position;}
                //void setPosition(const Vector2df& position){this->position.x = position.x;this->position.y = position.y;this->position.z = 0.0f;}
                void setPosition(CRfloat x,CRfloat y){setPosition(Vector3df(x,y,0.0f));}
                void setPosition(CRfloat x,CRfloat y,CRfloat z);
            #endif
        #endif
        //	Sets the font colour
        void setColour(const Colour& colour){this->colour = colour;}
        void setColour(const uchar& red,const uchar& green,const uchar& blue);		//	Sets the font colour
        Colour getColour()const{return colour;}
        void setBgColour(const Colour& col){bgColour = col;setRenderMode(GlyphClass::BOXED);}
        Colour getBgColour()const{return bgColour;}

        void setAlignment(const ALIGNMENT& align){alignment = align;}
        ALIGNMENT getAlignment()const{return alignment;}
        void setStyle(CRint style){TTF_SetFontStyle(font, style);}
        int getStyle()const{return TTF_GetFontStyle(font);}
        bool isMonoSpaced()const{return TTF_FontFaceIsFixedWidth(font);}
        void setRenderMode(const GlyphClass::RENDER_MODES& m){glyphs[fontSize-1][0]->setRenderMode(m);}
        GlyphClass::RENDER_MODES getRenderMode()const{return glyphs[fontSize-1][0]->getRenderMode();}

        #ifndef PENJIN3D
            Vector2df getStartPosition()const{return startPos;}
            Vector2df getPosition()const{return position;}
            Vector2di getDimensions()const{return dimensions;}
            Vector2di getDimensions(CRstring str);
        #else
            Vector3df getStartPosition()const{return startPos;}
            Vector3df getPosition()const{return position;}
            Vector3df getDimensions()const{return dimensions;}
            Vector3df getDimensions(CRstring str);
        #endif
        int getWidth()const{return dimensions.x;}
        int getHeight()const{return dimensions.y;}

        void setRelativity(CRbool rel){relativePos = rel;}
        //void setCentreText(CRbool centre){centreText = centre;} /// WARNING needs some work!

        ///	You must have used the above functions in order to use the following print functions
        void print(char* text);		//	write a char* string to the screen
        void print(const char* text);
        void print(CRstring text);       //	write a string to the screen
        //	write an integer to the screen
        void print(CRint number){print(StringUtility::intToString(number));}
        //	write a float number to the screen
        void print(CRfloat number){print(StringUtility::floatToString(number));}
        #ifdef PENJIN_SDL
            void print(SDL_Surface* screen, char* text);		//	write a char* string to the screen
            void print(SDL_Surface* screen, const char* text);
            void print(SDL_Surface* screen, CRstring text);       //	write a string to the screen
            //	write an integer to the screen
            void print(SDL_Surface* scr, CRint number){print(scr,intToString(number));}
            //	write a float number to the screen
            void print(SDL_Surface* scr, CRfloat number){print(scr,floatToString(number));}
        #endif

        void clear();

        void setUpBoundary(const Vector2di& bound)
        {
            clipBoundary.w = bound.x;
            clipBoundary.h = bound.y;
        }
        void setDownBoundary(const Vector2di& bound)
        {
            clipBoundary.x = bound.x;
            clipBoundary.y = bound.y;
        }
        void setBoundaries(const Vector2di& lowBound,const Vector2di& hiBound)
        {
            setUpBoundary(hiBound);
            setDownBoundary(lowBound);
        }
        void setBoundaries(const SDL_Rect& boundaries){clipBoundary = boundaries;}

        void clearGlyphs();
    private:
        void align(const Vector2di& dims);
        void calcDimensions();
        void newLine();
        TTF_Font* font;
        string fontName;
        uint fontSize;
        #ifndef PENJIN3D
            Vector2di position;
            Vector2di startPos;
            Vector2di dimensions;
        #else
            Vector3df position;
            Vector3df startPos;
            Vector3df dimensions;
        #endif
        #ifdef PENJIN_SDL
            SDL_Surface* screen;
        #endif
        DoubleVector<Glyph*> glyphs;  //  stores each individual charactor for printing.

        bool relativePos;
        ALIGNMENT alignment;
        Colour colour;
        Colour bgColour;
        SDL_Rect clipBoundary;      //  The area that the particle is allowed to exist within
};

#endif	//	TEXT_H

