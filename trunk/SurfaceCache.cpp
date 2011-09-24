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
#include "SurfaceCache.h"

#include <iostream>

SurfaceCache* SurfaceCache::self = NULL;

SurfaceCache::SurfaceCache()
{
    returnErrorSurface = true;
    verbose = true;
    errorSurface = createErrorSurface(64,64);
}

SurfaceCache::~SurfaceCache()
{
    clear();
    SDL_FreeSurface(errorSurface);
}

//--- public -------------------------------------------------------------------

SurfaceCache* SurfaceCache::getSurfaceCache()
{
	if (not self)
        self = new SurfaceCache();
	return self;
}

SDL_Surface* SurfaceCache::loadSurface(const std::string &filename, const bool &optimize)
{
    std::map<std::string, CachedSurface>::iterator iter;

    iter = cache.find(filename);
    if (iter == cache.end())
    {
        // Surface was not found, let's create it
        if (verbose)
            std::cout << "Loading new image to cache \"" << filename << "\"" << std::endl;
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if(not surface)
        {
            if (verbose)
            {
                std::cout << "Error loading \"" << filename << "\"" << std::endl;
                std::cout << "The error was: " << IMG_GetError() << std::endl;
            }
            if (returnErrorSurface)
                return errorSurface;
            else
                return NULL;
        }
        if (optimize)
        {
            SDL_Surface* dummy = surface;
            if(dummy->flags & SDL_SRCALPHA)
                surface = SDL_DisplayFormatAlpha(dummy);
            else
                surface = SDL_DisplayFormat(dummy);
            SDL_FreeSurface(dummy);
        }
        cache[filename].surface = surface;
        cache[filename].count = 1;
        return surface;
    }
    else
    {
        ++((*iter).second.count);
        return (*iter).second.surface;
    }
}

Uint32 SurfaceCache::unloadSurface(SDL_Surface const * const surf)
{
    std::map<std::string,CachedSurface>::iterator iter;
    for (iter = cache.begin(); iter != cache.end(); ++iter)
    {
        if ((*iter).second.surface == surf)
        {
            return --((*iter).second.count);
        }
    }
    return 0;
}

void SurfaceCache::clear()
{
    size_t size = cache.size();
    std::map<std::string,CachedSurface>::iterator iter;
    for (iter = cache.begin(); iter != cache.end(); ++iter)
    {
        if ((*iter).second.surface != errorSurface)
            SDL_FreeSurface((*iter).second.surface);
        (*iter).second.surface = NULL;
    }
    cache.clear();
    if (verbose)
        std::cout << "Surface cache cleared - deleted " << size << " images!" << std::endl;
}

void SurfaceCache::cleanUp()
{
    size_t size = cache.size();
    std::map<std::string,CachedSurface>::iterator iter;
    for (iter = cache.begin(); iter != cache.end();)
    {
        if ((*iter).second.count == 0)
        {
            (*iter).second.surface = NULL;
            cache.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }
    cache.clear();
    if (verbose)
        std::cout << "Surface cache cleaned - deleted " << size - cache.size() << " images!" << std::endl;
}

void SurfaceCache::removeSurface(const std::string &filename, const bool &destroy)
{
    std::map<std::string, CachedSurface>::iterator iter;

    iter = cache.find(filename);
    if (iter != cache.end())
    {
        if (verbose)
            std::cout << "Removing single surface from cache \"" << filename << "\"" << std::endl;
        if (destroy && (*iter).second.surface != errorSurface)
            SDL_FreeSurface((*iter).second.surface);
        (*iter).second.surface = NULL;
        cache.erase(iter);
    }
}

bool SurfaceCache::isCached(const std::string &filename) const
{
    std::map<std::string, CachedSurface>::const_iterator iter;

    iter = cache.find(filename);
    if (iter == cache.end())
        return false;
    return true;
}

//--- private ------------------------------------------------------------------

#define XOR(a,b) ((a) && !(b)) || (!(a) && (b))
#define CHECKER_SIZE 4

SDL_Surface* SurfaceCache::createErrorSurface(const Uint32 width, const Uint32 height) const
{
    SDL_Surface* dummy = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,32,
                        0xff000000, 0x00ff0000, 0x0000ff00,  0x000000ff);
    SDL_LockSurface(dummy);
    Uint8* pixel = (Uint8*)(dummy->pixels);
    for (int x=0;x<width;x++)
        for (int y=0;y<height;y++)
        {
            if (XOR(x % (CHECKER_SIZE*2) < CHECKER_SIZE,y % (CHECKER_SIZE*2) < CHECKER_SIZE))
            {
                pixel[(x+y*width)*4+0]=255; //A
                pixel[(x+y*width)*4+1]=0; //B
                pixel[(x+y*width)*4+2]=0; //G
                pixel[(x+y*width)*4+3]=0; //R
            }
            else
            {
                pixel[(x+y*width)*4+0]=255; //A
                pixel[(x+y*width)*4+1]=255; //B
                pixel[(x+y*width)*4+2]=0; //G
                pixel[(x+y*width)*4+3]=255; //R
            }
        }
    SDL_UnlockSurface(dummy);
    SDL_Surface* result = SDL_DisplayFormatAlpha(dummy);
    SDL_FreeSurface(dummy);
    return result;
}

SDL_Surface* SurfaceCache::getErrorSurface() {
    return errorSurface;
}
