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
    // reset counter
    if (counter.getLimit() > 0)
    {
        if (not counter.isStarted())
            counter.start();
        else if (counter.hasFinished())
        {
            counter.start();
            count = 0;
        }
    }

    if (changeEvents.size() == events.size())
        count++;
}
