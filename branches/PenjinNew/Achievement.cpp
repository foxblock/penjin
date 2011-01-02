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
#include "Achievement.h"

#include "AchievementSystem.h"

#define PARENT_SYSTEM ((AchievementSystem*)parent)

///------------------------------
/// Constructor / Destructor
///------------------------------

Achievement::Achievement()
{
    count = 0;
    limit = 1;
    secret = false;
    unlocked = false;
    name = "Achievement Name";
    descr = "Achievement Description";
    type = atGENERAL;
    counter.setLimit(0);
    position = Vector2di(0,0);
    size = Vector2di(DEFAULT_WIDTH,DEFAULT_HEIGHT);

    showProgress = true;
    text.loadFont("font/modernaBold.ttf");
    text.setRelativity(true);
}

Achievement::~Achievement()
{
    vector<Event*>::iterator I;
    for (I = events.begin(); I < events.end(); ++I)
        delete (*I);
}


///------------------------------
/// Public
///------------------------------

bool Achievement::check(const vector<Event*>& checkEvents)
{
    vector<Event*> countEvents;
    vector<Event*>::const_iterator I;

    // go through the logged events and compare with achievements events
    for (I = checkEvents.begin(); I < checkEvents.end(); ++I)
    {
        vector<Event*>::const_iterator K;
        for (K = events.begin(); K < events.end(); ++K)
        {
            // comparison:
            if ((*K)->check((*I)))
            {
                // add necessary information to a temporary vector which will be passed to the changeCount function
                (*I)->action = (*K)->action;
                countEvents.push_back((*I));
            }
        }
    }

    // checks for count change
    if (countEvents.size() > 0)
        changeCount(countEvents);

    // returns true if achievemnt has been unlocked
    if (count >= limit && not unlocked)
    {
        counter.stop();
        unlocked = true;
        return true;
    }
    else
    {
        vector<int>::iterator I;
        for (I = milestones.begin(); I < milestones.end(); ++I)
        {
            if (*I <= count)
            {
                milestones.erase(I);
                return true;
            }
        }
        return false;
    }
}

// the actual addEvent function, which all wrapper functions use
void Achievement::addEventSpecial(CRstring name,vector<SpecialProperty>* special, CRint count, CRint comparison, CRint action)
{
    // check whether event was already added to prevent duplicates
    Event* ev = new Event(name,special,count,comparison,action);
	if (not ev->isEvent(events))
	{
		events.push_back(ev);
	}
    else
    {
        delete ev;
    #ifdef _DEBUG
        cout << "[Achievements] Error: Duplicate event " << name << " on achievement " << this->name << " - ignored!" << endl;
    #endif
    }
}

void Achievement::setCount(CRint value)
{
    count = value;


    vector<int>::iterator I;
    for (I = milestones.begin(); I < milestones.end(); ++I)
    {
        if ((*I) <= count)
        {
            milestones.erase(I);
            --I;
        }
    }

    if (count >= limit)
        unlocked = true;
}

void Achievement::setPosition(const Vector2di &newPos)
{
    position = newPos;
    bgBox.setPosition(newPos.x,newPos.y);
    icon.setPosition(newPos.x+5,newPos.y+5);
}

void Achievement::load(CRstring value)
{
    setCount(StringUtility::stringToInt(value));
}

string Achievement::save() const
{
    return StringUtility::intToString(count);
}


#ifdef PENJIN_SDL
void Achievement::render(SDL_Surface* screen)
{
    // background box
    if (unlocked)
    {
        bgBox.setColour(PARENT_SYSTEM->getProgressColour());
    }
    else
    {
        bgBox.setColour(PARENT_SYSTEM->getBackgroundColour());
    }
    bgBox.setDimensions(size.x,size.y);
    bgBox.render(screen);

    // progress background and text
    if (not secret || unlocked)
        renderProgress(screen);

    // text
    text.setBoundaries(Vector2di(position.x+size.y,position.y+BORDER),Vector2di(position.x+size.x-5,position.y+size.y-BORDER));
    text.setPosition(position.x+size.y,position.y+BORDER);
    text.setAlignment(TextClass::LEFT_JUSTIFIED);
    text.setFontSize(18);
    text.setColour(PARENT_SYSTEM->getHeadlineColour());
    if (secret && not unlocked)
    {
        text.print(screen,PARENT_SYSTEM->getSecretHeadline()+"\n");
        text.setFontSize(12);
        text.setColour(PARENT_SYSTEM->getFontColour());
        text.print(screen, PARENT_SYSTEM->getSecretDescription());
    }
    else
    {
        text.print(screen,name+"\n");
        string temp = descr;
        temp = StringUtility::substrReplace(temp,"%c",StringUtility::intToString(count));
        temp = StringUtility::substrReplace(temp,"%l",StringUtility::intToString(limit));
        text.setFontSize(12);
        text.setColour(PARENT_SYSTEM->getFontColour());
        text.print(screen,temp+"\n");
    }

    // icon
    if (unlocked)
        icon.setCurrentFrame(1);
    else
        icon.setCurrentFrame(0);
    icon.render(screen);
}

