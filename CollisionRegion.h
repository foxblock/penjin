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
#include "Rectangle.h"
#include "Vector2df.h"
#include "SimpleDirection.h"

class CollisionRegion
{
public:
    CollisionRegion();
    ~CollisionRegion();


    PENJIN_ERRORS loadImage(CRstring image)
    {
        createMap();
        return map->loadImageNoKey(image);
    }

    PENJIN_ERRORS loadImage(CRstring image,CRuint xTiles,CRuint yTiles)
    {
        createMap();
        return map->loadImageSheetNoKey(image,xTiles,yTiles);
    }

    PENJIN_ERRORS loadImage(SDL_Surface *surface,CRuint xTiles,CRuint yTiles,CRuint skipTiles)
    {
        createMap();
        return map->loadImageSheetNoKey(surface,xTiles,yTiles,skipTiles,1);
    }
    // deletes the image, but preserves the region, call resetHitRegion to delete that, too
    void freeImage()
    {
        delete map;
        map = NULL;
    }

    void setNoCollisionColour(const Colour& c)
    {
        noCollision = c;
    }
    Colour getNoCollisionColour()const
    {
        return noCollision;
    }

    // generates a HitRegion from the loaded collision image
    // this will only work with images containing a single object (as only one region will be created)
    // and the region will be around the object (noCollision parts surrounded by collision parts will not be detected)
    void generateHitRegion();
    // deletes region, but does not touch the collision-image
    void resetHitRegion()
    {
        region.x = 0;
        region.y = 0;
        region.w = 0;
        region.h = 0;
        delete showRect;
        showRect = NULL;
    }

    // Functions to check whether the CollisionRegion has an image or a region
    bool hasImage() const
    {
        return (map != NULL);
    }
    bool hasRegion() const
    {
        return (region.w != 0 || region.h != 0);
    }

    // get position or size of the object, withRegion also takes the generated or set region into account
    // you should always use withRegion=true as the returned values will also be accurate on the absence of a collision-region
    float getX(CRbool withRegion=true) const
    {
        if (withRegion)
            return pos.x + region.x;
        else return pos.x;
    }
    float getY(CRbool withRegion=true) const
    {
        if (withRegion)
            return pos.y + region.y;
        else return pos.y;
    }
    Vector2df getPosition(CRbool withRegion=true) const
    {
        if (withRegion)
            return (pos + Vector2df(region.x,region.y));
        else return pos;
    }
    float getWidth(CRbool withRegion=true) const
    {
        if (withRegion && region.w != 0)
            return region.w;
        else if (map != NULL)
            return map->getWidth();
        else
            return 0;
    }
    float getHeight(CRbool withRegion=true) const
    {
        if (withRegion && region.h != 0)
            return region.h;
        else if (map != NULL)
            return map->getHeight();
        else
            return 0;
    }
    Vector2df getRegionOffset() const
    {
        return Vector2df(region.x,region.y);
    }
    float getRegionOffsetX() const
    {
        return region.x;
    }
    float getRegionOffsetY() const
    {
        return region.y;
    }

    // adjust the position (or size) to match the one of the sprite
    void setX(CRfloat value)
    {
        pos.x = value;
    }
    void incX(CRfloat value)
    {
        pos.x += value;
    }
    void setY(CRfloat value)
    {
        pos.y = value;
    }
    void incY(CRfloat value)
    {
        pos.y += value;
    }
    void setPosition(const Vector2df &value)
    {
        pos = value;
    }
    void setPosition(CRfloat x, CRfloat y)
    {
        pos = Vector2di(x,y);
    }
    void incPosition(const Vector2df &value)
    {
        pos += value;
    }
    void setWidth(CRfloat value)
    {
        region.w = value;
    }
    void setHeight(CRfloat value)
    {
        region.h = value;
    }
    void setSize(const Vector2df &value)
    {
        region.w = value.x;
        region.h = value.y;
    }
    void setSize(CRfloat w, CRfloat h)
    {
        region.w = w;
        region.h = h;
    }

    // debug render function, draws the loaded image (if any) and the outline of the region
    void render() {render(GFX::getVideoSurface());} // to main surface (aka screen)
    void render(SDL_Surface* surf); // to another surface

    // returns the colour of the collision image at position x,y or checks against the region if no image has been loaded
    // absulute = true - the passed point is relative to the logic zero-point (for example the top-left corner of the screen)
    // absolute = false - the passed point is relative to the position of the collisionRegion, so (0,0) will reference to the top-left corner of the region
    // returns noCollision if out of range
    Colour getCollisionType(float x, float y, CRbool absolute) const;

    // check whether a single point collides with the collisionRegion (always fullShape if possible)
    // absolute - see above
    bool hitTest(float x, float y, CRbool absolute) const
    {
        return (getCollisionType(x,y,absolute) != noCollision);
    }
    // check whether another region collides with this region (rectangular or fullShape)
    // also works when one or both have no collision image or region loaded
    bool hitTest(const CollisionRegion* const tester, CRbool fullShape=false) const;
    // use external positioning
    bool hitTest(const CollisionRegion* const tester, const Vector2df& PosObj, const Vector2df& PosTester, CRbool fullShape=false) const;
    // performs a hitTest first and a (rectangular) check for direction afterwards
    // returns the result of that check (only 4 base directions, no corners, viewed from this object)
    // might fail on extreme shapes (e.g. very tall and very thin)
    SimpleDirection directionTest(const CollisionRegion* const tester, CRbool fullShape=false) const;
    // use external positioning
    SimpleDirection directionTest(const CollisionRegion* const tester, const Vector2df& posObj, const Vector2df& posTester, CRbool fullShape=false) const;

private:
    void createMap()
    {
        if (map == NULL)
            map = new Image;
    }
    Image *map;
    Rectangle *showRect;
    Colour noCollision;
    Vector2df pos; // actual position of the collisionRegion

    struct RECT
    {
        float x, y, w, h;
    };

    RECT region; // x,y values are offset of the generated region and cannot be set by the user
};

#endif // COLLISIONREGION_H
