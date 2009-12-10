#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "Image.h"
#include "PenjinTypes.h"

class Sprite
{
    public:
        Sprite();
        #ifndef PENJIN3D
            Sprite(CRint x,CRint y);
            Sprite(const Vector2di& position);
        #else
            Sprite(CRfloat x,CRfloat y);
            Sprite(const Vector2df& position);
            Sprite(CRfloat x,CRfloat y,CRfloat z);
            Sprite(const Vector3df& position);
        #endif
        PENJIN_ERRORS loadSprite(CRstring fileName);     // Loads an image for this sprite

        PENJIN_ERRORS setTransparentColour(const Colour& c){return image.setTransparentColour(c);}
        PENJIN_ERRORS setTransparentColour(const Vector2di& v){return image.setTransparentColour(v);}
        void setAlpha(const uchar& alpha){image.setAlpha(alpha);}
        uchar getAlpha()const{return image.getAlpha();}
        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);         // Draws the image onto the screen
            void render(){render(screen);}
            bool hasCollided(Sprite &spr);			//	Has this sprite collided with the passed in sprite?
            void loadSprite(SDL_Surface* s){image.loadImage(s);}
        #else
            void render();
        #endif
        uint getWidth()const{return image.getWidth();}
        uint getHeight()const{return image.getHeight();}

        void setRotation(CRfloat angle){image.setRotation(angle);}
        void setScaleX(CRfloat scaleX){image.setScaleX(scaleX);}
        void setScaleY(CRfloat scaleY){image.setScaleY(scaleY);}
        void setScale(CRfloat scale){image.setScale(scale);}
        #ifdef PENJIN_SDL
            void setUseHardware(CRbool useHW){image.setUseHardware(useHW);}
            void setX(CRint x){position.x = x;}
            void setX(CRFixed x){position.x = fixedpoint::fix2int(x);}
            void setY(CRint y){position.y = y;}
            void setY(CRFixed y){position.y = fixedpoint::fix2int(y);}
            Vector2df getPosition(){return position;}
            void setPosition(CRFixed x,CRFixed y){setPosition(Vector2dx(x,y));}
            void setPosition(CRint x,CRint y){setPosition(Vector2di(x,y));}
            void setPosition(const Vector2dx& position){this->position.x = position.x.intValue >>16;this->position.y = position.y.intValue >>16;}
            template <class T>
            void setPosition(const T& position){this->position = position;}
            float getX()const{return position.x;}
            float getY()const{return position.y;}
        #else
            void setScale(const Vector3df& scale);
            void setX(CRfloat x){position.x = x;}
            void setY(CRfloat y){position.y = y;}
            #ifdef PENJIN3D
                void setZ(CRfloat z){position.z = z;}
                float getZ()const{return position.z;}
                Vector3df getPosition()const{return position;}
            #else
                Vector2df getPosition()const{return position;}
            #endif
            void setRotation(const Vector3df& rotationVector);
            template <class T>
            void setPosition(const T& position){this->position = position;}
            void setPosition(const Vector2df& position){setPosition(Vector3df(position.x, position.y, 0.0f));}
            void setPosition(CRfloat x,CRfloat y,CRfloat z){setPosition(Vector3df(x,y,z));}
            void setPosition(CRfloat x,CRfloat y){setPosition(x,y, 0.0f);}
            float getX()const{return position.x;}
            float getY()const{return position.y;}
        #endif
        void clear(){image.clear();}
    private:
        Image image;
        #ifdef PENJIN3D
            Vector3df position;
        #else
            Vector2df position;
        #endif
        #ifdef PENJIN_SDL
            SDL_Surface* screen;
        #endif
};


#endif // SPRITE_H_INCLUDED
