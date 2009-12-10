#include "AchievementBoolean.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementBoolean::AchievementBoolean() : Achievement()
{
    type = atBOOLEAN;
}

AchievementBoolean::~AchievementBoolean()
{

}

///------------------------------
/// Public
///------------------------------


///------------------------------
/// Private
///------------------------------

void AchievementBoolean::changeCount(const vector<Event>& changeEvents)
{
    if (changeEvents.size() == events.size())
        count++;
}
