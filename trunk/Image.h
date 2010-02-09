#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <SDL/SDL.h>
#ifdef PENJIN_GL
    #include <SDL/SDL_opengl.h>
    #include "Texture.h"
#elif PENJIN_SDL
    #include <SDL/SDL_rotozoom.h>
    #include <SDL/SDL_image.h>
#endif

#ifdef PLATFORM_WII
    #include "Penjin.h"
#endif

#include <string>
#include <vector>
using namespace std;

#include "PenjinTypes.h"
#include "PenjinErrors.h"
using namespace PenjinErrors;
#include "Colour.h"
#include "GFX.h"

class Image
{
    public:
        Image();
        ~Image();

        #ifdef PENJIN_SDL
            void loadImage(SDL_Surface* s)
            {
                images.push_back(s);
                sheetMode = false;
            }
            void disableTransparentColour(CRuint i)
            {
                SDL_SetColorKey(images.at(i), 0, images.at(i)->format->colorkey);
                colourKey.alpha = 0;
            }
            void disableTransparentColour(){disableTransparentColour(images.size()-1);}
        #elif PENJIN_GL
            void loadImage(const Texture& t)
            {
                textures.push_back(t);
                sheetMode = false;
            }
            void loadImage(SDL_Surface* s)
            {
                Texture t;
                t.loadSurface(s);
                textures.push_back(t);
                sheetMode = false;
            }
		#endif
		PENJIN_ERRORS loadImage(CRstring imageName);                                 // Load an image into the vector
        PENJIN_ERRORS loadImageNoKey(CRstring imageName);
        PENJIN_ERRORS loadImageSheet(CRstring imageName,CRuint xTiles,CRuint yTiles);  // store the separated images on the vector
        PENJIN_ERRORS loadImageSheetNoKey(CRstring imageName,CRuint xTiles,CRuint yTiles);
        PENJIN_ERRORS loadImageSheet(SDL_Surface *surface,CRuint xTiles,CRuint yTiles,CRuint skipTiles,CRuint numTiles); // use this for caching sprites, so Image objects can share data
        PENJIN_ERRORS loadImageSheetNoKey(SDL_Surface *surface,CRuint xTiles,CRuint yTiles,CRuint skipTiles,CRuint numTiles); // use this for caching sprites, so Image objects can share data
        PENJIN_ERRORS assignClipAreas(CRuint xTiles, CRuint yTiles,CRuint skipTiles,CRuint numTiles); // extracted identical code from loadImageSheet[NoKey]

        #ifdef PENJIN3D
            void renderImage(uint i,CRfloat destX,CRfloat destY,CRfloat destZ);
            template <class T>
            void renderImage(const T& destX,const T& destY){renderImage(0,destX,destY,0);}
            template <class T>
            void renderImage(CRuint i, const T& destX,const T& destY){renderImage(i,destX,destY,0);}
            template <class T>
            void renderImage(const T& position){renderImage(0,position.x,position.y,position.z);}
            template <class T>
            void renderImage(const T& destX,const T& destY,const T& destZ){renderImage(0,destX,destY,destZ);}
            template <class T>
            void renderImage(CRuint i,const T& position){renderImage(i,position.x,position.y,position.z);}
        #else
            template <class T>
            void renderImage(const T& destX,const T& destY){renderImage(0,destX,destY);}
            template <class T>
            void renderImage(const T& pos){renderImage(0,pos.x,pos.y);}
            template <class T>
            void renderImage(CRuint i, const T& pos){renderImage(i,pos.x,pos.y);}
            void renderImage(uint i, CRfloat destX,CRfloat destY);
            #ifdef PENJIN_SDL
                void renderImage(uint i,CRint destx, CRint desty){renderImage(i,screen, destx,desty);}
                void renderImage(uint i,SDL_Surface *dstimg,CRint destx,CRint desty);    // Render specific image to the surface
                template <class T>
                void renderImage(SDL_Surface* dstimg,const T& destX,const T& destY){renderImage(0,dstimg,destX,destY);}            // Render the default image
                template <class T>
                void renderImage(SDL_Surface* dstimg,const T& pos){renderImage(dstimg, pos.x, pos.y);}
                void renderImage(CRuint i, SDL_Surface* screen, CRFixed x, CRFixed y){renderImage(i, screen, fixedpoint::fix2int(x), fixedpoint::fix2int(y));}
                template <class T>
                void renderImage(CRuint i, SDL_Surface* screen,const T& pos){renderImage(i, screen, pos.x, pos.y);}
            #endif
        #endif

        PENJIN_ERRORS setTransparentColour(CRuint i, const Vector2di& pixel);
        PENJIN_ERRORS setTransparentColour(const Vector2di& pixel)
        {
            PENJIN_ERRORS error;
            uint i;
            #ifdef PENJIN_SDL
            for (i=0;i<images.size();i++)
            {
                error = setTransparentColour(i,pixel);
                if (error != PENJIN_OK) return error;
            }
            #elif PENJIN_GL
            for (i=0;i<textures.size();i++)
            {
                error = setTransparentColour(i,pixel);
                if (error != PENJIN_OK) return error;
            }
            #endif
            return error;
        }
        PENJIN_ERRORS setTransparentColour(CRuint i, const Colour& c);
        PENJIN_ERRORS setTransparentColour(const Colour& c)
        {
            PENJIN_ERRORS error;
            uint i;
            #ifdef PENJIN_SDL
            for (i=0;i<images.size();i++)
            {
                error = setTransparentColour(i,c);
                if (error != PENJIN_OK) return error;
            }
            #else
            for (i=0;i<textures.size();i++)
            {
                error = setTransparentColour(i,c);
                if (error != PENJIN_OK) return error;
            }
            #endif
            return error;
        }

