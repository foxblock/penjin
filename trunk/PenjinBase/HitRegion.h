//-----------------------------------------------------
// Defines
//-----------------------------------------------------
#ifndef HitRegion_H
#define HitRegion_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Sprite.h"
#include "Rectangle.h"
#include "CollisionMap.h"

struct RECT
{
    int x, y, w, h;
};
//-----------------------------------------------------
// HitRegion Class
//-----------------------------------------------------
class HitRegion
{
public:
    HitRegion();   //Constructor
    virtual ~HitRegion();  //Destructor

	//-------------------------------------------------
	// Public Methods
	//-------------------------------------------------
    void init(int x, int y, int width, int height);
    void render(SDL_Surface* screen);

    void move(int x, int y);
    void moveTo(int x, int y);

    bool hitTest(HitRegion region);
    bool hitTest(HitRegion* region);
    bool hitTest(CollisionMap* map);

private:
	//-------------------------------------------------
	// Private Methods
	//-------------------------------------------------
    int getX();
    int getY();
    int getWidth();
    int getHeight();

	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
    RECT m_Region;
};

//-----------------------------------------------------
// POINT Struct
//-----------------------------------------------------
struct POINT
{
    int x, y;
};

#endif // HitRegion_H
