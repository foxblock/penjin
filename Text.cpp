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
#include "Text.h"
#ifdef PENJIN_ASCII
    #ifdef _WIN32
        #include "Wincon.h"
    #elif _LINUX
        #include <ncurses.h>
    #endif
#endif
#include "StringUtility.h"
#include "NumberUtility.h"
using namespace StringUtility;
PENJIN_ERRORS TextClass::init()
{
    if(isInitialised())
        return PENJIN_OK;
    int result = TTF_Init();
    if(result != 0)
    {
        result = PENJIN_ERROR;
    }
    else
    {
        result = PENJIN_OK;
    }
    return (PENJIN_ERRORS)result;
}

bool TextClass::isInitialised(){return TTF_WasInit();}

void TextClass::deInit()
{
    if(isInitialised())
        TTF_Quit();
}

Text::Text()
{
    TextClass::init();// auto init font library if needed.
	font = NULL;
	fontName = "NULL";
	fontSize = 12;  // default to 12 point font
	position.x = 0;
	position.y = 0;
	startPos.x = 0;
	startPos.y = 0;
	dimensions.x = dimensions.y = 0;
	clipBoundary.x = 0;
	clipBoundary.y = 0;
	#ifdef PENJIN_3D
        #ifdef PENJIN_FIXED
			position.z = startPos.z = 0;
        #else
            position.z = startPos.z = 0.0f;
        #endif
    #else
        #ifdef PENJIN_SDL
            screen = GFX::getVideoSurface();
        #endif
	#endif
    alignment = LEFT_JUSTIFIED;
    bgColour = BLACK;
    relativePos = false;
    wrapText = false;
    lastText = "";
}

void Text::clear()
{
	if(font)
    {
        //  Sleep to try and allow any text rendering to finish...
        #ifndef PENJIN_SYS_TIMER
            SDL_Delay(1);
        #else
            sleep(1);
        #endif
        TTF_CloseFont(font);			// Release the font object
        font = NULL;
    }
}

void Text::clearGlyphs()
{
    //  run through all sizes of chars
    for(int i = glyphs.size()-1; i >=0; --i)
    {
        for(int j = glyphs[i].size()-1; j>=0; --j)
        {
            delete glyphs[i][j];
            glyphs[i][j] = NULL;
        }
    }
}

Text::~Text()
{
    // close font
	clear();
	// clear Glyphs
	clearGlyphs();
}

PENJIN_ERRORS Text::loadFont(CRstring name,CRuint fontSize)
{
    //  check if fontSize is not the same as loaded font
    if(this->fontSize != fontSize || name != fontName)
    {
        clear();
        #ifdef PLATFORM_WII
            font = TTF_OpenFont((Penjin::getWorkingDirectory() + name).c_str(), fontSize);
        #else
            font = TTF_OpenFont(name.c_str(), fontSize);
        #endif
    }
	if(font)
	{
		// TODO: Implement kerning for glyphs
		#if defined(TTF_SetFontKerning)
		TTF_SetFontKerning(font, 0);
		#endif
	    // check if we already have Glyphs for this fontSize
	    if(glyphs.size() >= fontSize)
	    {
	        if(glyphs.at(fontSize-1).size())
	        {
                // if the fontSize checks out...
                if(glyphs.at(fontSize-1)[0]->getFontSize() == fontSize)
                {
                    this->fontSize = fontSize;
                    return PENJIN_OK;
                }
	        }
	    }
        else
        {
            //Setup enough glyphs for fontSize
            glyphs.resize(fontSize);
        }
        //  create Dummy Char for spacing calcs
        glyphs[fontSize-1].push_back(NULL);
        glyphs[fontSize-1][0] = new Glyph();
        glyphs[fontSize-1][0]->setFontSize(fontSize);
        glyphs[fontSize-1][0]->setFont(font);
        glyphs[fontSize-1][0]->setCharacter('-');    // picked because a nice square char to give us a "standard surface width"
        glyphs[fontSize-1][0]->setPosition(&position);
        glyphs[fontSize-1][0]->refresh();
        fontName = name;
        this->fontSize = fontSize;
        // At this point we can already calculate the height of a single line
		dimensions.y = TTF_FontLineSkip(font);
		return PENJIN_OK;
	}
	return PENJIN_TTF_UNABLE_TO_OPEN;
}

PENJIN_ERRORS Text::loadFont(CRstring name)
{
    return loadFont(name,fontSize);
}

PENJIN_ERRORS Text::setFontSize(CRuint s)
{
    return loadFont(fontName, s);
}

void Text::setRenderMode(const GlyphClass::RENDER_MODES& mode)
{
    if (glyphs.size())
    {
        if(glyphs.size(fontSize-1))
            glyphs.at(fontSize-1,0)->setRenderMode(mode);
        else
            cout << "No Glyphs - Can't set RenderMode" << mode << endl;
    }
    else
        cout << "No Glyphs - Can't set RenderMode" << mode << endl;
}

