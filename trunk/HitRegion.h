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

// RECT Struct
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
    #ifdef PENJIN_SDL
        void render(SDL_Surface* screen);
    #endif
    void render();

    void move(int x, int y);
    void moveTo(int x, int y);

    bool hitTest(HitRegion region);
    bool hitTest(HitRegion* region);
    bool hitTest(CollisionMap* map);
    Colour colourTest(CollisionMap* map);
    Colour colourTest(CollisionMap* map, int x, int y);

    int getX();
    int getY();
    int getWidth();
    int getHeight();

private:
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
    RECT m_Region;
    Rectangle box;
};

#endif // HitRegion_H
