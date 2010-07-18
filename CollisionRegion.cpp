#include "CollisionRegion.h"

#include "NumberUtility.h"

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
    delete map;
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

bool CollisionRegion::hitTest(const CollisionRegion* const tester, const Vector2df& posObj, const Vector2df& posTester, CRbool fullShape) const
{
    float objPosX = posObj.x + this->getRegionOffsetX();
    float objPosY = posObj.y + this->getRegionOffsetY();
    float testerPosX = posTester.x + tester->getRegionOffsetX();
    float testerPosY = posTester.y + tester->getRegionOffsetY();
    if (fullShape)
    {
        // determine overlaping area
        float xPos = max(objPosX, testerPosX);
        float yPos = max(objPosY, testerPosY);
        float xPosMax = min(objPosX + this->getWidth(), testerPosX + tester->getWidth());
        float yPosMax = min(objPosY + this->getHeight(), testerPosY + tester->getHeight());

        // check for collision
        for (float I = xPos; I <= xPosMax; ++I)
        {
            for (float K = yPos; K < yPosMax; ++K)
            {
                // if both have a collision-pixel at the same spot, we have a collision
                if (this->hitTest(I - posObj.x,K - posObj.y,false) && tester->hitTest(I - posTester.x,K - posTester.y,false))
                    return true;
            }
        }
        return false;
    }
    else
    {
        // check rectangular bounds only
        if (((testerPosX - objPosX) < this->getWidth() && (objPosX - testerPosX) < tester->getWidth()) &&
            ((testerPosY - objPosY) < this->getHeight() && (objPosY - testerPosY) < tester->getHeight())) return true;

        return false;
    }
}

Directions CollisionRegion::directionTest(const CollisionRegion* const tester, CRbool fullShape) const
{
    // check for collision first
    if (not hitTest(tester,fullShape))
    {
        return diNONE;
    }
    // now check collision direction, by a simple check of the overlaping area
    else
    {
        // calculate overlaping pixels
        float diffX = min(this->getX() + this->getWidth(), tester->getX() + tester->getWidth()) - max(this->getX(), tester->getX());
        float diffY = min(this->getY() + this->getHeight(), tester->getY() + tester->getHeight()) - max(this->getY(), tester->getY());

        // check which side overlaps more (relatively)
        if (diffX / min(this->getWidth(),tester->getWidth()) > diffY / min(this->getHeight(),tester->getHeight()))
        {
            // more X -> top/bottom collision
            if ((this->getY() + this->getHeight()/2) > (tester->getY() + tester->getHeight()/2))
                return diTOP;
            else
                return diBOTTOM;
        }
        else
        {
            // more Y -> left/right collision
            if ((this->getX() + this->getWidth()/2) > (tester->getX() + tester->getWidth()/2))
                return diLEFT;
            else
                return diRIGHT;
        }
    }
}

Directions CollisionRegion::directionTest(const CollisionRegion* const tester, const Vector2df& posObj, const Vector2df& posTester, CRbool fullShape) const
{
    // check for collision first
    if (not hitTest(tester,posObj,posTester,fullShape))
    {
        return diNONE;
    }
    // now check collision direction, by a simple check of the overlaping area
    else
    {
        float objPosX = posObj.x + this->getRegionOffsetX();
        float objPosY = posObj.y + this->getRegionOffsetY();
        float testerPosX = posTester.x + tester->getRegionOffsetX();
        float testerPosY = posTester.y + tester->getRegionOffsetY();

        // calculate overlaping pixels
        float diffX = min(objPosX + this->getWidth(), testerPosX + tester->getWidth()) - max(objPosX, testerPosX);
        float diffY = min(objPosY + this->getHeight(), testerPosY + tester->getHeight()) - max(objPosY, testerPosY);

        // check which side overlaps more (relatively)
        if (diffX / min(this->getWidth(),tester->getWidth()) > diffY / min(this->getHeight(),tester->getHeight()))
        {
            // more X -> top/bottom collision
            if ((objPosY + this->getHeight()/2) > (testerPosY + tester->getHeight()/2))
                return diTOP;
            else
                return diBOTTOM;
        }
        else
        {
            // more Y -> left/right collision
            if ((objPosX + this->getWidth()/2) > (testerPosX + tester->getWidth()/2))
                return diLEFT;
            else
                return diRIGHT;
        }
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
