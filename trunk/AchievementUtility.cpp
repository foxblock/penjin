#include "AchievementUtility.h"

vector<SpecialProperty> AchievementUtility::emptySpecial()
{
    vector<SpecialProperty> prop;
    return prop;
}

SpecialProperty AchievementUtility::special(CRstring name, CRint value, CRint comparison)
{
    SpecialProperty prop = {name,value,comparison};
    return prop;
}

SpecialProperty AchievementUtility::special(CRint name, CRint value, CRint comparison)
{
    SpecialProperty prop = {StringUtility::intToString(name),value,comparison};
    return prop;
}

bool AchievementUtility::compare(CRint reference, CRint value, CRint op)
{
    if (op == coDONT_CARE)
        return true;
    else if (op == coSMALLER)
        return value < reference;
    else if (op == coEQUAL)
        return value == reference;
    else if (op == coGREATER)
        return value > reference;
}

bool AchievementUtility::checkSpecial(const SpecialProperty& sp1, const SpecialProperty& sp2)
{
    if (sp1.property != sp2.property && not compare(sp1.value,sp2.value,sp1.comparison))
        return false;

    return true;
}

bool AchievementUtility::checkSpecial(const vector<SpecialProperty>& sp1, const vector<SpecialProperty>& sp2)
{
    if (sp1.size() == 0)
        return true;
    if (sp1.size() > sp2.size())
        return false;

    vector<SpecialProperty>::const_iterator I;
    for (I = sp1.begin(); I < sp1.end(); I++)
    {
        // searches for same property name
        bool found = false;
        vector<SpecialProperty>::const_iterator K;
        for (K = sp2.begin(); K < sp2.end(); K++)
        {
            if (I->property == K->property)
            {
                // if found it compares the values
                if (not compare(I->value,K->value,I->comparison))
                {
                    return false;
                }
                else
                {
                    found = true;
                    break;
                }
            }
        }
        // if not found - return missmatch
        if (found == false)
            return false;
    }

    return true;
}

bool AchievementUtility::isEvent(CRstring name, const vector<Event>& events)
{
	bool found = false;
	vector<Event>::const_iterator I;

	for(I = events.begin(); I < events.end() && not found; I++)
	{
		if (I->name == name)
			found = true;
	}

	return found;
}

bool AchievementUtility::isEventSpecial(CRstring name, const vector<SpecialProperty>& special, const vector<Event>& events)
{
    bool found = false;
    vector<Event>::const_iterator I;

    for (I = events.begin(); I < events.end() && not found; I++)
    {
        if (I->name == name && checkSpecial(I->special,special))
            found = true;
    }

    return found;
}

string AchievementUtility::getSecretName()
{
     return "???";
}

string AchievementUtility::getSecretDescription()
{
     return "It's a secret.";
}
