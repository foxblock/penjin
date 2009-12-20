#include "AchievementList.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementList::AchievementList() : Achievement()
{
    type = atRESET;
    showProgress = false;
    doneCount = 0;
}

AchievementList::~AchievementList()
{

}


///------------------------------
/// Public
///------------------------------
// the actual addEvent function, which all wrapper functions use
void AchievementList::addEventSpecial(CRstring name, const vector<SpecialProperty>& special, CRint count, CRint comparison, CRint action)
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

#ifdef PENJIN_SDL
void AchievementList::renderProgress(SDL_Surface* screen)
{
    if (showProgress)
    {
        if (not unlocked)
        {
            bgBox.setDimensions(round(size.x*float(doneCount)/limit),size.y);
            bgBox.setColour(Colour(160,160,160));
            bgBox.render(screen);

        }
        text.setBoundaries(Vector2di(position.x+size.y,position.y+round(0.7*size.y)),Vector2di(position.x+size.x-BORDER,position.y+size.y));
        text.setPosition(position.x+size.y,position.y+round(0.7*size.y));
        text.setAlignment(TextClass::RIGHT_JUSTIFIED);
        text.setFontSize(18);
        string temp = StringUtility::intToString(min(doneCount,limit))+"/"+StringUtility::intToString(limit);
        text.print(screen,temp);
    }
}
#else
void AchievementList::renderProgress()
{
    if (showProgress)
    {
        if (not unlocked)
        {
            bgBox.setDimensions(round(size.x*float(doneCount)/limit),size.y);
            bgBox.setColour(Colour(160,160,160));
            bgBox.render();

        }
        text.setBoundaries(Vector2di(position.x+size.y,position.y+round(0.7*size.y)),Vector2di(position.x+size.x-BORDER,position.y+size.y));
        text.setPosition(position.x+size.y,position.y+round(0.7*size.y));
        text.setAlignment(TextClass::RIGHT_JUSTIFIED);
        text.setFontSize(18);
        string temp = StringUtility::intToString(min(doneCount,limit))+"/"+StringUtility::intToString(limit);
        text.print(temp);
    }
}
#endif

///------------------------------
/// Private
///------------------------------

void AchievementList::changeCount(const vector<Event>& changeEvents)
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
                    ++doneCount;
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
    ++count;
    resetDone();
}

void AchievementList::resetDone()
{
    vector<Event>::const_iterator I;
    vector<bool>::iterator K = doneEvents.begin();
    for (I = events.begin(); I < events.end(); ++I)
    {
        if (I->action != acRESET && I->action != acDECREASE)
            *K = false;
        ++K;
    }
    doneCount = 0;
}