        size_t size()const;                  // Returns the number of images in the vector
        void clear();                 // Clears all images out of the vector

        uchar getAlpha()const;  // Presumes all images are same dimensionality.
        uint getWidth()const;
        uint getHeight()const;
        void setAlpha(const uchar& alpha); //  alpha 0 to 255
        #ifndef PENJIN3D
            void setScaleX(CRfloat scaleX){this->scale.x = scaleX;}
            void setScaleY(CRfloat scaleY){this->scale.y = scaleY;}
            void setScale(CRfloat scale){this->scale.x = this->scale.y = scale;}
            void setRotation(CRfloat angle){this->angle = angle;}
        #endif
        #ifdef PENJIN_SDL
            //	Set if to use a HW surface to blit
            void setUseHardware(CRbool useHW){if(useHW){convertToHW();}}
            void setUseHardWare(){convertToHW();}
            /// Pixel manipulation functions
            // check and lock screen
            void screenLock();
            // set a pixel
            void setPixel(CRint x,CRint y,const Colour& colour);
            void setPixel(CRint x,CRint y,const uchar& r,const uchar& g,const uchar& b,const uchar& a);
            void setPixel(CRint x,CRint y,const uchar& r,const uchar& g,const uchar& b);
            // get a pixel
            Colour getPixel(CRint x,CRint y){return GFX::getPixel(images.at(0),x,y);}
            Colour getPixel(CRuint i,CRint x,CRint y){return GFX::getPixel(images.at(i),x,y);}
            uint* getPixelArray(CRint x,CRint y);
            // check and unlock screen
            void screenUnlock();
        #elif PENJIN_GL
            #ifdef PENJIN3D
                void setRotation(const Vector3df& rotationVector) {rotation = rotationVector;}
                void setRotation(CRfloat a){rotation.z = a;}
                void setScale(const Vector3df& scaleVector) {scale = scaleVector;}
                void setScale(CRfloat s){scale.x=scale.y=scale.z=s;}
                void setScaleX(CRfloat s){scale.x = s;}
                void setScaleY(CRfloat s){scale.y=s;}
            #endif

            void setAlpha(float alpha) //  alpha in the range of 0 to 1;
            {
                if(alpha>1.0f)
                    alpha = 1.0f;
                else if(alpha<0.0f)
                    alpha = 0.0f;
                setAlpha(alpha*255);
            }
             // set a pixel
            void setPixel(CRfloat x,CRfloat y,const Colour& colour);
            void setPixel(CRfloat x,CRfloat y,const uchar& r,const uchar& g,const uchar& b,const uchar& a);
            void setPixel(CRfloat x,CRfloat y,const uchar& r,const uchar& g,const uchar& b);
            void setPixel(CRfloat x,CRfloat y,CRfloat z,const Colour& colour);
            void setPixel(CRfloat x,CRfloat y,CRfloat z,const uchar& r,const uchar& g,const uchar& b,const uchar& a);
            void setPixel(CRfloat x,CRfloat y,CRfloat z,const uchar& r,const uchar& g,const uchar& b);

            // Get a pixel from the image
            Colour getPixel(CRint x, CRint y);

            /// Override dimensions of texture
            void setWidth(CRint w){textures[0].setWidth(w);}
            void setHeight(CRint h){textures[0].setHeight(h);}
            void setDimensions(const Vector2di& dims){textures[0].setDimensions(dims);}

            // get a pixel
           /* Colour getPixel(float x, float y);
            uint* getPixelArray(float x, float y);
            Colour getPixel(float x, float y, float z);
            uint* getPixelArray(float x, float y, float z);*/
        #endif

        //  Effects
        void toGreyScale(); //  convert this image to greyscale
        void toNegative();  //  convert to an inverse image
        void swapRG();      //  Swap the red and green channels
        void swapGB();      //  Swap the green and blue channels
        void swapRB();      //  Swap the red and blue channels
    private:
        // Disabled to revent double freed pointers.
        Image(const Image& BlingRef);
        Image& operator=(const Image& BlingRef);

        Colour colourKey;

        #ifdef PENJIN_SDL
            void convertToHW();
            vector<SDL_Surface*>images; //  Stores surfaces
            SDL_Surface* screen;        //  The pointer to the screen;
		#elif PENJIN_GL
            vector<Texture> textures;   //  Stores Textures for image
		#endif

		bool sheetMode;             //  Performs tilesheet style loading/rendering

        uchar alpha;
        vector<SDL_Rect>clipAreas;  //  Stores clipping planes
        #ifdef PENJIN3D
            Vector3df scale;            //  scale Vector for opengl
            Vector3df rotation;         //  Rotation Vector for opengl
        #else
            Vector2df scale;
            float angle;                //  angle for rotations
        #endif

};
#endif // IMAGE_H_INCLUDED
