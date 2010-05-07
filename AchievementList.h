#ifndef ACHIEVEMENTRESETTWO_H
#define ACHIEVEMENTRESETTWO_H

///------------------------------
/// List Achievement class
/// by foxblock 15/12/09
///
/// Mix of Boolean, Reset and Time Achievements
/// Several events, must be completed in no particular order and without time constraint
/// Reset-events, reset count and completed events
///------------------------------

#include "Achievement.h"
using namespace std;

class AchievementList : public Achievement
{
    public:
        AchievementList();

        void addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count, CRint comparison, CRint action);

        virtual int getTimeLimit() const {return -1;};
        virtual void setTimeLimit(CRint value);

        virtual void load(CRstring);
        virtual string save() const;

        #ifdef PENJIN_SDL
        void renderProgress(SDL_Surface* screen);
        #else
        void renderProgress();
        #endif

    protected:
        // increase or decrease achievement count
        void changeCount(const vector<Event*>& changeEvents);

        void resetDone();

        vector<bool> doneEvents;
        int doneCount;
        int eCount;
};

#endif // ACHIEVEMENTRESETTWO_H


