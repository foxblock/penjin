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
    m_Region.w = width;
    m_Region.h = height;
}
void HitRegion::move(int x, int y)
{
    m_Region.x += x;
    m_Region.y += y;
}
void HitRegion::moveTo(int x, int y)
{
    m_Region.x = x;
    m_Region.y = y;
}

#ifdef PENJIN_SDL
    void HitRegion::render(SDL_Surface* screen)
    {
        Rectangle box;

        box.init();
        box.setPosition(m_Region.x, m_Region.y);
        box.setDimensions(m_Region.w, m_Region.h);
        box.setColour(RED);
        box.render(screen);
    }
#endif
void HitRegion::render()
{
    Rectangle box;

    box.init();
    box.setPosition(m_Region.x, m_Region.y);
    box.setDimensions(m_Region.w, m_Region.h);
    box.setColour(RED);
    box.render();
}
bool HitRegion::hitTest(HitRegion region)
{
    if(((region.getX() - m_Region.x) < m_Region.w && (m_Region.x - region.getX()) < region.getWidth()) &&
       ((region.getY() - m_Region.y) < m_Region.h && (m_Region.y - region.getY()) < region.getHeight())) return true;

    return false;
}
bool HitRegion::hitTest(HitRegion* region)
{
    if(((region->getX() - m_Region.x) < m_Region.w && (m_Region.x - region->getX()) < region->getWidth()) &&
       ((region->getY() - m_Region.y) < m_Region.h && (m_Region.y - region->getY()) < region->getHeight())) return true;

    return false;
}
bool HitRegion::hitTest(CollisionMap* map)
{
    for(int xpos = m_Region.x; xpos <= m_Region.x + m_Region.w; xpos += 1)
    {
        for(int ypos = m_Region.y; ypos <= m_Region.y + m_Region.h; ypos += 1)
        {
            if(map->hasCollided(xpos, ypos)) return true;
        }
    }

    return false;
}
Colour HitRegion::colourTest(CollisionMap* map)
{
    return map->getCollisionType(m_Region.x + (m_Region.w / 2), m_Region.y + (m_Region.h / 2));
}
Colour HitRegion::colourTest(CollisionMap* map, int x, int y)
{
    int xpos = min(m_Region.w - 1, x);

    int ypos = min(m_Region.h - 1, y);

    return map->getCollisionType(m_Region.x + xpos, m_Region.y + ypos);
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
