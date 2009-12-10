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

    tDescr.loadFont("font/atrox.ttf", 16);
    tDescr.setColour(Colour(WHITE)),
    tName.loadFont("font/atrox.ttf", 24);
    tName.setColour(Colour(WHITE));
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
                Event ev = {K->name,emptySpecial(),I->count,0,I->action};
                countEvents.push_back(ev);
            }
        }
    }

    // checks for count change
    changeCount(countEvents);

    // returns true if achievemnt has been unlocked
    if (count >= limit)
        return true;
    else
        return false;
}

// the actual addEvent function, which all wrapper functions use
void Achievement::addEventSpecial(CRstring name, const vector<SpecialProperty>& special, CRint count, CRint comparison, CRint action)
{
    // check whether event was already added to prevent duplicates
	if (not isEvent(name,events))
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
    Rectangle rect;
    rect.setPosition(xPos,yPos);
    rect.setDimensions(300,80);
    rect.setColour(DARK_GREY);
    rect.render(screen);
    icon.setPosition(xPos+5,yPos+5);
    icon.render(screen);

    tName.setPosition(xPos+80,yPos+5);
    tName.print(screen,name);
    tDescr.setPosition(xPos+80,yPos+30);
    tDescr.print(screen,descr);
    tName.setPosition(xPos+260,yPos+55);
    string temp = StringUtility::intToString(min(count,limit))+"/"+StringUtility::intToString(limit);
    tName.print(screen,temp);
}

#else
void Achievement::render(int xPos, int yPos)
{
    Rectangle rect;
    rect.setPosition(xPos,yPos);
    rect.setDimensions(300,80);
    rect.setColour(DARK_GREY);
    rect.render();
    icon.setPosition(xPos+5,yPos+5);
    icon.render();

    tName.setPosition(xPos+80,yPos+5);
    tName.print(name);
    tDescr.setPosition(xPos+80,yPos+30);
    tDescr.print(descr);
    tName.setPosition(xPos+260,yPos+55);
    string temp = StringUtility::intToString(min(count,limit))+"/"+StringUtility::intToString(limit);
    tName.print(temp);
}
#endif


///------------------------------
/// Private
///------------------------------

void Achievement::changeCount(const vector<Event>& changeEvents)
{
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
