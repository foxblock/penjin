/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "AchievementList.h"
#include "AchievementSystem.h"

#define PARENT_SYSTEM ((AchievementSystem*)parent)

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

void AchievementList::load(CRstring value)
{
    if (showProgress)
    {
        for (uint I = 0; I < doneEvents.size() && I < value.length(); ++I)
        {
            bool temp = StringUtility::stringToBool(value.substr(I,1));
            doneEvents.at(I) = temp;
            if (temp)
                ++doneCount;
        }
        if (doneCount >= eCount)
            setCount(count + 1);
    }
    else
        setCount(StringUtility::stringToInt(value));
}

string AchievementList::save() const
{
    if (showProgress)
    {
        string result = "";
        vector<bool>::const_iterator I;
        for (I = doneEvents.begin(); I < doneEvents.end(); ++I)
            result += StringUtility::boolToString((*I),false);

        return result;
    }
    else
        return StringUtility::intToString(count);
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
            bgBox.setColour(PARENT_SYSTEM->getProgressColour());
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
            bgBox.setColour(PARENT_SYSTEM->getProgressColour());
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
                if ((*K)->action == acRESET || (*K)->action == acDECREASE)
                {
                    resetDone();
                    return;
                }
                else
                {
                    if ((*L) != true)
                    {
                        *L = true;
                        ++doneCount;
                    }
                }
            }
            ++L;
        }
    }

    if (doneCount >= eCount)
    {
        ++count;
        if (limit > 1)
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
