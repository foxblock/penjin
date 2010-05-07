#include "AchievementList.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementList::AchievementList() : Achievement()
{
    type = atRESET;
    showProgress = false;
    doneCount = 0;
    eCount = 0;
}


///------------------------------
/// Public
///------------------------------
// the actual addEvent function, which all wrapper functions use
void AchievementList::addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count, CRint comparison, CRint action)
{
    // check whether event was already added to prevent duplicates
    Event* ev = new Event(name,special,count,comparison,action);
	if (not ev->isEvent(events))
	{
		events.push_back(ev);
		if (action == acRESET || action == acDECREASE)
            doneEvents.push_back(true);
        else
        {
            doneEvents.push_back(false);
            ++eCount;
        }
	}
    else
    {
        delete ev;
    #ifdef _DEBUG
        cout << "[Achievements] Error: Duplicate event " << name << " on achievement " << this->name << " - ignored!" << endl;
    #endif
    }

}

void AchievementList::setTimeLimit(CRint value)
{
    #ifdef _DEBUG
    cout << "[Achievements] Error: AchievementList does not use a timer ( " << this->name << ")!" << endl;
    #endif
}

#ifdef PENJIN_SDL
void AchievementList::renderProgress(SDL_Surface* screen)
{
    int useCount = count;
    int useLimit = limit;
    if (limit == 1)
    {
        useCount = doneCount;
        useLimit = eCount;
    }

    if (showProgress)
    {
        if (not unlocked)
        {
            bgBox.setDimensions(round(size.x*float(useCount)/useLimit),size.y);
            bgBox.setColour(Colour(160,160,160));
            bgBox.render(screen);

        }
        text.setBoundaries(Vector2di(position.x+size.y,position.y+round(0.7*size.y)),Vector2di(position.x+size.x-BORDER,position.y+size.y));
        text.setPosition(position.x+size.y,position.y+round(0.7*size.y));
        text.setAlignment(TextClass::RIGHT_JUSTIFIED);
        text.setFontSize(18);
        string temp = StringUtility::intToString(min(useCount,useLimit))+"/"+StringUtility::intToString(useLimit);
        text.print(screen,temp);
    }
}
#else
void AchievementList::renderProgress()
{
    int useCount = count;
    int useLimit = limit;
    if (limit == 1)
    {
        useCount = doneCount;
        useLimit = eCount;
    }

    if (showProgress)
    {
        if (not unlocked)
        {
            bgBox.setDimensions(round(size.x*float(useCount)/useLimit),size.y);
            bgBox.setColour(Colour(160,160,160));
            bgBox.render();

        }
        text.setBoundaries(Vector2di(position.x+size.y,position.y+round(0.7*size.y)),Vector2di(position.x+size.x-BORDER,position.y+size.y));
        text.setPosition(position.x+size.y,position.y+round(0.7*size.y));
        text.setAlignment(TextClass::RIGHT_JUSTIFIED);
        text.setFontSize(18);
        string temp = StringUtility::intToString(min(useCount,useLimit))+"/"+StringUtility::intToString(useLimit);
        text.print(temp);
    }
}
#endif

///------------------------------
/// Private
///------------------------------

void AchievementList::changeCount(const vector<Event*>& changeEvents)
{
    vector<Event*>::const_iterator I;
    for (I = changeEvents.begin(); I < changeEvents.end(); ++I)
    {
        vector<Event*>::const_iterator K;
        vector<bool>::iterator L = doneEvents.begin();
        for (K = events.begin(); K < events.end(); ++K)
        {
            if ((*K)->name == (*I)->name && (*K)->checkSpecial((*I)->special))
            {
                if ((*I)->action == acRESET || (*I)->action == acDECREASE)
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

    if (doneCount >= eCount)
    {
        ++count;
        resetDone();
    }
}

void AchievementList::resetDone()
{
    vector<Event*>::const_iterator I;
    vector<bool>::iterator K = doneEvents.begin();
    for (I = events.begin(); I < events.end(); ++I)
    {
        if ((*I)->action != acRESET && (*I)->action != acDECREASE)
            *K = false;
        ++K;
    }
    doneCount = 0;
}
