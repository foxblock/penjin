/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef TEXT_H
#define TEXT_H
#if defined(PENJIN_SDL) || defined(PENJIN_GL) || defined(PENJIN_SOFT) || defined(PENJIN_ES) || defined(PENJIN_ES2)
    #include "Glyph.h"
#endif
#include <string>
#include "DoubleVector.h"
#include <ctype.h>
#ifdef PLATFORM_WII
    #include "Penjin.h"
#endif
using namespace std;
#include "PenjinTypes.h"
#include "Colour.h"
#include "PenjinErrors.h"
using namespace PenjinErrors;


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
        // Sets the starting position of the text
        // If a bounding box has been set by a call to setBoundary, this sets the
        // top-left corner position and text will be aligned in that bounding box.
        // Else it will be aligned to this position
        template <class T>
        void setPosition(const T& pos){position.x = pos.x;position.y = pos.y;startPos = position;}

        #ifndef PENJIN_3D
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

		// Wrap text if it exceeds the horizontal boundary. Will try to wrap text
		// nicely on space and - first, will wrap on any char if that is not possible
		// The boundary is defined by a call to setBoundary.
		// If no boundary has been defined the borders of the screen will break the text
        void setWrapping(CRbool shouldWrap){wrapText = shouldWrap;}
        bool getWrapping()const{return wrapText;}
        void setAlignment(const ALIGNMENT& align){alignment = align;}
        ALIGNMENT getAlignment()const{return alignment;}
        void setStyle(CRint style){TTF_SetFontStyle(font, style);}
        int getStyle()const{return TTF_GetFontStyle(font);}
        bool isMonoSpaced()const{return TTF_FontFaceIsFixedWidth(font);}
        void setRenderMode(const GlyphClass::RENDER_MODES& m);
        GlyphClass::RENDER_MODES getRenderMode()const;
        // Get dimensions of the text from the last print call
        Vector2di getDimensions()const{return dimensions;}
        Vector2di getDimensions(CRstring str);
        int getWidth()const{return dimensions.x;}
        int getHeight()const{return dimensions.y;}
        #ifndef PENJIN_3D
            Vector2df getStartPosition()const{return startPos;}
            Vector2df getPosition()const{return position;}

        #else
            Vector3df getStartPosition()const{return startPos;}
            Vector3df getPosition()const{return position;}
        #endif
		// Keep the position in between multiple print calls
        void setRelativity(CRbool rel){relativePos = rel;}

        ///	You must have used the above functions in order to use the following print functions
        void print(char* text);		//	write a char* string to the screen
        void print(const char* text);
        void print(CRstring text);       //	write a string to the screen
        //	write an integer to the screen
        void print(CRint number);
        //	write a float number to the screen
        void print(CRfloat number);
        #ifdef PENJIN_SDL
            void print(SDL_Surface* screen, char* text);		//	write a char* string to the screen
            void print(SDL_Surface* screen, const char* text);
            void print(SDL_Surface* screen, CRstring text);       //	write a string to the screen
            //	write an integer to the screen
            void print(SDL_Surface* scr, CRint number);
            //	write a float number to the screen
            void print(SDL_Surface* scr, CRfloat number);
        #endif
        string getLastText() {return lastText;}

        void clear();

		// Set the size of the boundary
		// The boundary affects text alignment and text wrapping (see those functions for more details).
		// If none has been set or it has been set to a non-positive number, the
		// borders of the screen will define text wrapping and position will be used for alignment
        void setBoundary(const Vector2di& bound)
        {
            clipBoundary.x = bound.x;
            clipBoundary.y = bound.y;
        }
        void setBoundary(CRint width, CRint height)
        {
        	clipBoundary.x = width;
        	clipBoundary.y = height;
        }
        // Kept for backwards compatibility
        void setUpBoundary(const Vector2di& bound)
        {
        	setBoundary(bound);
        }
        void setUpBoundary(CRint width, CRint height)
        {
        	setBoundary(width, height);
        }
        void setBoundaries(const Vector2di& lowBound,const Vector2di& hiBound)
        {
            setBoundary(hiBound);
            setPosition(lowBound);
        }
        void setBoundaries(SDL_Rect bounds)
        {
        	setPosition(bounds.x, bounds.y);
        	setBoundary(bounds.w, bounds.h);
        }

        void clearGlyphs();
    private:
        void align(const Vector2di& dims);
        void calcDimensions();
        void newLine();
        TTF_Font* font;
        string fontName;
        uint fontSize;
        #ifndef PENJIN_3D
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
        DoubleVector<Glyph*> glyphs;  //  stores each individual charactor for printing. [FONT_SIZE][CHARACTER]

        bool relativePos;
        bool wrapText;
        ALIGNMENT alignment;
        Colour colour;
        Colour bgColour;
        Vector2di clipBoundary; // The size of the area that the Text is allowed to exist within (also used for position with right aligned or centred text)
        string lastText;
};

#endif	//	TEXT_H

