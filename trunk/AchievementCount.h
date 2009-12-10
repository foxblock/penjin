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
using namespace AchievementUtility;

class AchievementCount : public Achievement
{
    public:
        AchievementCount();
        ~AchievementCount();

        void addEventSpecial(CRstring name, const vector<SpecialProperty>& special, CRint count=1, CRint comparison=0, CRint action=0);

    protected:
        // increase or decrease achievement count
        void changeCount(const vector<Event>& changeEvents);
};

#endif // ACHIEVEMENT_H

