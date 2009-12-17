#include "Achievement.h"

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

    text.loadFont("font/atrox.ttf",16);
    //text.setRenderMode(GlyphClass::BOXED);
    text.setBgColour(DARK_GREY);
    text.setRelativity(true);
}

Achievement::~Achievement()
{

}


///------------------------------
/// Public
///------------------------------

bool Achievement::check(const vector<Event>& checkEvents)
{
    vector<Event> countEvents;
    vector<Event>::const_iterator I;

    // go through the logged events and compare with achievements events
    for (I = checkEvents.begin(); I < checkEvents.end(); I++)
    {
        vector<Event>::const_iterator K;
        for (K = events.begin(); K < events.end(); K++)
        {
            // comparison:
            if (I->name == K->name && compare(K->count,I->count,K->comparison) && checkSpecial(K->special,I->special))
            {
                // add necessary information to a temporary vector which will be passed to the changeCount function
                Event ev = {K->name,emptySpecial(),I->count,0,K->action};
                countEvents.push_back(ev);
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
        return false;
}

// the actual addEvent function, which all wrapper functions use
void Achievement::addEventSpecial(CRstring name, const vector<SpecialProperty>& special, CRint count, CRint comparison, CRint action)
{
    // check whether event was already added to prevent duplicates
	if (not isEventSpecial(name,special,events))
	{
	    Event ev = {name,special,count,comparison,action};
		events.push_back(ev);
	}
    #ifdef _DEBUG
    else
        cout << "[Achievements] Error: Duplicate event " << name << " on achievement " << this->name << " - ignored!" << endl;
    #endif
}


#ifdef PENJIN_SDL
void Achievement::render(SDL_Surface* screen, int xPos, int yPos)
{
    // background box
    bgBox.setPosition(xPos,yPos);
    bgBox.setDimensions(ACHIEVEMENT_WIDTH,ACHIEVEMENT_HEIGHT);
    text.setPosition(xPos+80,yPos+5);
    text.setBoundaries(Vector2di(xPos+80,yPos+5),Vector2di(xPos+ACHIEVEMENT_WIDTH-5,yPos+ACHIEVEMENT_HEIGHT-5));
    if (unlocked)
    {
        bgBox.setColour(Colour(160,160,160));
        text.setBgColour(Colour(160,160,160));
    }
    else
    {
        bgBox.setColour(DARK_GREY);
        text.setBgColour(DARK_GREY);
    }
    bgBox.render(screen);

    // icon
    icon.setPosition(xPos+5,yPos+5);
    if (unlocked)
        icon.setCurrentFrame(1);
    else
        icon.setCurrentFrame(0);
    icon.render(screen);

    // text
    text.setAlignment(TextClass::LEFT_JUSTIFIED);
    text.setFontSize(24);
    text.setColour(40,40,100);
    if (secret && not unlocked)
    {
        text.print(screen,getSecretName()+"\n");
        text.setFontSize(16);
        text.setColour(WHITE);
        text.print(screen, getSecretDescription());
    }
    else
    {
        text.print(screen,name+"\n");
        string temp = descr;
        temp = StringUtility::substrReplace(temp,"%c",StringUtility::intToString(count));
        temp = StringUtility::substrReplace(temp,"%l",StringUtility::intToString(limit));
        text.setFontSize(16);
        text.setColour(WHITE);
        text.print(screen,temp);
        text.setBoundaries(Vector2di(xPos+80,yPos+54),Vector2di(xPos+ACHIEVEMENT_WIDTH-5,yPos+ACHIEVEMENT_HEIGHT));
        text.setPosition(xPos+80,yPos+54);
        text.setAlignment(TextClass::RIGHT_JUSTIFIED);
        text.setFontSize(24);
        temp = StringUtility::intToString(min(count,limit))+"/"+StringUtility::intToString(limit);
        text.print(screen,temp);
    }
}

#else
void Achievement::render(int xPos, int yPos)
{

}
#endif


///------------------------------
/// Private
///------------------------------

void Achievement::changeCount(const vector<Event>& changeEvents)
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

    vector<Event>::const_iterator I;

    // go through events and change count accordingly
    for (I = changeEvents.begin(); I < changeEvents.end(); I++)
    {
        if (I->action == acRESET)
        {
            count = 0;
            break;
        }
        else if (I->action == acDECREASE)
            count--;
        else if (I->action == acINCREASE)
            count++;
        else if (I->action == acINCREASE_COUNT)
            count += I->count;
    }
}
