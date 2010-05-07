#ifndef ACHIEVEMENTTIME_H
#define ACHIEVEMENTTIME_H

///------------------------------
/// Time Achievement class
/// by foxblock 11/12/09
///
/// Timed Achievement, first event triggers the timer, all events have to occur
/// in the given time for the count to be increased
///------------------------------

#include "Achievement.h"
using namespace std;

class AchievementTime : public Achievement
{
    public:
        AchievementTime();

        void addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count=1, CRint comparison=0, CRint action=0);

    protected:
        // increase or decrease achievement count
        void changeCount(const vector<Event*>& changeEvents);

        vector<bool> doneEvents;
};

#endif // ACHIEVEMENTTIME_H


