#ifndef ACHIEVEMENTSYSTEM_H
#define ACHIEVEMENTSYSTEM_H

///------------------------------
/// AchievementSystem class
/// by foxblock 10/12/09
///
/// The backbone of the Achievement system
/// Contains all achievements, monitors and updates progress and is used for renderring
///------------------------------


#define DEFAULT_ACHIEVEMENT_HEIGHT 74
#define DEFAULT_ACHIEVEMENT_WIDTH 300

#include "Achievement.h"
#include "AchievementBoolean.h"
#include "AchievementCount.h"
#include "AchievementTime.h"
#include "AchievementReset.h"
#include "AchievementList.h"
#include "Text.h"
#include "Timer.h"
#include "Vector2di.h"

#include "TextDoc.h"
#include "Encryption.h"
#include "PenjinErrors.h"

using namespace PenjinErrors;
using namespace std;
using namespace AchievementUtility;

enum PopupPos // Top positions currently not sliding in correctly
{
    ppTOPLEFT,
    ppTOPCENTER,
    ppTOPRIGHT,
    ppBOTTOMLEFT,
    ppBOTTOMCENTER,
    ppBOTTOMRIGHT
};

struct Popup
{
    Achievement* a;
    int time;
};

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
        void setOffset(CRint newX, CRint newY) {setOffset(Vector2di(newX,newY));};
        void setOffset(const Vector2di& newOffset) {offset = newOffset;};
        Vector2di getAchievementSize() const {return achievementSize;};
        void setAchievementSize(CRint newW, CRint newH) {setAchievementSize(Vector2di(newW,newH));};
        void setAchievementSize(const Vector2di& newSize) {achievementSize = newSize;};
        void setPopupSize(CRint newW, CRint newH) {setPopupSize(Vector2di(newW,newH));};
        void setPopupSize(const Vector2di& newSize) {popupSize = newSize;};
        void setSpacing(int newS) {spacing = newS;};
        void setPopupPosition(PopupPos pos);
        void setPopupFadeTime(CRint newFade) {fadeTime = newFade;};
        void setPopupShowTime(CRint newShow) {showTime = newShow;};

        // general functions
        int achievementCount() const {return achievements.size();};
        int unlockedCount() const;
        int getListSize() const;
        #ifdef PENJIN_SDL
        void render(SDL_Surface* screen);
        void renderList(SDL_Surface* screen, int numOffset);
        #else
        void render();
        void renderList(int numOffset);
        #endif
        void update();

        PENJIN_ERRORS load(CRstring file);
        PENJIN_ERRORS save(CRstring file);

    private:
        vector<Event> log;
        vector<Achievement*> achievements;
        vector<Popup> popups;
        Encryption crypt;
        TextDoc doc;

        Vector2di offset;
        Vector2di achievementSize;
        Vector2di popupSize;
        int spacing;
        Vector2di popup;
        int fadeTime;
        int showTime;
        Timer popupTimer;
};

#endif // ACHIEVEMENTSYSTEM_H
