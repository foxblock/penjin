#ifndef ACHIEVEMENTRESETTWO_H
#define ACHIEVEMENTRESETTWO_H

///------------------------------
/// Boolean Reset Achievement class
/// by foxblock 15/12/09
///
/// Mix of Boolean, Reset and Time Achievements
/// Several events, must be completed in no particular order and without time constraint
/// Reset events, reset count and completed events
///------------------------------

#include "Achievement.h"
using namespace std;
using namespace AchievementUtility;

class AchievementReset2 : public Achievement
{
    public:
        AchievementReset2();
        virtual ~AchievementReset2();

        void addEventSpecial(CRstring name, const vector<SpecialProperty>& special, CRint count, CRint comparison, CRint action);

    protected:
        // increase or decrease achievement count
        void changeCount(const vector<Event>& changeEvents);

        void resetDone();

        vector<bool> doneEvents;
};

#endif // ACHIEVEMENTRESETTWO_H