void Text::print(SDL_Surface* screen, CRstring text)
{
	//  no text, no render
	if (!text.size())
		return;

	// make text advance cursor position
	if (!relativePos)
		position = startPos;
	Vector2di guess;
	TTF_SizeText(font, text.c_str(), &guess.x, &guess.y );
	if (alignment != LEFT_JUSTIFIED)
	{
		align(guess);
	}
	Vector2di topLeft(position.x, position.y);
	Vector2di bottomRight(-1,-1);
	//  Run through the text chars
	for (uint i = 0; i < text.size(); ++i)
	{
		uchar c = text[i];
		// check for NULL terminator
		if (c == '\0')
		{
			break;
		}
		//  check for newLine
		else if (c == '\n')
		{
			bottomRight.x = max(bottomRight.x, position.x);
			topLeft.x = min(topLeft.x, startPos.x);
			newLine();
			continue;
		}
		// check for space char
		else if (c == ' ')
		{
			//  use dummy for spacing
			position.x += glyphs[fontSize-1][0]->getWidth();
			// we get a substring that is from here to the end of the string.
			if (wrapText)
			{
				if (i+1<text.size())
				{
					string subString = text.substr(i+1);
					// we search this substring for the next space
					uint x = 0;
					for (x = 0; x < subString.size(); ++x)
					{
						if(subString[x] == ' ' || subString[x] == '-') // characters at which we break the line
							break;
					}
					subString = subString.substr(0,x);
					TTF_SizeText(font, subString.c_str(), &guess.x, &guess.y );
				}
				// Wrapping can be calculated no matter how text is aligned
				if ((clipBoundary.x > 0 && position.x + guess.x >= startPos.x + clipBoundary.x)
						|| (clipBoundary.x <= 0 && position.x + guess.x >= GFX::getXResolution()))
				{
					bottomRight.x = max(bottomRight.x, position.x);
					topLeft.x = min(topLeft.x, startPos.x);
					newLine();
				}
				continue;
			}
			else
				continue;
		}
		//  check for tab
		else if(c == '\t')
		{
			//  use dummy for spacing
			position.x += glyphs[fontSize-1][0]->getWidth()*3;
			continue;
		}
		// check for other unprintables
		else if(!isprint(c))
		{
			continue;
		}

		//  create more (empty) glyphs as needed - shifted 19 indices
		int start = glyphs[fontSize-1].size();
		for (int I = start; I <= c-19; ++I)
		{
			Glyph* temp = new Glyph;
			temp->setFont(font);
			temp->setCharacter(I+19);
			temp->setFontSize(fontSize);
			glyphs[fontSize-1].push_back(temp);
		}

		Glyph* current = glyphs[fontSize-1].at(c-19);

		// check properties of glyph if they differ from what we want to render.
		// init/fill glyph image, if glyph was just created
		current->setPosition(&position);
		current->update(colour,bgColour,glyphs[fontSize-1].front()->getRenderMode());

		// Forced wrapping (text does not fit screen and does not wrap nicely at next space)
		if (wrapText)
		{
			if ((clipBoundary.x > 0 && position.x + current->getWidth() >= startPos.x + clipBoundary.x)
					|| (clipBoundary.x <= 0 && position.x + current->getWidth() >= GFX::getXResolution()))
			{
				bottomRight.x = max(bottomRight.x, position.x);
				topLeft.x = min(topLeft.x, startPos.x);
				newLine();
				current->setPosition(&position);
			}
		}

		//  if everything up to date we can render the glyph
		current->render(screen);
		//  Advance cursor
		position.x += current->getWidth();
	}
	bottomRight.x = max(bottomRight.x, position.x);
	bottomRight.y = position.y + TTF_FontLineSkip(font);
	dimensions = bottomRight - topLeft;
	lastText = text;
}

void Text::print(SDL_Surface* screen, char* text)
{
	string t = text;
	print(screen,t);
}

/// TODO: Fix newlines with \n symbol.
void Text::print(const char* text){print(screen,text);}
void Text::print(CRstring text){print(screen,text);}
void Text::print(char* text){print(screen,text);}
void Text::print(SDL_Surface* screen,const char* text)
{
	string t = text;
	print( screen,t);
}
	//	write an integer to the screen
void Text::print(SDL_Surface* scr, CRint number){print(scr,intToString(number));}
//	write a float number to the screen
void Text::print(SDL_Surface* scr, CRfloat number){print(scr,floatToString(number));}
		//	write an integer to the screen
void Text::print(CRint number){print(screen,number);}
//	write a float number to the screen
void Text::print(CRfloat number){print(screen,number);}

#ifndef PENJIN_3D
    void Text::setPosition(CRfloat x, CRfloat y)
    {
        position.x = startPos.x = x;
        position.y = startPos.y = y;
    }
#else
    #ifdef PENJIN_FIXED
        void Text::setPosition(CRFixed x,CRFixed y,CRFixed z)
    #else
        void Text::setPosition(CRfloat x,CRfloat y,CRfloat z)
    #endif
    {
        position.x = startPos.x = x;
        position.y = startPos.y = y;
        position.z = startPos.z = z;
    }
#endif

void Text::setColour(const uchar& red,const uchar& green,const uchar& blue)
{
	colour.red = red;
	colour.green = green;
	colour.blue = blue;
}

void Text::newLine()
{
    position.x = startPos.x;
    position.y += TTF_FontLineSkip(font);
}

void Text::align(const Vector2di& guess)
{
    if(alignment == CENTRED)
    {
		position.x += (clipBoundary.x - guess.x) / 2.0f;
    }
    else if(alignment == RIGHT_JUSTIFIED)
    {
    	if (position.x != startPos.x)
		{
			// This happens when relativity is true and the last print operation did not end in a new line
			// In this case we try to align to last printed text
			// (We cannot do this on centred text, since it would not be properly centred then)
			position.x -= dimensions.x + guess.x;
		}
		else
			position.x += clipBoundary.x - guess.x;
    }
    // Otherwise text is LEFT_JUSTIFIED so do nothing.
}

Vector2di Text::getDimensions(CRstring str)
{
    Vector2di guess;
    TTF_SizeText(font, str.c_str(), &guess.x, &guess.y );
    return guess;
}
