#include "CollisionRegion.h"

CollisionRegion::CollisionRegion()
{
    //ctor
    noCollision = WHITE;
    map = NULL;
    showRect = NULL;
    region.x = 0;
    region.y = 0;
    region.w = 0;
    region.h = 0;
    pos = Vector2di(0,0);
}

CollisionRegion::~CollisionRegion()
{
    if (map)
        delete map;
    if (showRect)
        delete showRect;
}

void CollisionRegion::generateHitRegion()
{
    if (map == NULL)
        return;

    float x,y,w,h;
    w = h = 0;
    x = map->getWidth();
    y = map->getHeight();
    // starting on the bottom left, go to the top right of the image
    // determines the smallest bounding box aroudn the colliding object
    for (float I = map->getWidth()-1; I >= 0; --I)
    {
        for (float K = map->getHeight()-1; K >= 0; --K)
        {
            if (map->getPixel(I,K) != noCollision)
            {
                w = max(w,I);
                h = max(h,K);
                x = min(x,I);
                y = min(y,K);
            }
        }
    }
    region.x = x;
    region.y = y;
    region.w = w-x+1;
    region.h = h-y+1;
}

Colour CollisionRegion::getCollisionType(float x, float y, CRbool absolute) const
{
    if (absolute)
    {
        x -= getX();
        y -= getY();
    }
    if (map == NULL)
    {
        // bounds check
        if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight())
            return noCollision;
        else
        {
            if (noCollision == Colour(WHITE))
                return BLACK;
            else
                return WHITE;
        }
    }
    else
    {
        // bounds check
        if(x < 0 || y < 0 || x >= getWidth() || y >= getHeight())
            return noCollision;

        return map->getPixel(x + region.x,y + region.y);
    }
}  //  check what sort of collision has been made.

bool CollisionRegion::hitTest(const CollisionRegion* const tester, CRbool fullShape) const
{
    if (fullShape)
    {
        // determine overlaping area
        float xPos = max(this->getX(), tester->getX());
        float yPos = max(this->getY(), tester->getY());
        float xPosMax = min(this->getX() + this->getWidth(), tester->getX() + tester->getWidth());
        float yPosMax = min(this->getY() + this->getHeight(), tester->getY() + tester->getHeight());

        // check for collision
        for (float I = xPos; I <= xPosMax; ++I)
        {
            for (float K = yPos; K < yPosMax; ++K)
            {
                // if both have a collision-pixel at the same spot, we have a collision
                if (this->hitTest(I,K,true) && tester->hitTest(I,K,true))
                    return true;
            }
        }
        return false;
    }
    else
    {
        // check rectangular bounds only
        if (((tester->getX() - this->getX()) < this->getWidth() && (this->getX() - tester->getX()) < tester->getWidth()) &&
            ((tester->getY() - this->getY()) < this->getHeight() && (this->getY() - tester->getY()) < tester->getHeight())) return true;

        return false;
    }
}

void  CollisionRegion::render()
{
    if (map)
    {
        map->renderImage(pos);
    }
    if (not showRect && region.w != 0 && region.h != 0)
    {
        showRect = new Rectangle(region.w,region.h);
        showRect->setColour(Colour(GREEN));
        showRect->setThickness(max(getWidth() / 100.0, 1.0));
    }
    if (showRect)
    {
        showRect->setDimensions(region.w,region.h);
        showRect->setPosition(pos.x + region.x,pos.y + region.y);
        showRect->render();
    }
}
