#include "Text.h"

Text::Text()
{
    initialise();   // auto init font library if needed.
	font = NULL;
	fontSize = 0;
	position.x = 0;
	position.y = 0;
	startPos.x = 0;
	startPos.y = 0;
	dimensions.x = dimensions.y = 0;
	#ifdef PENJIN3D
        #ifdef PENJIN_FIXED
                position.z = startPos.z = 0;
        #else
            position.z = startPos.z = 0.0f;
        #endif
        clipBoundary.w = 1024;
        clipBoundary.h = 768;
        lastPrint = "NULL";
    #else
        #ifdef PENJIN_SDL
            screen = SDL_GetVideoSurface();
            clipBoundary.w = screen->w;
            clipBoundary.h = screen->h;
        #endif
	#endif
    centreText = false;
    relativePos = false;
}

PENJIN_ERRORS Text::initialise()
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

void Text::deInitialise()
{
    if(isInitialised())
        TTF_Quit();
}

void Text::clear()
{
	if(font)
    {
        TTF_CloseFont(font);			// Release the font object
        font = NULL;
    }
    #ifdef PENJIN3D
        lastPrint = "NULL";
    #endif
}

Text::~Text()
{
	clear();
//
    for(int i = glyphs.size()-1; i >=0; --i)
    {
        delete glyphs[i];
        glyphs[i] = NULL;
    }
}

PENJIN_ERRORS Text::loadFont(CRstring fontName,CRuint fontSize)
{
	clear();
	font = TTF_OpenFont(fontName.c_str(), fontSize);
	if(font)
	{
	    this->fontSize = fontSize;
        //  create Dummy Char for spacing calcs
        glyphs.push_back(NULL);
        glyphs[glyphs.size()-1] = new Glyph();
        glyphs[0]->setFontSize(fontSize);
        glyphs[0]->setFont(font);
        glyphs[0]->setCharacter('-');    // picked because a nice square char to give us a "standard surface width"
        glyphs[0]->setPosition(&position);
        glyphs[0]->refresh();
		return PENJIN_OK;
	}
	return PENJIN_TTF_UNABLE_TO_OPEN;
}

