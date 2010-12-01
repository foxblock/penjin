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
#include "Texture.h"
#if defined (PENJIN_GL) || defined(PENJIN_ES) || defined(PENJIN_ES2)
Texture::Texture()
{
	init();
}

Texture::Texture(CRstring fileName)
{
    init();
	loadTexture(fileName);
}

void Texture::init()
{
    loaded = false;
    dimensions.x = dimensions.y = -1;
    colourKey = MAGENTA;
}

Texture::~Texture()
{
	if(loaded)
		glDeleteTextures( 1, &textureID);
    loaded = false;
}

PENJIN_ERRORS Texture::loadSurface(SDL_Surface* surface)
{
    if(loaded)
		glDeleteTextures(1, &textureID);
    loaded = false;

    if(surface == NULL)
		return PENJIN_TEXTURE_CONVERSION_ERROR;

    //  Store dimensions of original RAW surface
    dimensions.x = rawDimensions.x = surface->w;
    dimensions.y = rawDimensions.y = surface->h;

	//  Check if surface is PoT
    if(!isPoT(surface->w))
        rawDimensions.x = NumberUtility::nextPowerOfTwo(surface->w);
    if(!isPoT(surface->h))
        rawDimensions.y = NumberUtility::nextPowerOfTwo(surface->h);

    //  work out texture coords
    txCoords.x = (float)dimensions.x/(float)rawDimensions.x;
    txCoords.y = (float)dimensions.y/(float)rawDimensions.y;

    colourKey.alpha = 0;
    SDL_Surface* intermediary = NULL;
    GLenum textureFormat = NULL;

    intermediary = SDL_CreateRGBSurface(SDL_SWSURFACE, rawDimensions.x, rawDimensions.y, 32,
    #if SDL_BYTEORDER == SDL_LIL_ENDIAN // OpenGL RGBA masks
        0x000000FF,
        0x0000FF00,
        0x00FF0000,
        0xFF000000
    #else
        0xFF000000,
        0x00FF0000,
        0x0000FF00,
        0x000000FF
    #endif
);

    //  check if original image uses an alpha channel
    if(!(surface->flags & SDL_SRCALPHA))
    {
        // if no alpha use MAGENTA and key it out.
        colourKey = MAGENTA;
        colourKey.alpha = 1.0f;
        SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surface->format,colourKey.red*255,colourKey.green*255,colourKey.blue*255));
    }
    else
        SDL_SetAlpha(surface, 0, 0);
    SDL_BlitSurface(surface, 0 , intermediary, 0);
    //int numColours = intermediary->format->BytesPerPixel;
    //  We convert all formats to RGBA it makes life simpler!
    textureFormat = GL_RGBA;//getTextureFormat(intermediary);

    glPixelStorei(GL_UNPACK_ALIGNMENT, textureFormat);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    #ifdef PENJIN_3D
        //gluBuild2DMipmaps(GL_TEXTURE_2D, textureFormat,intermediary->w, intermediary->h, textureFormat, GL_UNSIGNED_BYTE, intermediary->pixels);
        glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, intermediary->w, intermediary->h, 0, textureFormat, GL_UNSIGNED_BYTE, intermediary->pixels);
    #else
        glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, intermediary->w, intermediary->h, 0, textureFormat, GL_UNSIGNED_BYTE, intermediary->pixels);
    #endif
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if(surface)
    {
    SDL_FreeSurface(surface);
    surface = NULL;
    }
  	if(intermediary)
  	{
      SDL_FreeSurface(intermediary);
      intermediary = NULL;
  	}

	loaded = true;
	return PENJIN_OK;
}

PENJIN_ERRORS Texture::loadTexture(CRstring fileName)
{
	SDL_Surface* surface = NULL;
	surface = IMG_Load(fileName.c_str());
	return loadSurface(surface);
}

GLenum Texture::getTextureFormat(SDL_Surface* surface)
{
    int numColours = surface->format->BytesPerPixel;

    if (numColours == 4)
    {
        if (surface->format->Rmask == 0x000000ff)
            return GL_RGBA;
        #ifdef PENJIN_GL
        else
            return GL_BGRA;
        #endif
    }
    else if (numColours == 3)
    {
        if (surface->format->Rmask == 0x000000ff)
            return GL_RGB;
        #ifdef PENJIN_GL
        else
            return GL_BGR;
        #endif
        }

//  TODO in image is palleted, convert to a truecolour surface
//    else if (numColours == 2)
//    {
//    }
//    else if (numColours == 1)
//    {
//    }

    // invalid surface format HACK return RGBA
    return GL_RGBA;
}
#endif

