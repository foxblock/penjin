#include "AchievementSystem.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementSystem* AchievementSystem::m_self = NULL;

AchievementSystem::AchievementSystem()
{
    offset = Vector2di(0,0);
    achievementSize = Vector2di(DEFAULT_ACHIEVEMENT_WIDTH,DEFAULT_ACHIEVEMENT_HEIGHT);
    popupSize = achievementSize;
    spacing = 0;
    popup = Vector2di(0,0);
    fadeTime = 500;
    showTime = 2000;
    showTop = false;
    popupTimer.start();

    colours[coFontColour] = DEFAULT_FONT_COLOUR;
    colours[coHeadlineColour] = DEFAULT_HEADLINE_COLOUR;
    colours[coBackgroundColour] = DEFAULT_BACKGROUND_COLOUR;
    colours[coProgressColour] = DEFAULT_PROGRESS_COLOUR;

    secretText[0] = DEFAULT_SECRET_HEADLINE;
    secretText[1] = DEFAULT_SECRET_DESCRIPTION;
}

AchievementSystem::~AchievementSystem()
{
    vector<Achievement*>::iterator I;
    for (I = achievements.begin(); I < achievements.end(); ++I)
        delete (*I);

    vector<Event*>::iterator K;
    for (K = log.begin(); K < log.end(); ++K)
        delete (*K);
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

void AchievementSystem::logEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count)
{
    bool found = false;
    vector<Event*>::iterator I;

    // goes through the vector of already logged events and increases count if found
    for (I = log.begin(); I < log.end() && not found; ++I)
    {
        if ((*I)->name == name && (*I)->checkSpecial(special))
        {
            found = true;
            (*I)->count += count;
        }
    }

    // if not found, logged event is added to vector
    if (not found)
    {
        Event* ev = new Event(name,special,count,0,0);
        log.push_back(ev);
    }
}

void AchievementSystem::setPopupPosition(PopupPos pos)
{
    SDL_Surface* screen = SDL_GetVideoSurface();
    if (pos == ppTOPLEFT || pos == ppTOPCENTER || pos == ppTOPRIGHT)
    {
        popup.y = 0;
        showTop = true;
    }
    else
    {
        popup.y = screen->h - popupSize.y;
        showTop = false;
    }

    if (pos == ppTOPLEFT || pos == ppBOTTOMLEFT)
        popup.x = 0;
    else if (pos == ppTOPCENTER || pos == ppBOTTOMCENTER)
        popup.x = round((screen->w - popupSize.x) / 2);
    else
        popup.x = screen->w - popupSize.x;
}

int AchievementSystem::unlockedCount() const
{
    vector<Achievement*>::const_iterator I;
    int count = 0;
    for (I = achievements.begin(); I < achievements.end(); ++I)
    {
        if ((**I).getStatus())
            ++count;
    }
    return count;
}

float AchievementSystem::getListSize() const
{
    SDL_Surface* screen = SDL_GetVideoSurface();
    return (float)(screen->h - offset.y + spacing) / (float)(achievementSize.y + spacing);
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

        I->a->setSize(popupSize);

        if (showTop)
        {
            // fade in
            if (diff <= fadeTime)
                I->a->setPosition(popup.x, popup.y + (popupSize.y * count) - (popupSize.y * (count + 1) * (fadeTime - diff) / fadeTime) );
            // show
            else if (diff <= (fadeTime + showTime))
                I->a->setPosition(popup.x,popup.y + (popupSize.y * count));
            // fade out
            else
                I->a->setPosition(popup.x, popup.y + (popupSize.y * count) - (popupSize.y * (count + 1) * (diff - (fadeTime + showTime)) / fadeTime));
        }
        else
        {
            // fade in
            if (diff <= fadeTime)
                I->a->setPosition(popup.x, popup.y - (popupSize.y * count) + (popupSize.y * (count + 1) * (fadeTime - diff) / fadeTime) );
            // show
            else if (diff <= (fadeTime + showTime))
                I->a->setPosition(popup.x,popup.y - (popupSize.y * count));
            // fade out
            else
                I->a->setPosition(popup.x, popup.y - (popupSize.y * count) + (popupSize.y * (count + 1) * (diff - (fadeTime + showTime)) / fadeTime));
        }

        I->a->render(screen);

        I->a->setSize(achievementSize);
        count++;
    }
}