#ifdef PENJIN_SDL
    void Text::print(SDL_Surface* screen, CRstring text)
    {
        //  no text, no render
        if(!text.size())
            return;

        // make text advance cursor position
        if(!relativePos)
            position = startPos;
        //  Check if any of the string has had to be recreated
        bool isRefreshed = false;
        // make a guess to dimensions using the Dummy char
        Vector2di guess;
        TTF_SizeText(font, text.c_str(), &guess.x, &guess.y );
        if(position.x + guess.x >= clipBoundary.w)
            newLine();
        if(centreText)
        {
            Vector2df b(clipBoundary.w,clipBoundary.h);
            b-= (position + guess);
            b*=0.5f;
            //position.x = startPos.x;
            position.x += b.x;
        }
        //  Run through the text chars
        for(int i = 0; i < text.size(); ++i)
        {
            char c = text[i];
            // check for NULL terminator
            if(c == '\0')
            {
                break;
            }
            //  check for newLine
            else if(c == '\n')
            {
                newLine();
                continue;
            }
            // check for space char
            else if(c == ' ')
            {
                //  use dummy for spacing
                position.x+=glyphs[0]->getWidth();
                continue;
            }
            // check for other unprintables
            else if(!isprint(c))
            {
                continue;
            }

            //  create more glyphs as needed
            while(glyphs.size() <= c)
            {
                glyphs.push_back(NULL);
                glyphs[glyphs.size()-1] = new Glyph();
            }

            //  check properties of glyph if they differ from what we want to render.
            bool changed = false;
            if(glyphs.at(c)->getColour() != colour)
            {
                glyphs.at(c)->setColour(colour);
                changed = true;
            }
            if(glyphs.at(c)->getFontSize() != fontSize)
            {
                glyphs.at(c)->setFontSize(fontSize);
                changed = true;
            }
            if(glyphs.at(c)->getCharacter() != c)
            {
                glyphs.at(c)->setCharacter(c);
                changed = true;
            }
            if(glyphs.at(c)->getRenderMode() != glyphs.front()->getRenderMode())
            {
                glyphs.at(c)->setRenderMode(glyphs.front()->getRenderMode());
                changed = true;
            }
            //  set common glyph properties
            glyphs.at(c)->setFont(font);
            glyphs.at(c)->setPosition(&position);
            if(changed)
            {
                glyphs.at(c)->refresh();
                isRefreshed = true;
            }

            //  if everything up to date we can render the glyph
            glyphs.at(c)->render(screen);
            //  Advance cursor
            position.x += glyphs.at(c)->getWidth();
        }
        if(isRefreshed)
            calcDimensions();
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
#else
    void Text::print(CRstring text)
    {
        //  no text, no render
        if(!text.size())
            return;

        // make text advance cursor position
        if(!relativePos)
            position = startPos;
        //  Check if any of the string has had to be recreated
        bool isRefreshed = false;
        // make a guess to dimensions using the Dummy char
        Vector2di guess;
        TTF_SizeText(font, text.c_str(), &guess.x, &guess.y );
        if(position.x + guess.x >= clipBoundary.w)
            newLine();
        if(centreText)
        {
            Vector2df b(clipBoundary.w,clipBoundary.h);
            b-= (position + guess);
            b*=0.5f;
            //position.x = startPos.x;
            position.x += b.x;
        }
        //  Run through the text chars
        for(int i = 0; i < text.size(); ++i)
        {
            char c = text[i];
            // check for NULL terminator
            if(c == '\0')
            {
                break;
            }
            //  check for newLine
            else if(c == '\n')
            {
                newLine();
                continue;
            }
            // check for space char
            else if(c == ' ')
            {
                //  use dummy for spacing
                position.x+=glyphs[0]->getWidth();
                continue;
            }
            // check for other unprintables
            else if(!isprint(c))
            {
                continue;
            }

            //  create more glyphs as needed
            while(glyphs.size() <= c)
            {
                glyphs.push_back(NULL);
                glyphs[glyphs.size()-1] = new Glyph();
            }

            //  check properties of glyph if they differ from what we want to render.
            bool changed = false;
            if(glyphs.at(c)->getColour() != colour)
            {
                glyphs.at(c)->setColour(colour);
                changed = true;
            }
            if(glyphs.at(c)->getFontSize() != fontSize)
            {
                glyphs.at(c)->setFontSize(fontSize);
                changed = true;
            }
            if(glyphs.at(c)->getCharacter() != c)
            {
                glyphs.at(c)->setCharacter(c);
                changed = true;
            }
            if(glyphs.at(c)->getRenderMode() != glyphs.front()->getRenderMode())
            {
                glyphs.at(c)->setRenderMode(glyphs.front()->getRenderMode());
                changed = true;
            }
            //  set common glyph properties
            glyphs.at(c)->setFont(font);
            glyphs.at(c)->setPosition(&position);
            if(changed)
            {
                glyphs.at(c)->refresh();
                isRefreshed = true;
            }

            //  if everything up to date we can render the glyph
            glyphs.at(c)->render();
            //  Advance cursor
            position.x += glyphs.at(c)->getWidth();
        }
        if(isRefreshed)
            calcDimensions();
    }
    void Text::print(char* text)
    {
        string t = text;
        print(t);
    }

    void Text::print(const char* text)
    {
        string t = text;
        print(t);
    }
#endif
#ifndef PENJIN3D
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
    position.x =  startPos.x;
    position.y += TTF_FontLineSkip(font);
}

void Text::centralise()
{
    #ifndef PENJIN3D
        Vector2df b(clipBoundary.w,clipBoundary.h);
        b-= (position + dimensions);
        b*=0.5f;
        //position.x = startPos.x;
        position.x += b.x;
    #else
        Vector3df b = Vector3df(clipBoundary.w,clipBoundary.h,0);
        b-= (position + dimensions);
        b*=0.5f;
        //position.x = startPos.x;
        position.x += b.x;
    #endif
}

void Text::calcDimensions()
{
    dimensions.x = position.x - startPos.x + glyphs[0]->getWidth();
    dimensions.y = TTF_FontLineSkip(font);
}

Vector2di Text::getDimensions(CRstring str)
{
    Vector2di guess;
    TTF_SizeText(font, str.c_str(), &guess.x, &guess.y );
    return guess;
}
