#include "AchievementCount.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementCount::AchievementCount() : Achievement()
{
    type = atCOUNT;
}

///------------------------------
/// Public
///------------------------------

// the actual addEvent function, which all wrapper functions use
void AchievementCount::addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count, CRint comparison, CRint action)
{
    // check whether event was already added to prevent duplicates
	if (events.size() == 0)
	{
	    Event* ev = new Event(name,special,count,comparison,action);
		events.push_back(ev);
	}
    #ifdef _DEBUG
	else
        cout << "[Achievements] Error: Can't add multiple events to an AchievementCount (" << this->name << ")" << endl;
	#endif

}


///------------------------------
/// Private
///------------------------------

void AchievementCount::changeCount(const vector<Event*>& changeEvents)
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

    vector<Event*>::const_iterator I;

    // go through events and change count accordingly
    for (I = changeEvents.begin(); I < changeEvents.end(); I++)
    {
        count += (*I)->count;
    }
}

