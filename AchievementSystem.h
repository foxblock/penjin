#ifndef ACHIEVEMENTSYSTEM_H
#define ACHIEVEMENTSYSTEM_H

///------------------------------
/// AchievementSystem class
/// by foxblock 10/12/09
///
/// The backbone of the Achievement system
/// Contains all achievements, monitors and updates progress and is used for renderring
///------------------------------


#define ACHIEVEMENT_HEIGHT 80
#define ACHIEVEMENT_WIDTH 300

#include "Achievement.h"
#include "AchievementBoolean.h"
#include "AchievementCount.h"
#include "Text.h"
#include "TextDoc.h"
#include "Encryption.h"
#include "PenjinErrors.h"

using namespace PenjinErrors;
using namespace std;
using namespace AchievementUtility;

class AchievementSystem
{
    private:
        AchievementSystem();

        static AchievementSystem* m_self;
    public:
        ~AchievementSystem();
        static AchievementSystem* GetSingleton();

        // adds an achievent to the vector, what else...
        void addAchievement(Achievement* a){achievements.push_back(a);}

        // different wrapper functions for logging an event using different levels of information
        void logEvent(CRint id, CRint count=1) {logEventSpecial(StringUtility::intToString(id),emptySpecial(),count);}
        void logEvent(CRstring name, CRint count=1) {logEventSpecial(name,emptySpecial(),count);}
        void logEventSpecial(CRint id, const vector<SpecialProperty>& special, CRint count=1) {logEventSpecial(StringUtility::intToString(id),special,count);}
        void logEventSpecial(CRstring name, const vector<SpecialProperty>& special, CRint count=1);

        // display and layout functions
        void setOffset(int newX, int newY) {offsetX = newX; offsetY = newY;};

        // general functions
        #ifdef PENJIN_SDL
        void render(SDL_Surface* screen);
        #else
        void render();
        #endif
        void update();

        PENJIN_ERRORS load(CRstring file);
        PENJIN_ERRORS save(CRstring file);

    private:
        vector<Event> log;
        vector<Achievement*> achievements;
        Encryption crypt;
        TextDoc doc;

        int offsetX;
        int offsetY;
};

#endif // ACHIEVEMENTSYSTEM_H
