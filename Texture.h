#ifndef INC_TEXTURE_H
#define INC_TEXTURE_H

#ifdef PENJIN_GL
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include "NumberUtility.h"
#include "PenjinTypes.h"
#include "PenjinErrors.h"
//#include "Colour.h"
#include "GFX.h"
using namespace PenjinErrors;

class Texture
{
	public :
        Texture();
        Texture(CRstring fileName);
        ~Texture();

        Colour getTransparentColour()const{return transparent;}
        void setTransparentColour(const Colour& c){transparent = c;}

        PENJIN_ERRORS loadSurface(SDL_Surface* surface){return loadSurface(surface,true);}            //  Load a texture from a surface
        PENJIN_ERRORS loadSurfaceNoKey(SDL_Surface* surface){return loadSurface(surface,false);}
        PENJIN_ERRORS loadTexture(CRstring fileName){return loadTexture(fileName,true);}               //  Load a texture from an image file
        PENJIN_ERRORS loadTextureNoKey(CRstring imageName){return loadTexture(imageName,false);}       // Load a texture with no colourkey

        bool isLoaded()const{return loaded;}                //  Check if the texture is still taking up mem by OpenGL

        void setTextureID(const GLuint& textureID);             //  If you have created a texture elsewhere you can pass in
                                                                //    the ID so that it will be cleaned up
        GLuint getTextureID()const{return textureID;}

        int getWidth()const{return dimensions.x;}
        int getHeight()const{return dimensions.y;}
        void setDimensions(const Vector2di& dims){dimensions = dims;}  // overide dimensions
        Vector2di getDimensions()const{return dimensions;}
        void setWidth(const int& w){dimensions.x = w;}
        void setHeight(const int& h){dimensions.y = h;}

        //  Get the RAW dimensions
        int getRawWidth()const{return rawDimensions.x;}
        int getRawHeight()const{return rawDimensions.y;}
        Vector2di getRawDimensions()const{return rawDimensions;}

	private :
        void init();
        PENJIN_ERRORS loadSurface(SDL_Surface* screen, CRbool keyed);
        PENJIN_ERRORS loadTexture(CRstring file, CRbool keyed);
        GLenum getTextureFormat(SDL_Surface* surface);  // Get the proper OpenGL format of the data stored in an SDL surface
        /// Check if a value is a power of two
        bool isPoT(const int& x)const{return NumberUtility::isPowerOfTwo(x);}
		bool loaded;
		GLuint textureID;
        Vector2di rawDimensions;   // stores the raw width and height in pixels of the image.
        Vector2di dimensions;
        Colour transparent;
};
#endif
#endif