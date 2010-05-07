#include "AchievementTime.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementTime::AchievementTime() : Achievement()
{
    type = atTIME;
    showProgress = false;
}

///------------------------------
/// Public
///------------------------------

// the actual addEvent function, which all wrapper functions use
void AchievementTime::addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count, CRint comparison, CRint action)
{
    // check whether event was already added to prevent duplicates
    Event* ev = new Event(name,special,count,comparison,action);
	if (not ev->isEvent(events))
	{
		events.push_back(ev);
		doneEvents.push_back(false);
	}
    else
    {
        delete ev;
    #ifdef _DEBUG
        cout << "[Achievements] Error: Duplicate event " << name << " on achievement " << this->name << " - ignored!" << endl;
    #endif
    }
}

///------------------------------
/// Private
///------------------------------

void AchievementTime::changeCount(const vector<Event*>& changeEvents)
{
    if (not counter.isStarted())
        counter.start();

    vector<Event*>::const_iterator I;
    for (I = changeEvents.begin(); I < changeEvents.end(); ++I)
    {
        vector<Event*>::const_iterator K;
        vector<bool>::iterator L = doneEvents.begin();
        for (K = events.begin(); K < events.end(); ++K)
        {
            if ((*K)->name == (*I)->name)
                *L = true;
            ++L;
        }
    }

    bool done = true;
    vector<bool>::iterator K;
    for (K = doneEvents.begin(); K < doneEvents.end(); ++K)
        if (*K == false)
            done = false;
    if (done)
        count++;

    if (counter.hasFinished() || done)
    {
        counter.stop();
        vector<bool>::iterator L;
        for (L = doneEvents.begin(); L < doneEvents.end(); ++L)
            *K = false;
    }
}

