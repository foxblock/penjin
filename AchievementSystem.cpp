#include "AchievementSystem.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementSystem* AchievementSystem::m_self = NULL;

AchievementSystem::AchievementSystem()
{

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


#ifdef PENJIN_SDL
void AchievementSystem::render(SDL_Surface* screen)
{
    // Render all achievements at a given offset (in a list form)
    for (int I = 0; I < achievements.size(); I++)
    {
        achievements.at(I)->render(screen,offsetX,offsetY + ACHIEVEMENT_HEIGHT*I);
    }
}

#else
void AchievementSystem::render()
{
    for (int I = 0; I < achievements.size(); I++)
    {
        achievements.at(I)->render(offsetX,offsetY + ACHIEVEMENT_HEIGHT*I);
    }
}
#endif

void AchievementSystem::update()
{
    vector<Achievement*>::iterator I;

    // compares all achievements with log and checks for updates
    if (log.size() > 0)
    {
        for (I=achievements.begin(); I < achievements.end(); I++)
        {
            (**I).check(log);
        }
    }

	log.clear();
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
        string line = doc.getLine(i);
        vector<Achievement*>::iterator I;
        // first look for the name of the achievement
        for (I=achievements.begin(); I < achievements.end(); ++I)
        {
            // when we find a name which matches an achievement
            string name = (*I)->getName() + "\n";
            if(name == line)
            {
                //  the next line is the count
                ++i;
                (*I)->setCount(StringUtility::stringToInt(doc.getLine(i)));
                //  move to the next line
                ++i;
                //  break out since we are finished with this achievement
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
        doc.append((*I)->getName());
        //  save the count
        doc.append(StringUtility::intToString((*I)->getCount()));
    }
	doc.save(file);
	return PENJIN_OK;
}

///------------------------------
/// Private
///------------------------------
