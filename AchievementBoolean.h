#ifndef ACHIEVEMENTBOOLEAN_H
#define ACHIEVEMENTBOOLEAN_H

///------------------------------
/// Boolean Achievement class
/// by foxblock 10/12/09
///
/// Simple achievement, count is increased by one if all events are matched
///------------------------------


#include "Achievement.h"
using namespace std;

class AchievementBoolean : public Achievement
{
    public:
        AchievementBoolean();

    protected:
        // increase or decrease achievement count
        virtual void changeCount(const vector<Event*>& changeEvents);
};

#endif // ACHIEVEMENTBOOLEAN_H

