#include "AchievementReset.h"

///------------------------------
/// Constructor / Destructor
///------------------------------

AchievementReset::AchievementReset() : Achievement()
{
    type = atRESET;
}

AchievementReset::~AchievementReset()
{

}


///------------------------------
/// Public
///------------------------------

// the actual addEvent function, which all wrapper functions use
void AchievementReset::addEventSpecial(CRstring name, const vector<SpecialProperty>& special, CRint count, CRint comparison, CRint action)
{
    // check whether event was already added to prevent duplicates
	if ((action != acINCREASE || action != acINCREASE_COUNT) || events.size() == 0)
	{
	    Event ev = {name,special,count,comparison,action};
		events.push_back(ev);
	}
    #ifdef _DEBUG
	else
        cout << "[Achievements] Error: Can't add multiple increasing events to an AchievementReset (" << this->name << ")" << endl;
	#endif
}


///------------------------------
/// Private
///------------------------------
