#include "Image.h"

Image::Image()
{
    alpha = 255;
    #ifdef PENJIN3D
        rotation.x = rotation.y = rotation.z = 0.0f;
        scale.x = scale.y = scale.z = 1.0f;
    #else
        scale.x = 1;
        scale.y = 1;
        angle = 0;
    #endif

    #ifdef PENJIN_SDL
        //  Get the screen pointer
        screen = SDL_GetVideoSurface();
        //	By default we don't want to process rotation since these are slower
        //useRotation = false;
        useHardware = false;    //  and HW doesn't support alpha (need colour masking for transparencies)
    #endif

    sheetMode = false;      //  Stores if we use a spritesheet or if we use separate surfaces.
}

Image::~Image()
{
	clear();
}


PENJIN_ERRORS Image::setTransparentColour(CRuint i, const Colour& c)
{
#ifdef PENJIN_SDL
    if((size_t)i >= images.size())
        return PENJIN_INVALID_INDEX;
    if(SDL_SetColorKey(images[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(images[i]->format,c.red,c.green,c.blue)) == -1)
            return PENJIN_SDL_INVALID_COLORKEY;
    return PENJIN_OK;
#endif
    return PENJIN_OK;
}

PENJIN_ERRORS Image::setTransparentColour(CRuint i, const Vector2di& v)
{
#ifdef PENJIN_SDL
    if((size_t)i >= images.size())
        return PENJIN_INVALID_INDEX;
    Colour c = GFX::getPixel(images[i],v.x,v.y);
    return setTransparentColour(i,c);
#endif
    return PENJIN_OK;
}

PENJIN_ERRORS Image::loadImage(CRstring name)
{
    PENJIN_ERRORS error;
    #ifdef PENJIN_SDL
        //  load image
        error = loadImageNoKey(name);
        if(error != PENJIN_OK)
            return error;

        //  Apply colour key
        uint currentI = (uint)images.size()-1;
        error = setTransparentColour(currentI,Vector2di(0,0));
    #else
        textures.resize(textures.size()+1);
        error = (PENJIN_ERRORS)textures[textures.size()-1].loadTexture(name);
        if(error != PENJIN_OK)
        {
            textures.pop_back();
            return error;
        }
    #endif
    sheetMode = false;
    return error;
}

PENJIN_ERRORS Image::loadImageNoKey(CRstring name)
{
    #ifdef PENJIN_SDL
        uint currentI = (uint)images.size();
        images.push_back(NULL);
        images[currentI] = IMG_Load(name.c_str());
        if (!images[currentI])
        {
            images.pop_back();
            return PENJIN_IMG_UNABLE_TO_OPEN;
        }
        isConverted.push_back(false);
    #else
        textures.resize(textures.size()+1);
        PENJIN_ERRORS error = (PENJIN_ERRORS)textures[textures.size()-1].loadTextureNoKey(name);
        if(error != PENJIN_OK)
        {
            textures.pop_back();
            return error;
        }
    #endif
    sheetMode = false;
    return PENJIN_OK;
}

PENJIN_ERRORS Image::loadImageSheet(CRstring name,CRuint xTiles,CRuint yTiles)
{
    //  We load the image into the image vector
    PENJIN_ERRORS error = loadImage(name);
    if(error != PENJIN_OK)
        return error;
    sheetMode = true;  //  succesful loading means we have a tilesheet

    //  now we have to build the clipping areas based on the tile info we have.
    //first the width and height per tile needs to be calculated
    #ifdef PENJIN_SDL
        uint width = images[0]->w;
        uint height = images[0]->h;
    #else
        uint width = textures[0].getWidth();
        uint height = textures[0].getHeight();
    #endif
    uint xTileWidth = width/xTiles;
    uint yTileWidth = height/yTiles;

    //  Accomodate clip areas
    clipAreas.resize(xTiles*yTiles);

    uint currTile = 0;
    //  Run along then down

    for(uint y = 0; y < height; y+=yTileWidth)
    {
        for(uint x = 0; x < width; x+=xTileWidth)
        {
            //  and set the values for the clip plane
            clipAreas[currTile].x = x;
            clipAreas[currTile].y = y;
            clipAreas[currTile].w = xTileWidth;
            clipAreas[currTile].h = yTileWidth;
            ++currTile;
        }
    }
    return PENJIN_OK;
}

PENJIN_ERRORS Image::loadImageSheetNoKey(CRstring name,CRuint xTiles,CRuint yTiles)
{
    //  We load the image into the image vector
    PENJIN_ERRORS error = loadImageNoKey(name);
    if(error != PENJIN_OK)
        return error;
    sheetMode = true;  //  succesful loading means we have a tilesheet

    //  now we have to build the clipping areas based on the tile info we have.
    //first the width and height per tile needs to be calculated
    #ifdef PENJIN_SDL
        uint width = images[0]->w;
        uint height = images[0]->h;
    #else
        uint width = textures[0].getWidth();
        uint height = textures[0].getHeight();
    #endif
    uint xTileWidth = width/xTiles;
    uint yTileWidth = height/yTiles;

    //  Accomodate clip areas
    clipAreas.resize(xTiles*yTiles);

    uint currTile = 0;
    //  Run along then down

    for(uint y = 0; y < height; y+=yTileWidth)
    {
        for(uint x = 0; x < width; x+=xTileWidth)
        {
            //  and set the values for the clip plane
            clipAreas[currTile].x = x;
            clipAreas[currTile].y = y;
            clipAreas[currTile].w = xTileWidth;
            clipAreas[currTile].h = yTileWidth;
            ++currTile;
        }
    }
    return PENJIN_OK;
}

#ifdef PENJIN_SDL
    void Image::renderImage(uint i,CRfloat destx, CRfloat desty)
    {
        #ifdef PENJIN_FIXED
            renderImage(i,fixedpoint::fix2int(destx),fixedpoint::fix2int(destx));
        #else
            renderImage(i,(int)destx, (int) desty);
        #endif
    }
    void Image::renderImage(uint i, SDL_Surface* dstimg, CRint destx, CRint desty)
    {
        // Don't render if invisible or if there is no image!
        if(alpha == SDL_ALPHA_TRANSPARENT)
            return;
        if(!images.size() || i >= this->size())
        {
            if(sheetMode)   //  We have a spritesheet
            {
                //  If there is no area to clip the spritesheet we have a problem
                if(!images[0] || clipAreas.size() || !clipAreas[i].w || !clipAreas[i].h)
                    return;
            }
            else if(!images[i])
                return;
        }

       // Set up blitting area
       SDL_Rect src, dst;
        //   If the image is a spritesheet, then set the relevant clips
        if(sheetMode)
        {
            src.x = clipAreas[i].x;
            src.y = clipAreas[i].y;
            src.w = clipAreas[i].w;
            src.h = clipAreas[i].h;
            i = 0;  // only element zero should have spritesheet data
        }
        else    //  Make the clip the size of the image
        {
            src.x = images[i]->clip_rect.x;
            src.y = images[i]->clip_rect.y;
            src.w = images[i]->w;
            src.h = images[i]->h;
        }

        dst.x = destx;
        dst.y = desty;

        // Check if we need to alpha blend
        if(alpha != SDL_ALPHA_OPAQUE)   //  We check SDL_ALPHA_TRANSPARENT earlier.
            SDL_SetAlpha(images[i], SDL_SRCALPHA|SDL_RLEACCEL, alpha);
        if((angle == 0 && scale.x == 1 && scale.y == 1) && !useHardware)
            SDL_BlitSurface(images[i], &src, dstimg, &dst);

        else if(angle != 0 || scale.x!= 1 || scale.y!= 1)
        {
            SDL_Surface* tempImage = NULL;
            SDL_Surface* subSprite = NULL; // Need to use this for animated sprites to get the subsprite isolated.
            if(sheetMode)
            {
                subSprite = GFX::cropSurface(images[i],&src);
                #ifdef PENJIN_FIXED
                    tempImage = rotozoomSurfaceXY(subSprite,
                    fixedpoint::fix2float(angle),
                    fixedpoint::fix2float(scale.x),
                    fixedpoint::fix2float(scale.y),SMOOTHING_OFF);
                #else
                    tempImage = rotozoomSurfaceXY(subSprite, angle, scale.x, scale.y, SMOOTHING_ON);
                #endif
                dst.x += (subSprite->w - tempImage->w)*0.5f;
                dst.y += (subSprite->h - tempImage->h)*0.5f;
                SDL_FreeSurface(subSprite);
            }
            else
            {
                #ifdef PENJIN_FIXED
                    tempImage = rotozoomSurfaceXY(images[i],
                    fixedpoint::fix2float(angle),
                    fixedpoint::fix2float(scale.x),
                    fixedpoint::fix2float(scale.y),SMOOTHING_OFF);
                #else
                    tempImage = rotozoomSurfaceXY(images[i], angle, scale.x, scale.y, SMOOTHING_ON);
                #endif
                dst.x += (images[i]->w - tempImage->w)*0.5f;
                dst.y += (images[i]->h - tempImage->h)*0.5f;
            }
            SDL_BlitSurface(tempImage,NULL, dstimg, &dst);
            SDL_FreeSurface(tempImage);
        }
        else	//	The only other option is to use HW surfaces
        {
            //	Check if we have converted the current image to a HW Surface already
            if(!isConverted[i])
            {
                //	convert current image
                SDL_Surface* temp = images[i];
                images[i] = SDL_ConvertSurface(images[i], dstimg->format, SDL_HWSURFACE);
                SDL_FreeSurface(temp);
                isConverted[i] = true;
            }
            // Now we blit
            SDL_BlitSurface(images[i], &src, dstimg, &dst);
        }
    }
    //void Image::renderImage(SDL_Surface* dstimg, const Vector2di& pos){renderImage(0, dstimg, pos.x, pos.y);}
    //template <class  T>
    //void Image::renderImage(SDL_Surface* dstimg, const T& destX, const T& destY){renderImage(0,dstimg,destX,destY);}

    void Image::screenLock()
    {
       // Check and lock the surface if necessary.
       if (SDL_MUSTLOCK(images.at(0)))
            if (SDL_LockSurface(images.at(0)) < 0 )
                return;
    }

    void Image::setPixel(CRint x, CRint y, CRuchar r, CRuchar g, CRuchar b,CRuchar a){GFX::setPixel(images.at(0),x,y,Colour(r,g,b,a));}
    void Image::setPixel(CRint x, CRint y, CRuchar r, CRuchar g, CRuchar b){setPixel(x,y,r,g,b,255);}
    void Image::setPixel(CRint x, CRint y, const Colour& c){setPixel(x,y,c.red,c.green,c.blue,c.alpha);}

    void Image::screenUnlock()
    {
       // Check and unlock the durface if necessary
       if ( SDL_MUSTLOCK(images.at(0)) )
            SDL_UnlockSurface(images.at(0));
    }
#else
    #ifdef PENJIN3D
        void Image::renderImage(uint i,CRfloat destx, CRfloat desty,CRfloat destz)
    #else
        void Image::renderImage(uint i,CRfloat destx, CRfloat desty)
    #endif
    {
        // Don't render if invisible or if there is no image!
        if(!textures.size() || alpha == 0)
        {
            if(sheetMode)   //  We have a spritesheet
            {
                //  If there is no area to clip the spritesheet we have a problem
                if(!textures[0].isLoaded() || !clipAreas.size() || !clipAreas[i].w || !clipAreas[i].h)
                    return;
            }
            else if(!textures[i].isLoaded())
                return;
        }

        // Set up blitting area
        Vector4df texCoords;
        Vector2df dims;
        dims.x = textures[0].getRawWidth();
        dims.y = textures[0].getRawHeight();
        //   If the image is a spritesheet, then set the relevant clips
        if(sheetMode)
        {
            texCoords.x = (float)clipAreas[i].x / (float)dims.x;
            texCoords.y = (float)clipAreas[i].y / (float)dims.y;
            texCoords.z = ((float)clipAreas[i].x + (float)clipAreas[i].w) / (float)dims.x;
            texCoords.w = ((float)clipAreas[i].y + (float)clipAreas[i].h) / (float)dims.y;
            i = 0;  // only element zero should have spritesheet data
        }
        else    //  Make the clip the size of the image
        {
            texCoords.x = 0.0f;
            texCoords.y = 0.0f;
            texCoords.z = 1.0f;
            texCoords.w = 1.0f;
        }

        // Check if we need to alpha blend
        float tAlpha = (float)alpha *0.003921569f;
        //  Set OpenGL alpha
        #ifdef PENJIN_FIXED
            glColor4f(1.0f, 1.0f, 1.0f,fixedpoint::fix2float( tAlpha));
        #else
            glColor4f(1.0f, 1.0f, 1.0f, tAlpha);
        #endif
        // Scale and rotate
        glPushMatrix();
        #ifdef PENJIN3D
            glScalef(scale.x, scale.y, scale.z);
            glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
            glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
            glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
        #else
            glScalef(scale.x,scale.y,1.0f);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
        #endif
        glLoadIdentity( );
        //glMatrixMode( GL_MODELVIEW );
            glEnable(GL_TEXTURE_2D);
                if(textures[i].getTransparentColour().alpha == 1)
                {
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glEnable(GL_BLEND);
                    glAlphaFunc(GL_GREATER,0.1f);
                    glEnable(GL_ALPHA_TEST);
                }
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                glBindTexture (GL_TEXTURE_2D, textures[i].getTextureID());
                glBegin(GL_QUADS);
                    glTexCoord2f (texCoords.x, texCoords.y);
                    #ifdef PENJIN3D
                        glVertex3f(destx, desty,  destz);
                    #else
                        glVertex2f(destx,desty);
                    #endif
                    glTexCoord2f (texCoords.z, texCoords.y);
                    if(!sheetMode)
                    {
                        #ifdef PENJIN3D
                            glVertex3f(destx + textures[i].getRawWidth(), desty, destz);
                        #else
                            glVertex2f(destx + textures[i].getRawWidth(), desty);
                        #endif
                        glTexCoord2f (texCoords.z, texCoords.w);
                        #ifdef PENJIN3D
                            glVertex3f(destx + textures[i].getRawWidth(), desty + textures[i].getRawHeight(), destz);
                        #else
                            glVertex2f(destx + textures[i].getRawWidth(), desty + textures[i].getRawHeight());
                        #endif
                        glTexCoord2f (texCoords.x, texCoords.w);
                        #ifdef PENJIN3D
                            glVertex3f(destx, desty + textures[i].getRawHeight(), destz);
                        #else
                            glVertex2f(destx, desty + textures[i].getRawHeight());
                        #endif
                    }
                    else
                    {
                        #ifdef PENJIN3D
                            glVertex3f(destx + clipAreas[i].w, desty, destz);
                        #else
                            glVertex2f(destx + clipAreas[i].w, desty);
                        #endif
                        glTexCoord2f (texCoords.z, texCoords.w);
                        #ifdef PENJIN3D
                            glVertex3f(destx + clipAreas[i].w, desty + clipAreas[i].h, destz);
                        #else
                            glVertex2f(destx + clipAreas[i].w, desty + clipAreas[i].h);
                        #endif
                        glTexCoord2f (texCoords.x, texCoords.w);
                        #ifdef PENJIN3D
                            glVertex3f(destx, desty + clipAreas[i].h, destz);
                        #else
                            glVertex2f(destx, desty + clipAreas[i].h);
                        #endif
                    }
                glEnd();
                if(textures[i].getTransparentColour().alpha == 1)
                {
                    glDisable(GL_BLEND);
                    glDisable(GL_ALPHA_TEST);
                }
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    void Image::setPixel(CRfloat x,CRfloat y,CRfloat z,const uchar& r,const uchar& g,const uchar& b,const uchar& a)
    {
            glColor4f(r*0.003921569f, g*0.003921569f, b*0.003921569f, a*0.003921569f); // 1/255
            glBegin(GL_POINTS);
                glVertex3f(x, y, z);
            glEnd();
    }
    void Image::setPixel(CRfloat x,CRfloat y,CRfloat z,const uchar& r,const uchar& g,const uchar& b,const uchar& a);
    void Image::setPixel(CRfloat x,CRfloat y,CRfloat z,const uchar& r,const uchar& g,const uchar& b){setPixel(x,y,z,r,g,b,255);}
    void Image::setPixel(CRfloat x,CRfloat y,CRfloat z,const Colour& c){setPixel(x,y,z,c.red,c.green,c.blue,c.alpha);}
    void Image::setPixel(CRfloat x,CRfloat y,const uchar& r,const uchar& g,const uchar& b,const uchar& a){setPixel(x,y,0.0f,r,g,b,255);}
    void Image::setPixel(CRfloat x,CRfloat y,const uchar& r,const uchar& g,const uchar& b){setPixel(x,y,0.0f,r,g,b,255);}
    void Image::setPixel(CRfloat x,CRfloat y,const Colour& c){setPixel(x,y,0.0f,c.red,c.green,c.blue,c.alpha);}

    Colour Image::getPixel(CRint x, CRint y)
    {
        glPushAttrib(GL_ENABLE_BIT);
        glDrawBuffer(GL_BACK);

        // TODO: save the pixel that was at 0, 0

        // Only clear one point for our operation
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glScissor(0, 0, 1, 1);
        glEnable(GL_SCISSOR_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glOrtho(0, 1.0, 1.0, 0, -0.001, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glBindTexture(GL_TEXTURE_2D, textures.at(0).getTextureID());
        glEnable(GL_TEXTURE_2D);

        // Draw the one point of our texture
        glBegin(GL_POINTS);
            glTexCoord3f(x/getWidth(), y/getHeight(), 0);
            glVertex3f(0, 0, 0);
        glEnd();

        // Read the alpha value: if the pixel was
        // opaque (glAlphaTest succeeded), z-buffer was
        // written to by the above operation, otherwise
        // it should be intact
        GLfloat pix[4*4];
        glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, pix);

        // TODO: put back the pixel that was at 0, 0

        glScissor(0, 0, 1, 1);

        glMatrixMode(GL_PROJECTION);
        glDepthFunc(GL_LESS);

        glPopAttrib();
        return Colour((float)pix[0],pix[1],pix[2],pix[3]);
    }
#endif // PENJIN_SDL

size_t Image::size()const
{
    if(sheetMode)
        return clipAreas.size();
    else
    {
        #ifdef PENJIN_SDL
            return images.size();
        #else
            return textures.size();
        #endif
    }
}

void Image::clear()
{
    #ifdef PENJIN_SDL
        int i = images.size()-1;
        while(i >= 0)
        {
            if(images[i])
            {
                SDL_FreeSurface(images[i]);
                images[i] = NULL;
            }
            --i;
        }
        images.clear();
    #else
        textures.clear();
    #endif
    if(sheetMode)
        clipAreas.clear();
    sheetMode = false;
}

void Image::setAlpha(const uchar& alpha){this->alpha = alpha;}

uchar Image::getAlpha()const{return alpha;}

uint Image::getHeight()const
{
    if(sheetMode)
        return clipAreas.front().h;

    #ifdef PENJIN_SDL
        return images.front()->h;
    #else
        return textures.front().getHeight();
    #endif
}

uint Image::getWidth()const
{
    if(sheetMode)
        return clipAreas.front().w;

    #ifdef PENJIN_SDL
        return images.front()->w;
    #else
        return textures.front().getWidth();
    #endif
}
