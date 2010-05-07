#ifndef ACHIEVEMENTCOUNT_H
#define ACHIEVEMENTCOUNT_H

///------------------------------
/// Count Achievement class
/// by foxblock 10/12/09
///
/// Only one event, achievement count is increased by event count
///------------------------------

#include "Achievement.h"
using namespace std;

class AchievementCount : public Achievement
{
    public:
        AchievementCount();

        void addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count=1, CRint comparison=0, CRint action=0);

    protected:
        // increase or decrease achievement count
        void changeCount(const vector<Event*>& changeEvents);
};

#endif // ACHIEVEMENTCOUNT_H

