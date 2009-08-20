//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "HitRegion.h"

//-----------------------------------------------------
// Constructor & Destructor
//-----------------------------------------------------
HitRegion::HitRegion()
{
    m_Region.x = 0;
    m_Region.y = 0;
    m_Region.w = 0;
    m_Region.h = 0;
}
HitRegion::~HitRegion()
{

}
//-----------------------------------------------------
// Methodes
//-----------------------------------------------------
void HitRegion::init(int x, int y, int width, int height)
{
    m_Region.x = x;
    m_Region.y = y;
    m_Region.w = m_Region.x + width;
    m_Region.h = m_Region.y + height;
}
void HitRegion::move(int x, int y)
{
    m_Region.x += x;
    m_Region.y += y;
    m_Region.w += x;
    m_Region.h += y;
}
void HitRegion::moveTo(int x, int y)
{
    m_Region.w = m_Region.w - m_Region.x + x;
    m_Region.h = m_Region.h - m_Region.y + y;
    m_Region.x = x;
    m_Region.y = y;
}
void HitRegion::render(SDL_Surface* screen)
{
    Rectangle box;

    box.init();
    box.setPosition(m_Region.x, m_Region.y);
    box.setDimensions(m_Region.w - m_Region.x, m_Region.h - m_Region.y);
    box.setColour(RED);
    box.render(screen);
}
bool HitRegion::hitTest(HitRegion region)
{
    bool result;
    //------------------------------------------------
    // Making 8 points marking the pos of the rects
    //------------------------------------------------

    //This rect
    POINT upleft1, upright1, downleft1, downright1, center1;

    upleft1.x = m_Region.x;
    upleft1.y = m_Region.y;

    upright1.x = m_Region.w;
    upright1.y = m_Region.y;

    downleft1.x = m_Region.x;
    downleft1.y = m_Region.h;

    downright1.x = m_Region.w;
    downright1.y = m_Region.h;

    center1.x = (m_Region.x + m_Region.w) / 2;
    center1.y = (m_Region.y + m_Region.h) / 2;

    //the other rect
    POINT upleft2, upright2, downleft2, downright2, center2;

    upleft2.x = region.getX();
    upleft2.y = region.getY();

    upright2.x = region.getWidth();
    upright2.y = region.getY();

    downleft2.x = region.getX();
    downleft2.y = region.getHeight();

    downright2.x = region.getWidth();
    downright2.y = region.getHeight();

    center2.x = (region.getX() + region.getWidth()) / 2;
    center2.y = (region.getY() + region.getHeight()) / 2;

    //------------------------------------------------
    // Checking for a hit and returning the result
    //------------------------------------------------

    if(upleft1.x >= upleft2.x && upleft1.y >= upleft2.y && upleft1.x <= downright2.x && upleft1.y <= downright2.y) result = true;
    else if(upright1.x >= upleft2.x && upright1.y >= upleft2.y && upright1.x <= downright2.x && upright1.y <= downright2.y) result = true;
    else if(downleft1.x >= upleft2.x && downleft1.y >= upleft2.y && downleft1.x <= downright2.x && downleft1.y <= downright2.y) result = true;
    else if(downright1.x >= upleft2.x && downright1.y >= upleft2.y && downright1.x <= downright2.x && downright1.y <= downright2.y) result = true;
    else if(center1.x >= upleft2.x && center1.y >= upleft2.y && center1.x <= downright2.x && center1.y <= downright2.y) result = true;

    else if(upleft2.x >= upleft1.x && upleft2.y >= upleft1.y && upleft2.x <= downright1.x && upleft2.y <= downright1.y) result = true;
    else if(upright2.x >= upleft1.x && upright2.y >= upleft1.y && upright2.x <= downright1.x && upright2.y <= downright1.y) result = true;
    else if(downleft2.x >= upleft1.x && downleft2.y >= upleft1.y && downleft2.x <= downright1.x && downleft2.y <= downright1.y) result = true;
    else if(downright2.x >= upleft1.x && downright2.y >= upleft1.y && downright2.x <= downright1.x && downright2.y <= downright1.y) result = true;
    else if(center2.x >= upleft1.x && center2.y >= upleft1.y && center2.x <= downright1.x && center2.y <= downright1.y) result = true;

    else result = false;

    return result;
}
bool HitRegion::hitTest(HitRegion* region)
{
    bool result;
    //------------------------------------------------
    // Making 8 points marking the pos of the rects
    //------------------------------------------------

    //This rect
    POINT upleft1, upright1, downleft1, downright1, center1;

    upleft1.x = m_Region.x;
    upleft1.y = m_Region.y;

    upright1.x = m_Region.w;
    upright1.y = m_Region.y;

    downleft1.x = m_Region.x;
    downleft1.y = m_Region.h;

    downright1.x = m_Region.w;
    downright1.y = m_Region.h;

    center1.x = (m_Region.x + m_Region.w) / 2;
    center1.y = (m_Region.y + m_Region.h) / 2;

    //the other rect
    POINT upleft2, upright2, downleft2, downright2, center2;

    upleft2.x = region->getX();
    upleft2.y = region->getY();

    upright2.x = region->getWidth();
    upright2.y = region->getY();

    downleft2.x = region->getX();
    downleft2.y = region->getHeight();

    downright2.x = region->getWidth();
    downright2.y = region->getHeight();

    center2.x = (m_Region.x + m_Region.w) / 2;
    center2.y = (m_Region.y + m_Region.h) / 2;

    //------------------------------------------------
    // Checking for a hit and returning the result
    //------------------------------------------------

    if(upleft1.x >= upleft2.x && upleft1.y >= upleft2.y && upleft1.x <= downright2.x && upleft1.y <= downright2.y) result = true;
    else if(upright1.x >= upleft2.x && upright1.y >= upleft2.y && upright1.x <= downright2.x && upright1.y <= downright2.y) result = true;
    else if(downleft1.x >= upleft2.x && downleft1.y >= upleft2.y && downleft1.x <= downright2.x && downleft1.y <= downright2.y) result = true;
    else if(downright1.x >= upleft2.x && downright1.y >= upleft2.y && downright1.x <= downright2.x && downright1.y <= downright2.y) result = true;
    else if(center1.x >= upleft2.x && center1.y >= upleft2.y && center1.x <= downright2.x && center1.y <= downright2.y) result = true;

    else if(upleft2.x >= upleft1.x && upleft2.y >= upleft1.y && upleft2.x <= downright1.x && upleft2.y <= downright1.y) result = true;
    else if(upright2.x >= upleft1.x && upright2.y >= upleft1.y && upright2.x <= downright1.x && upright2.y <= downright1.y) result = true;
    else if(downleft2.x >= upleft1.x && downleft2.y >= upleft1.y && downleft2.x <= downright1.x && downleft2.y <= downright1.y) result = true;
    else if(downright2.x >= upleft1.x && downright2.y >= upleft1.y && downright2.x <= downright1.x && downright2.y <= downright1.y) result = true;

    else result = false;

    return result;
}
bool HitRegion::hitTest(CollisionMap* map)
{
    for(int xpos = m_Region.x; xpos <= m_Region.w; xpos += 1)
    {
        for(int ypos = m_Region.y; ypos <= m_Region.h; ypos += 1)
        {
            if(map->hasCollided(xpos, ypos)) return true;
        }
    }

    return false;
}
int HitRegion::getX()
{
    return m_Region.x;
}
int HitRegion::getY()
{
    return m_Region.y;
}
int HitRegion::getWidth()
{
    return m_Region.w;
}
int HitRegion::getHeight()
{
    return m_Region.h;
}
