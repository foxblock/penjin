#include "Event.h"

bool Event::check(const Event* const ev) const
{
    if (name == ev->name && SpecialProperty::compare(count,ev->count,comparison) && checkSpecial(ev->special))
        return true;

    return false;
}

bool Event::checkSpecial(const vector<SpecialProperty>* const sp) const
{
    if (special)
    {
        if (!sp)
            return false;
    }
    else
        return true;
    if (special->size() == 0)
        return true;
    if (special->size() > sp->size())
        return false;

    vector<SpecialProperty>::const_iterator I;
    for (I = special->begin(); I < special->end(); I++)
    {
        // checking the property
        bool found = false;
        vector<SpecialProperty>::const_iterator K;
        for (K = sp->begin(); K < sp->end(); K++)
        {
            if (I->property == K->property)
            {
                // if found it compares the values
                if (not SpecialProperty::compare(I->value,K->value,I->comparison))
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

bool Event::isEvent(const vector<Event*>& events) const
{
    bool found = false;
    vector<Event*>::const_iterator I;

    for (I = events.begin(); I < events.end() && not found; ++I)
    {
        if ((*I)->name == name && (*I)->checkSpecial(special))
            found = true;
    }

    return found;
}
