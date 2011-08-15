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
#ifndef SURFACE_CACHE_H
#define SURFACE_CACHE_H

#include <map>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/**
All image loading can done through this cache
This helps to center error output and also ensures no graphic is loaded twice,
but rather shared between objects through the SDL_Surface pointer
**/

#define SURFACE_CACHE SurfaceCache::getSurfaceCache()

class SurfaceCache
{
    private:
        SurfaceCache();
        static SurfaceCache *self;
    public:
        virtual ~SurfaceCache();
        static SurfaceCache* getSurfaceCache();

        // loads an image from file or the cache if already loaded previously
        // optimize tries to optimize the surface for fast blitting
        // also use it when having display problems
        // returns errorSurface or NULL on error depending on setting
        SDL_Surface* loadSurface(const std::string &filename, const bool &optimize=false);
        // indicate to the cache that one instance of a surface has been deleted,
        // thus reducing its useCount - does not do any clean up
        // returns the resulting useCount
        Uint32 unloadSurface(SDL_Surface const * const surf);

        // clear the cache - frees all stored surfaces!
        void clear();

        // clears all currently unused surfaces (with count == 0)
        void cleanUp();

        // removes a surface from the cache, set destroy to false to only remove
        // the reference from the map and not actually free the surface
        void removeSurface(const std::string &filename,const bool &destroy=true);

        // returns the number of loaded surfaces
        size_t size() const {return cache.size();}

        // check whether a file is present in the cache
        bool isCached(const std::string &filename) const;

        SDL_Surface* getErrorSurface();

        // settings
        bool returnErrorSurface; // if set to true an errorSurface is returned, NULL otherwise (default = true)
        bool verbose;            // if set to true will write status messages to stdout (default true)
    protected:
    private:
        SDL_Surface* createErrorSurface(const Uint32 width, const Uint32 height) const;

        struct CachedSurface
        {
            SDL_Surface *surface;
            Uint32 count;
        };
        std::map<std::string, CachedSurface> cache;
        SDL_Surface* errorSurface;
};


#endif // SURFACE_CACHE_H

