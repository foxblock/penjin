#include "AchievementCount.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementCount::AchievementCount() : Achievement()
{
    type = atCOUNT;
}

AchievementCount::~AchievementCount()
{

}


///------------------------------
/// Public
///------------------------------

// the actual addEvent function, which all wrapper functions use
void AchievementCount::addEventSpecial(CRstring name, const vector<SpecialProperty>& special, CRint count, CRint comparison, CRint action)
{
    // check whether event was already added to prevent duplicates
	if (events.size() == 0)
	{
	    Event ev = {name,special,count,comparison,action};
		events.push_back(ev);
	}
    #ifdef _DEBUG
	else
        cout << "[Achievements] Error: Can't add multiple events to an AchievementCount (" << name << ")" << endl;
	#endif
}


///------------------------------
/// Private
///------------------------------

void AchievementCount::changeCount(const vector<Event>& changeEvents)
{
    vector<Event>::const_iterator I;

    // go through events and change count accordingly
    for (I = changeEvents.begin(); I < changeEvents.end(); I++)
    {
        count += I->count;
    }
}

