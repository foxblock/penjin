#include "Texture.h"
#ifdef PENJIN_GL
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
    transparent = MAGENTA;
}

Texture::~Texture()
{
	if(loaded)
		glDeleteTextures( 1, &textureID);
    loaded = false;
}

PENJIN_ERRORS Texture::loadSurface(SDL_Surface* surface, CRbool keyed)
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

    SDL_Surface* intermediary = NULL;
	GLenum textureFormat = NULL;
	int numColours = surface->format->BytesPerPixel;
    intermediary = SDL_CreateRGBSurface(SDL_SWSURFACE, rawDimensions.x, rawDimensions.y, surface->format->BitsPerPixel,
    GFX::RED_MASK, GFX::GREEN_MASK, GFX::BLUE_MASK, GFX::ALPHA_MASK);
    if(keyed)
    {
        transparent = GFX::getPixel(surface,0,0);

        SDL_FillRect(intermediary, NULL, SDL_MapRGBA(intermediary->format,transparent.red,transparent.green,transparent.blue,0));
        SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(intermediary->format,transparent.red,transparent.green,transparent.blue));
        transparent.alpha = 1;  //  We use this as a flag that a tranparent key is set.
    }
    SDL_SetAlpha(surface,0,SDL_ALPHA_OPAQUE);
    SDL_BlitSurface(surface, 0 , intermediary, 0);
    textureFormat = getTextureFormat(intermediary);

	glPixelStorei(GL_UNPACK_ALIGNMENT, numColours);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
#ifdef PENJIN3D
    gluBuild2DMipmaps(GL_TEXTURE_2D, textureFormat,intermediary->w, intermediary->h, textureFormat, GL_UNSIGNED_BYTE, intermediary->pixels);
#else
    glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, intermediary->w, intermediary->h, 0, textureFormat, GL_UNSIGNED_BYTE, intermediary->pixels);
#endif
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
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

PENJIN_ERRORS Texture::loadTexture(CRstring fileName, CRbool keyed)
{
	SDL_Surface* surface = NULL;
	surface = IMG_Load(fileName.c_str());
	return loadSurface(surface,keyed);
}

GLenum Texture::getTextureFormat(SDL_Surface* surface)
{
    int numColours = surface->format->BytesPerPixel;

    if (numColours == 4)
    {
        if (surface->format->Rmask == 0x000000ff)
            return GL_RGBA;
        else
            return GL_BGRA;
    }
    else if (numColours == 3)
    {
        if (surface->format->Rmask == 0x000000ff)
            return GL_RGB;
        else
            return GL_BGR;
    }
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

