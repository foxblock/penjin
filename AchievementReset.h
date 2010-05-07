#ifndef ACHIEVEMENTRESET_H
#define ACHIEVEMENTRESET_H

///------------------------------
/// Reset Achievement class
/// by foxblock 10/12/09
///
/// Like AchievementCount - only one increasing event, but multiple events
/// which reset the count or decrease it
///------------------------------

#include "Achievement.h"
using namespace std;

class AchievementReset : public Achievement
{
    public:
        AchievementReset();

        virtual void addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count=1, CRint comparison=0, CRint action=0);

    protected:
};

#endif // ACHIEVEMENTRESET_H


