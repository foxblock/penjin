//********************************************************************************//
// HitRegion class by Dragons_Slayer                                              //
// ---------------------------------											  //
//																				  //
//	Simple hit detection using rectangle shapes					            	  //
//	For more advanced collision see the CollisionRegion and CollisionMap class    //
//																				  //
//********************************************************************************//

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
struct HRECT
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
    void init(CRint x, CRint y, CRint width, CRint height);
    #ifdef PENJIN_SDL
        void render(SDL_Surface* screen);
    #endif
    void render();

    void move(CRint x, CRint y);
    void moveTo(CRint x, CRint y);

    bool hitTest(const HitRegion* const region) const;
    bool hitTest(CollisionMap* const map, CRint x, CRint y)const;
    Colour colourTest(CollisionMap* const map) const;
    Colour colourTest(CollisionMap* const map, CRint x, CRint y)const;

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

private:
	//-------------------------------------------------
	// Datamembers
	//-------------------------------------------------
    HRECT m_Region;
    Rectangle box;
};

#endif // HitRegion_H
