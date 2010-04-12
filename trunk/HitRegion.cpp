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
    box.setColour(RED);
    box.setThickness(1);
}
HitRegion::~HitRegion()
{

}
//-----------------------------------------------------
// Methodes
//-----------------------------------------------------
void HitRegion::init(CRint x, CRint y, CRint width, CRint height)
{
    m_Region.x = x;
    m_Region.y = y;
    m_Region.w = width;
    m_Region.h = height;
    box.setPosition(x,y);
    box.setDimensions(width,height);
}
void HitRegion::move(CRint x, CRint y)
{
    m_Region.x += x;
    m_Region.y += y;
    box.setPosition(x,y);
}
void HitRegion::moveTo(CRint x, CRint y)
{
    m_Region.x = x;
    m_Region.y = y;
    box.setPosition(x,y);
}

#ifdef PENJIN_SDL
    void HitRegion::render(SDL_Surface* screen)
    {
        box.render(screen);
    }
#endif
void HitRegion::render()
{
    box.render();
}
bool HitRegion::hitTest(const HitRegion* const region) const
{
    if(((region->getX() - m_Region.x) < m_Region.w && (m_Region.x - region->getX()) < region->getWidth()) &&
       ((region->getY() - m_Region.y) < m_Region.h && (m_Region.y - region->getY()) < region->getHeight())) return true;

    return false;
}

bool HitRegion::hitTest(CollisionMap* const map, CRint x, CRint y)const
{
    for(int xpos = m_Region.x - x; xpos <= m_Region.x - x + m_Region.w; ++xpos)
    {
        for(int ypos = m_Region.y - y; ypos <= m_Region.y - y + m_Region.h; ++ypos)
        {
            if(map->getCollisionType(xpos, ypos) == BLACK) return true;
        }
    }

    return false;
}
Colour HitRegion::colourTest(CollisionMap* const map) const
{
    return map->getCollisionType(m_Region.x + (m_Region.w / 2), m_Region.y + (m_Region.h / 2));
}
Colour HitRegion::colourTest(CollisionMap* const map, CRint x, CRint y)const
{
    int xpos = min(m_Region.w - 1, x);

    int ypos = min(m_Region.h - 1, y);

    return map->getCollisionType(m_Region.x + xpos, m_Region.y + ypos);
}
int HitRegion::getX() const
{
    return m_Region.x;
}
int HitRegion::getY() const
{
    return m_Region.y;
}
int HitRegion::getWidth() const
{
    return m_Region.w;
}
int HitRegion::getHeight() const
{
    return m_Region.h;
}
