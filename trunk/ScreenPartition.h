#ifndef SCREENPARTITION_H
#define SCREENPARTITION_H

#include "PenjinTypes.h"

/*
ABOUT:  Takes a screen, splitting it into quadrants
        This can be used to sort game objects, to minimise collision checks
*/

enum partitions
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	UNKNOWN_PARTITION
};

class ScreenPartition
{
    public:
        ScreenPartition();
        ~ScreenPartition();

        //	Set the middle of the screen
        void setPartition(const Vector2di& midPoint);

        //	check which partition the position is in
        uint getPartition(const Vector2di& position);
        uint getPartition(CRint x,CRint y);
        uint getPartition(const Vector2dx& position){return getPartition(position.x.intValue >> 16,position.y.intValue >> 16);};
    private:
        Vector2di midPoint;
};
#endif	//	SCREENPARTITION_H

