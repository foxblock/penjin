#include "Text.h"

Text::Text()
{
	font = NULL;
	position.x = 0;
	position.y = 0;
	startPos.x = 0;
	startPos.y = 0;
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
        clipBoundary.w = 320;
        clipBoundary.h = 240;
        #ifdef PENJIN_SDL
            screen = SDL_GetVideoSurface();
        #endif
	#endif
    clipBoundary.x = 0;
    clipBoundary.y = 0;
    IsInitialised = false;
    centreText = false;
}

int Text::initialise()
{
    int result = TTF_Init();
    if(result != 0)
    {
        IsInitialised = false;
        result = PENJIN_ERROR;
    }
    else
    {
        IsInitialised = true;
        result = PENJIN_OK;
    }
    return result;
}

void Text::deInitialise()
{
    TTF_Quit();
    IsInitialised = false;
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
}

PENJIN_ERRORS Text::loadFont(CRstring fontName,CRuint fontSize)
{
	clear();
	font = TTF_OpenFont(fontName.c_str(), fontSize);
	if(font)
		return PENJIN_OK;
	return PENJIN_TTF_UNABLE_TO_OPEN;
}

#ifdef PENJIN_SDL
    void Text::print(SDL_Surface* screen, CRstring text)
    {
        if(!text.size())
            return;

        print(screen,(char*)text.c_str());
    }

    void Text::print(SDL_Surface* screen, char* text)
    {
        const char* t = text;
        print(screen,t);
    }

    /// TODO: Fix newlines with \n symbol.
    void Text::print(const char* text){print(screen,text);}
    void Text::print(CRstring text){print(screen,text);}
    void Text::print(char* text){print(screen,text);}
    void Text::print(SDL_Surface* screen,const char* text)
    {
        if(centreText)
            centralise();
        uint CRcount = countCRs((string)text);
        if(CRcount) //  if we spand several lines
        {
            string tString;
            tString = stripCRs((string)text).c_str();
            SDL_Surface* textSurface =  TTF_RenderText_Blended(font, tString.c_str(), colour.getSDL_Colour());
            #ifdef PENJIN_FIXED
                SDL_Rect textLocation = {fixedpoint::fix2int(position.x), fixedpoint::fix2int(position.y), 0, 0 };
            #else
                SDL_Rect textLocation = { position.x, position.y, 0, 0 };
            #endif
            SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
            dimensions.y = textSurface->h;
            dimensions.x = textSurface->w;
            /// The cursor position depends on the previous word's ending position
            if(relativePos)
            {
                if(position.x + textSurface->w > clipBoundary.w)   //  Text wrapping onto newline
                    newLine(textSurface);
                else if(CRcount)                        //  forced newline by /n
                    for(int i=CRcount-1; i >= 0; --i)
                        newLine(textSurface);
                else
                    position.x += textSurface->w;       //  text added after last word
            }
            SDL_FreeSurface(textSurface);
        }
        else
        {
            SDL_Surface* textSurface =  TTF_RenderText_Blended(font, text, colour.getSDL_Colour());
            #ifdef PENJIN_FIXED
                SDL_Rect textLocation = {fixedpoint::fix2int(position.x), fixedpoint::fix2int(position.y), 0, 0 };
            #else
                SDL_Rect textLocation = { position.x, position.y, 0, 0 };
            #endif
            SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
            dimensions.y = textSurface->h;
            dimensions.x = textSurface->w;
            if(relativePos)
            {
                if(position.x + textSurface->w > clipBoundary.w)
                    newLine(textSurface);
                else
                    position.x += textSurface->w;
            }
            SDL_FreeSurface(textSurface);
        }
    }