#else

void Achievement::render()
{
    // background box
    if (unlocked)
    {
        bgBox.setColour(PARENT_SYSTEM->getProgressColour());
    }
    else
    {
        bgBox.setColour(PARENT_SYSTEM->getBackgroundColour());
    }
    bgBox.setDimensions(size.x,size.y);
    bgBox.render();

    // progress background and text
    if (not secret || unlocked)
        renderProgress();

    // text
    text.setBoundaries(Vector2di(position.x+size.y,position.y+BORDER),Vector2di(position.x+size.x-5,position.y+size.y-BORDER));
    text.setPosition(position.x+size.y,position.y+BORDER);
    text.setAlignment(TextClass::LEFT_JUSTIFIED);
    text.setFontSize(18);
    text.setColour(PARENT_SYSTEM->getHeadlineColour());
    if (secret && not unlocked)
    {
        text.print(PARENT_SYSTEM->getSecretHeadline()+"\n");
        text.setFontSize(12);
        text.setColour(PARENT_SYSTEM->getFontColour());
        text.print( PARENT_SYSTEM->getSecretDescription());
    }
    else
    {
        text.print(name+"\n");
        string temp = descr;
        temp = StringUtility::substrReplace(temp,"%c",StringUtility::intToString(count));
        temp = StringUtility::substrReplace(temp,"%l",StringUtility::intToString(limit));
        text.setFontSize(12);
        text.setColour(PARENT_SYSTEM->getFontColour());
        text.print(temp+"\n");
    }

    // icon
    if (unlocked)
        icon.setCurrentFrame(1);
    else
        icon.setCurrentFrame(0);
    icon.render();
}
#endif


///------------------------------
/// Private
///------------------------------

void Achievement::changeCount(const vector<Event*>& changeEvents)
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
    for (I = changeEvents.begin(); I < changeEvents.end(); ++I)
    {
        if ((*I)->action == acRESET)
        {
            count = 0;
            break;
        }
        else if ((*I)->action == acDECREASE)
        {
            count--;
        }
        else if ((*I)->action == acINCREASE)
        {
            count++;
        }
        else if ((*I)->action == acINCREASE_COUNT)
        {
            count += (*I)->count;
        }
    }
}

#ifdef PENJIN_SDL
void Achievement::renderProgress(SDL_Surface* screen)
{
    if (showProgress)
    {
        if (not unlocked)
        {
            bgBox.setDimensions(round(size.x*float(count)/limit),size.y);
            bgBox.setColour(PARENT_SYSTEM->getProgressColour());
            bgBox.render(screen);

        }
        text.setBoundaries(Vector2di(position.x+size.y,position.y+round(0.7*size.y)),Vector2di(position.x+size.x-BORDER,position.y+size.y));
        text.setPosition(position.x+size.y,position.y+round(0.7*size.y));
        text.setAlignment(TextClass::RIGHT_JUSTIFIED);
        text.setFontSize(18);
        string temp = StringUtility::intToString(min(count,limit))+"/"+StringUtility::intToString(limit);
        text.print(screen,temp);
    }
}

#else

void Achievement::renderProgress()
{
    if (showProgress)
    {
        if (not unlocked)
        {
            bgBox.setDimensions(round(size.x*float(count)/limit),size.y);
            bgBox.setColour(PARENT_SYSTEM->getProgressColour());
            bgBox.render();

        }
        text.setBoundaries(Vector2di(position.x+size.y,position.y+round(0.7*size.y)),Vector2di(position.x+size.x-BORDER,position.y+size.y));
        text.setPosition(position.x+size.y,position.y+round(0.7*size.y));
        text.setAlignment(TextClass::RIGHT_JUSTIFIED);
        text.setFontSize(18);
        string temp = StringUtility::intToString(min(count,limit))+"/"+StringUtility::intToString(limit);
        text.print(temp);
    }
}
#endif
