#ifndef COLLISIONREGION_H
#define COLLISIONREGION_H

/*************************************************
    CollisionRegion by foxblock for Penjin
    ---
    Multi-purpose collision checking class
    Works either using a special collision image or a simple rectangular region
    Can create a rectangular region from the collision image to simplify and speed up collision checking
*************************************************/

#include "Image.h"
#include "PenjinTypes.h"
#include "NumberUtility.h"
#include "Rectangle.h"
#include "Vector2di.h"

class CollisionRegion
{
    public:
        CollisionRegion();
        ~CollisionRegion();

        PENJIN_ERRORS loadImage(CRstring image){if (map == NULL) map = new Image; return map->loadImageNoKey(image);}
        PENJIN_ERRORS loadImage(SDL_Surface *surface,CRuint xTiles,CRuint yTiles,CRuint skipTiles){if (map == NULL) map = new Image; return map->loadImageSheetNoKey(surface,xTiles,yTiles,skipTiles,1);}
        // deletes the image, but preserves the region, call resetHitRegion to delete that, too
        void freeImage(){if (map) { delete map; map = NULL; } }

        void setNoCollisionColour(const Colour& c){noCollision = c;}
        Colour getNoCollisionColour()const{return noCollision;}

        // generates a HitRegion from the loaded collision image
        // this will only work with images containing a single object (as only one region will be created)
        // and the region will be around the object (noCollision parts surrounded by collision parts will not be detected)
        void generateHitRegion();
        // deletes region, but does not touch the collision-image
        void resetHitRegion() {region.x = 0; region.y = 0; region.w = 0; region.h = 0; if (showRect) { delete showRect; showRect = NULL; }}

        // get position or size of the object, withRegion also takes the generated or set region into account
        // you should always use withRegion=true as the returned values will also be accurate on the absence of a collision-region
        int getX(CRbool withRegion=true) const {if (withRegion) return pos.x + region.x; else return pos.x;}
        int getY(CRbool withRegion=true) const {if (withRegion) return pos.y + region.y; else return pos.y;}
        int getWidth(CRbool withRegion=true) const {if (withRegion && region.w != 0) return region.w; else if (map != NULL) return map->getWidth(); else return 0;}
        int getHeight(CRbool withRegion=true) const {if (withRegion && region.h != 0) return region.h; else if (map != NULL) return map->getHeight(); else return 0;}

        // adjust the position (or size) to match the one of the sprite
        void setX(CRint value) {pos.x = value;}
        void setY(CRint value) {pos.y = value;}
        void setPosition(const Vector2di &value) {pos = value;}
        void setPosition(CRint x, CRint y) {pos = Vector2di(x,y);}
        void setWidth(CRint value) {region.w = value;}
        void setHeight(CRint value) {region.h = value;}
        void setSize(const Vector2di &value) {region.w = value.x; region.h = value.y;}
        void setSize(CRint w, CRint h) {region.w = w; region.h = h;}

        // debug render function, draws the loaded image (if any) and the outline of the region
        void render();

        // returns the colour of the collision image at position x,y or checks against the region if no image has been loaded
        // return noCollision if out of range
        Colour getCollisionType(int x, int y, CRbool absolute) const;

        // check whether a single point collides with the collisionRegion (always fullShape if possible)
        bool hitTest(int x, int y, CRbool absolute) const{return (getCollisionType(x,y,absolute) != noCollision);}
        // check whether another region collides with this region (rectangular or fullShape)
        // also works when one or both have no collision image or region loaded
        bool hitTest(const CollisionRegion* const region, CRbool fullShape=false) const;

    private:
        Image *map;
        Rectangle *showRect;
        Colour noCollision;
        Vector2di pos; // actual position of the collisionRegion

        struct RECT
        {
            int x, y, w, h;
        };

        RECT region; // x,y values are offset of the generated region and cannot be set by the user
};

#endif // COLLISIONREGION_H
