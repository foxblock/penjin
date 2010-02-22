#ifndef USERSTATES_H
#define USERSTATES_H
/*
Modify this file to tailor the states needed by your specific game.
STATE_NULL is vital to the operation of this state system, you are strongly advised not to remove it from the
BaseState class.

STATE_TITLE is considered the default state, so you are strongly advised to leave this in this file also.

NOTE: Be sure to #include ALL state headers which correspond to these modes.
*/

//	STATE_NULL		//	Exit the program, this is defined in the BaseState
//	STATE_BASE		//	Template state, does nothing particularly useful
enum STATE_MODES
{
	STATE_TITLE = 2,
    STATE_ANIMATION,
    STATE_COLOUR,
    STATE_PRIMITIVE,
    STATE_RAYCAST,
    STATE_FILE_LIST,
    STATE_ROTATION
};
#include "StateTitle.h"
#include "StateAnimation.h" //  Animation testing suite.
#include "StateColour.h"    //  Colour class tests
#include "StatePrimitive.h" //  Primitive tests.
#include "StateRaycast.h"   //  Raycaster
#include "StateFileList.h"  //  File lister
#include "StateRotation.h"  //  Rotations tester

#endif	//	USERSTATES_H
