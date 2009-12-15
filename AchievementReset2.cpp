#include "AchievementReset2.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementReset2::AchievementReset2() : Achievement()
{
    type = atRESET;
}

AchievementReset2::~AchievementReset2()
{

}


///------------------------------
/// Public
///------------------------------
// the actual addEvent function, which all wrapper functions use
void AchievementReset2::addEventSpecial(CRstring name, const vector<SpecialProperty>& special, CRint count, CRint comparison, CRint action)
{
    // check whether event was already added to prevent duplicates
	if (not isEvent(name,events))
	{
	    Event ev = {name,special,count,comparison,action};
		events.push_back(ev);
		if (action == acRESET || action == acDECREASE)
            doneEvents.push_back(true);
        else
            doneEvents.push_back(false);
	}
    #ifdef _DEBUG
    else
        cout << "[Achievements] Error: Duplicate event " << name << " on achievement " << this->name << " - ignored!" << endl;
    #endif
}

///------------------------------
/// Private
///------------------------------

void AchievementReset2::changeCount(const vector<Event>& changeEvents)
{
    vector<Event>::const_iterator I;
    for (I = changeEvents.begin(); I < changeEvents.end(); ++I)
    {
        vector<Event>::const_iterator K;
        vector<bool>::iterator L = doneEvents.begin();
        for (K = events.begin(); K < events.end(); ++K)
        {
            if (K->name == I->name)
            {
                if (I->action == acRESET || I->action == acDECREASE)
                {
                    resetDone();
                    return;
                }
                else
                {
                    *L = true;
                }
            }
            ++L;
        }
    }

    vector<bool>::const_iterator K;
    for (K = doneEvents.begin(); K < doneEvents.end(); ++K)
    {
        if (*K == false)
            return;
    }
    count++;
    resetDone();
}

void AchievementReset2::resetDone()
{
    vector<Event>::const_iterator I;
    vector<bool>::iterator K = doneEvents.begin();
    for (I = events.begin(); I < events.end(); ++I)
    {
        if (I->action != acRESET && I->action != acDECREASE)
            *K = false;
        ++K;
    }
}
