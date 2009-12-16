#include "AchievementSystem.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementSystem* AchievementSystem::m_self = NULL;

AchievementSystem::AchievementSystem()
{
    offsetX = 0;
    offsetY = 0;
    popupX = 0;
    popupY = 0;
    fadeTime = 1000;
    showTime = 3000;
    popupTimer.start();
}

AchievementSystem::~AchievementSystem()
{
    vector<Achievement*>::iterator I;
    for (I = achievements.begin(); I < achievements.end(); I++)
    {
        delete (*I);
    }
}

AchievementSystem* AchievementSystem::GetSingleton()
{
	if ( m_self == NULL)
        m_self = new AchievementSystem();
	return m_self;
}

///------------------------------
/// Public
///------------------------------

void AchievementSystem::logEventSpecial(CRstring name, const vector<SpecialProperty>& special, CRint count)
{
    bool found = false;
    vector<Event>::iterator I;

    // goes through the vector of already logged events and increases count if found
    for (I = log.begin(); I < log.end() && not found; I++)
    {
        if (I->name == name && checkSpecial(I->special,special))
        {
            found = true;
            I->count += count;
        }
    }

    // if not found, logged event is added to vector
    if (not found)
    {
        Event ev = {name,special,count,0,0};
        log.push_back(ev);
    }
}

void AchievementSystem::setPopupPosition(PopupPos pos)
{
    SDL_Surface* screen = SDL_GetVideoSurface();
    if (pos == ppTOPLEFT || pos == ppTOPCENTER || pos == ppTOPRIGHT)
        popupY = 0;
    else
        popupY = screen->h - ACHIEVEMENT_HEIGHT;

    if (pos == ppTOPLEFT || pos == ppBOTTOMLEFT)
        popupX = 0;
    else if (pos == ppTOPCENTER || pos == ppBOTTOMCENTER)
        popupX = round((screen->w - ACHIEVEMENT_WIDTH) / 2);
    else
        popupX = screen->w - ACHIEVEMENT_WIDTH;
}

int AchievementSystem::getListSize() const
{
    SDL_Surface* screen = SDL_GetVideoSurface();
    return floor(screen->h / ACHIEVEMENT_HEIGHT);
}

#ifdef PENJIN_SDL
void AchievementSystem::render(SDL_Surface* screen)
{
    // Render achievement popups
    vector<Popup>::iterator I;
    int count = 0;
    for (I = popups.begin(); I < popups.end(); ++I)
    {
        int diff = popupTimer.getScaledTicks() - I->time;

        // fade in
        if (diff <= fadeTime)
        {
            // this is: general popup Y position + fade offset - count offset (depending on how many popups are on screen at once)
            I->a->render(screen,popupX, popupY + (ACHIEVEMENT_HEIGHT * (fadeTime - diff) / fadeTime) - (ACHIEVEMENT_HEIGHT * count));
        }
        // show
        else if (diff <= (fadeTime + showTime) - (ACHIEVEMENT_HEIGHT * count))
        {
            I->a->render(screen,popupX,popupY);
        }
        // fade out
        else
        {
            I->a->render(screen,popupX, popupY + (ACHIEVEMENT_HEIGHT * (diff - (fadeTime + showTime)) / fadeTime) - (ACHIEVEMENT_HEIGHT * count));
        }

        count++;
    }
}

void AchievementSystem::renderList(SDL_Surface* screen, int offset)
{
    if (offset < 0 || offset >= achievements.size())
    {
        #ifdef DEBUG
        cout << "[Achievements] Error: Trying to render list with out-of-bounds offset!" << endl;
        #endif
        return;
    }

    vector<Achievement*>::iterator I;
    int count = 0;
    for (I = achievements.begin()+offset; I < achievements.end(); ++I)
    {
        (**I).render(screen,offsetX,offsetY+(ACHIEVEMENT_HEIGHT*count));
        ++count;
    }
}

#else
void AchievementSystem::render()
{
    // Render achievement popups
    vector<Popup>::iterator I;
    int count = 0;
    for (I = popups.begin(); I < popups.end(); ++I)
    {
        int diff = popupTimer.getScaledTicks() - I->time;

        // fade in
        if (diff <= fadeTime)
        {
            // this is: general popup Y position + fade offset - count offset (depending on how many popups are on screen at once)
            I->a->render(popupX, popupY + (ACHIEVEMENT_HEIGHT * (fadeTime - diff) / fadeTime) - (ACHIEVEMENT_HEIGHT * count));
        }
        // show
        else if (diff <= (fadeTime + showTime) - (ACHIEVEMENT_HEIGHT * count))
        {
            I->a->render(popupX,popupY);
        }
        // fade out
        else
        {
            I->a->render(popupX, popupY + (ACHIEVEMENT_HEIGHT * (diff - (fadeTime + showTime)) / fadeTime) - (ACHIEVEMENT_HEIGHT * count));
        }

        count++;
    }
}
#endif

void AchievementSystem::update()
{
    vector<Achievement*>::iterator I;

    // compares all achievements with log and checks for updates
    if (log.size() > 0)
    {
        for (I = achievements.begin(); I < achievements.end(); ++I)
        {
            if (not (**I).getStatus() && (**I).check(log))
            {
                save("achieve.ach");
                Popup temp = {(*I),popupTimer.getScaledTicks()};
                popups.push_back(temp);
            }
        }
    }

	log.clear();

	// removes old popups
	vector<Popup>::iterator K;

    for (K = popups.begin(); K < popups.end(); ++K)
    {
        if (K->time <= popupTimer.getScaledTicks() - (2*fadeTime + showTime))
            popups.erase(K);
    }
}

PenjinErrors::PENJIN_ERRORS AchievementSystem::load(CRstring file)
{
	doc.clear();
	doc.load(file);
	if(!doc.size())
		return PENJIN_FILE_NOT_FOUND;
    int i = 0;
    while(i < doc.size())
    {
        // get a line
        string line = crypt.decryptBuffer(doc.getLine(i));
        vector<Achievement*>::iterator I;
        // first look for the name of the achievement
        for (I=achievements.begin(); I < achievements.end(); ++I)
        {
            // when we find a name which matches an achievement
            string name = (*I)->getName();
            if(name == line)
            {
                //  the next line is the count
                ++i;
                (*I)->setCount(StringUtility::stringToInt(crypt.decryptBuffer(doc.getLine(i))));
                //  move to the next line
                ++i;
                //  break out since we are finished with this achievement
                break;
            }
            //  we should only reach here if there was a problem loading an achievement from file.
            if(I == achievements.end())
                ++i;
        }
    }
	return PENJIN_OK;
}

PenjinErrors::PENJIN_ERRORS AchievementSystem::save(CRstring file)
{
	doc.clear();
    vector<Achievement*>::iterator I;
    // run through the achievements
    for (I=achievements.begin(); I < achievements.end(); ++I)
    {
        //  save the name
        doc.append(crypt.encryptBuffer((*I)->getName()));
        //  save the count
        doc.append( crypt.encryptBuffer(StringUtility::intToString((*I)->getCount())));
    }
	doc.save(file);
	return PENJIN_OK;
}

///------------------------------
/// Private
///------------------------------