void AchievementSystem::renderList(SDL_Surface* screen, float numOffset)
{
    if (floor(numOffset) < 0 || ceil(numOffset) >= achievements.size()) {
        #ifdef DEBUG
        cout << "[Achievements] Error: Trying to render list with out-of-bounds offset (" << numOffset << ")!" << endl;
        #endif
        if (floor(numOffset) < 0)
            numOffset = 0;
        else
            numOffset = achievements.size();
    }

    vector<Achievement*>::iterator I;
    float count = floor(numOffset) - numOffset;
    for (I = achievements.begin()+floor(numOffset); I < min(achievements.begin()+ceil(numOffset+getListSize()),achievements.end()); ++I)
    {
        (**I).setPosition(offset.x,round(offset.y+((achievementSize.y+spacing)*count)));
        (**I).render(screen);
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

        I->a->setSize(popupSize);

        if (showTop)
        {
            // fade in
            if (diff <= fadeTime)
                I->a->setPosition(popup.x, popup.y + (popupSize.y * count) - (popupSize.y * (count + 1) * (fadeTime - diff) / fadeTime) );
            // show
            else if (diff <= (fadeTime + showTime))
                I->a->setPosition(popup.x,popup.y + (popupSize.y * count));
            // fade out
            else
                I->a->setPosition(popup.x, popup.y + (popupSize.y * count) - (popupSize.y * (count + 1) * (diff - (fadeTime + showTime)) / fadeTime));
        }
        else
        {
            // fade in
            if (diff <= fadeTime)
                I->a->setPosition(popup.x, popup.y - (popupSize.y * count) + (popupSize.y * (count + 1) * (fadeTime - diff) / fadeTime) );
            // show
            else if (diff <= (fadeTime + showTime))
                I->a->setPosition(popup.x,popup.y - (popupSize.y * count));
            // fade out
            else
                I->a->setPosition(popup.x, popup.y - (popupSize.y * count) + (popupSize.y * (count + 1) * (diff - (fadeTime + showTime)) / fadeTime));
        }

        I->a->render();

        I->a->setSize(achievementSize);
        count++;
    }
}

void AchievementSystem::renderList(float numOffset)
{
    if (floor(numOffset) < 0 || ceil(numOffset) >= achievements.size()) {
        #ifdef DEBUG
        cout << "[Achievements] Error: Trying to render list with out-of-bounds offset (" << numOffset << ")!" << endl;
        #endif
        if (floor(numOffset) < 0)
            numOffset = 0;
        else
            numOffset = achievements.size();
    }

    vector<Achievement*>::iterator I;
    float count = floor(numOffset) - numOffset;
    for (I = achievements.begin()+floor(numOffset); I < min(achievements.begin()+ceil(numOffset+getListSize()),achievements.end()); ++I)
    {
        (**I).setPosition(offset.x,round(offset.y+((achievementSize.y+spacing)*count)));
        (**I).render();
        ++count;
    }
}
#endif

void AchievementSystem::update()
{
    vector<Achievement*>::iterator I;
    vector<int> unlocked;

    // compares all achievements with log and checks for updates
    if (log.size() > 0)
    {
        int index = 0;
        for (I = achievements.begin(); I < achievements.end(); ++I)
        {
            if (not (**I).getStatus() && (**I).check(log))
            {
                save("achieve.ach");
                Popup temp = {(*I),popupTimer.getScaledTicks()};
                popups.push_back(temp);
                unlocked.push_back(index);
            }
            ++index;
        }
    }

    // clear the log
    vector<Event*>::iterator L;
    for (L = log.begin(); L < log.end(); ++L)
        delete *(L);
	log.clear();

    // if anything was unlocked, log an event for that, too
    vector<int>::iterator M;
    for (M = unlocked.begin(); M < unlocked.end(); ++M)
    {
        vector<SpecialProperty>* prop = new vector<SpecialProperty>;
        prop->push_back(SpecialProperty("INDEX",(*M),coEQUAL));
        logEventSpecial("ACHIEVEMENT_UNLOCK",prop);
    }

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
    unsigned int i = 0;
    bool changed = true;
    while(i < doc.size())
    {
        // get a line
        if(changed == false)
            ++i;
        string line = crypt.decryptBuffer(doc.getLine(i));
        vector<Achievement*>::iterator I;
        // first look for the name of the achievement
        changed = false;
        for (I=achievements.begin(); I < achievements.end(); ++I)
        {
            // when we find a name which matches an achievement
            string name = (*I)->getName();
            if(name == line)
            {
                //  the next line is the count
                ++i;
                (*I)->load(crypt.decryptBuffer(doc.getLine(i)));
                //  move to the next line
                ++i;
                //  break out since we are finished with this achievement
                changed = true;
                break;
            }
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
        doc.append( crypt.encryptBuffer( (*I)->save() ));
    }
	doc.save(file);
	return PENJIN_OK;
}

///------------------------------
/// Private
///------------------------------