#else
    void Text::print(CRstring text)
    {
        if(!text.size())
            return;
        print(text.c_str());
    }
    void Text::print(char* text)
    {
        const char* t = text;
        print(t);
    }

    void Text::print(const char* text)
    {
        uint CRcount = countCRs((string)text);
        if(CRcount) //  if we spand several lines
        {
            string tString;
            tString = stripCRs((string)text).c_str();
            SDL_Surface* textSurface = NULL;
            textSurface =  TTF_RenderText_Blended(font, tString.c_str(), colour.getSDL_Colour());

             //  Convert the surface to a texture if the text is different from last render.
            if(text != lastPrint.c_str())
            {
                lastPrint = text;
                dimensions.y = textSurface->h;
                dimensions.x = textSurface->w;
                texture.loadSurface(textSurface);

            }

            //  With the surface now converted to a texture we can render it to a quad
            glColor4f(1.0f, 1.0f, 1.0f, colour.alpha);
            glBindTexture (GL_TEXTURE_2D, texture.getTextureID());
            glEnable(GL_TEXTURE_2D);
            glBegin(GL_QUADS);
                glTexCoord2f (0.0f, 0.0f);
                #ifdef PENJIN3D
                    glVertex3f(position.x, position.y, position.z);
                #else
                    glVertex2f(position.x,position.y);
                #endif
                glTexCoord2f (1.0f, 0.0f);
                #ifdef PENJIN3D
                    glVertex3f(position.x + texture.getWidth(), position.y, position.z);
                #else
                    glVertex2f(position.x + texture.getWidth(), position.y);
                #endif
                glTexCoord2f (1.0f,  1.0f);
                #ifdef PENJIN3D
                    glVertex3f(position.x + texture.getWidth(), position.y + texture.getHeight(), position.z);
                #else
                    glVertex2f(position.x + texture.getWidth(), position.y + texture.getHeight());
                #endif
                glTexCoord2f (0.0f, 1.0f);
                #ifdef PENJIN3D
                    glVertex3f(position.x, position.y + texture.getHeight(), position.z);
                #else
                    glVertex2f(position.x, position.y + texture.getHeight());
                #endif
            glEnd();
            glDisable(GL_TEXTURE_2D);


            /// The cursor position depends on the previous word's ending position
            if(relativePos)
            {
                if(position.x + dimensions.y > clipBoundary.w)   //  Text wrapping onto newline
                    newLine(textSurface);
                else if(CRcount)                        //  forced newline by /n
                    for(int i=CRcount-1; i >= 0; --i)
                        newLine(textSurface);
                else
                    position.x += dimensions.x;       //  text added after last word
            }
            if(textSurface)
                SDL_FreeSurface(textSurface);
        }
        else
        {
            SDL_Surface* textSurface = NULL;
            textSurface =  TTF_RenderText_Blended(font, text, colour.getSDL_Colour());

             //  Convert the surface to a texture if the text is different from last render.
            if(text != lastPrint.c_str())
            {
                dimensions.y = textSurface->h;
                dimensions.x = textSurface->w;
                texture.loadSurface(textSurface);
            }
            if(relativePos)
            {
                if(position.x + textSurface->w > clipBoundary.w)
                    newLine(textSurface);
                else
                    position.x += textSurface->w;
            }
            glColor3f(1.0f, 1.0f, 1.0f);
            glBindTexture (GL_TEXTURE_2D, texture.getTextureID());
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
                glEnable(GL_TEXTURE_2D);
                    glBegin(GL_QUADS);
                        glTexCoord2f (0.0f, 0.0f);
                        #ifdef PENJIN3D
                            glVertex3f(position.x, position.y, position.z);
                        #else
                            glVertex2f(position.x,position.y);
                        #endif
                        glTexCoord2f (1.0f, 0.0f);
                        #ifdef PENJIN3D
                            glVertex3f(position.x + texture.getRawWidth(), position.y, position.z);
                        #else
                            glVertex2f(position.x + texture.getRawWidth(), position.y);
                        #endif
                        glTexCoord2f (1.0f,  1.0f);
                        #ifdef PENJIN3D
                            glVertex3f(position.x + texture.getRawWidth(),position.y + texture.getRawHeight(), position.z);
                        #else
                            glVertex2f(position.x + texture.getRawWidth(),position.y + texture.getRawHeight());
                        #endif
                        glTexCoord2f (0.0f, 1.0f);
                        #ifdef PENJIN3D
                            glVertex3f(position.x, position.y + texture.getRawHeight(), position.z);
                        #else
                            glVertex2f(position.x, position.y + texture.getRawHeight());
                        #endif
                    glEnd();
                glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
        }
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

uint Text::countCRs(CRstring line)
{
	uint CRcount = 0;
	//	run through the string
	for(int i = line.size()-1; i >= 0; --i)
	{
		//	check for CR and increase CRcount if found
		if(line[i] == '\n')
			++CRcount;
	}
	return CRcount;
}

string Text::stripCRs(string line)
{
	for(int i = line.size()-1; i >= 0; --i)
		if(line[i] == '\n')
			line[i] = 0;

	return line;
}

void Text::newLine(SDL_Surface* textSurface)
{
    position.x =  startPos.x;
    position.y += textSurface->h;
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
