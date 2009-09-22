#include "ScreenPartition.h"

ScreenPartition::ScreenPartition()
{
	//	TOP_LEFT
	setPartition(Vector2di(160,120));
}

ScreenPartition::~ScreenPartition()
{
}

uint ScreenPartition::getPartition(CRint x,CRint y)
{
	//	Work out if the point is on the left or right of the screen first
	if(x < midPoint.x)
	{
		//	Left hand side of screen
		//	Now check if it is up or down
		if(y < midPoint.y)
			return TOP_LEFT;

		return BOTTOM_LEFT;
	}
	else
	{
		//	Right hand side of screen
		//	Now check if it is up or down
		if(y > midPoint.y)
			return BOTTOM_RIGHT;

		return TOP_RIGHT;
	}
}

uint ScreenPartition::getPartition(const Vector2di& position)
{
	return getPartition(position.x,position.y);
}

void ScreenPartition::setPartition(const Vector2di& midPoint)
{
	this->midPoint = midPoint;
}
