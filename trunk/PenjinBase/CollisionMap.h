#ifndef COLLISIONMAP_H
#define COLLISIONMAP_H

#include "Image.h"
#include "GFX.h"

class CollisionMap
{
    public:
        CollisionMap();
        ~CollisionMap();

        PENJIN_ERRORS loadImage(CRstring image){return map.loadImageNoKey(image);}
        void setNoCollisionColour(const Colour& c){noCollision = c;}
        Colour getNoCollisionColour()const{return noCollision;}

        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);
            void render();
        #else
            void render();
        #endif

        Colour getCollisionType(CRuint x, CRuint y){return map.getPixel(x,y);}  //  check what sort of collision has been made.
        bool hasCollided(CRuint x, CRuint y){return (getCollisionType(x,y) == noCollision);}         //  has there been a collision?

    private:
        Image map;
        Colour noCollision;
};

#endif // COLLISIONMAP_H
