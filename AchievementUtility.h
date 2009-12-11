#ifndef ACHIEVEMENTUTILITY_H
#define ACHIEVEMENTUTILITY_H

///------------------------------
/// Achievement Utility namespace
/// by foxblock 10/12/09
///
/// Contains functions, structs and enums for use with the Achievement system
///------------------------------

#include <vector>
#include <string>
#include "PenjinTypes.h"

using namespace std;

// use this for storing many more detailed layers of information about logged events
// e.g. type of weapon, id or name of game won, name of enemy hit, etc.
// logged events don't need the comparison op to be set, the one of the achievement will be used
struct SpecialProperty
{
	string property;
	int value;
	int comparison; // 1 - greater, -1 - smaller, 0 - equal, 2 - don't care
};

enum CompareOp // To-do: add SMALLER-EQUAL and GREATER-EQUAL
{
    coSMALLER=-1,
    coEQUAL,
    coGREATER,
    coDONT_CARE
};

// logged events don't need this, the action parameter of the achievement will be used
enum Action
{
    acRESET=-2, // resets the count to 0
    acDECREASE, // decreases the count by 1
    acDO_NOTHING, // no effect on achievement count
    acINCREASE, // increases count by 1
    acINCREASE_COUNT // increases count by event count value
};

struct Event
{
	string name;
	vector<SpecialProperty> special;
	int count;
	int comparison;
	int action;
};

namespace AchievementUtility
{
    // compares two special properties or two vectors of special properties
    // returns true if all properties match - more specialized proeprties match simpler ones
    // (= if sp2 has a property sp1 has not, it still matches, but not the other way around)
    bool checkSpecial(const SpecialProperty& sp1, const SpecialProperty& sp2);
    bool checkSpecial(const vector<SpecialProperty>& sp1, const vector<SpecialProperty>& sp2);

    // compares a value with a reference value using a comparison operator (CompareOp)
    bool compare(CRint reference, CRint value, CRint op);

    // returns an empty special property
    vector<SpecialProperty> emptySpecial();

    // checks whether an event is already present in an vector of events
    bool isEvent(CRstring name, const vector<Event>& events);
    bool isEventSpecial(CRstring name, const vector<SpecialProperty>& special, const vector<Event>& events);

    // secret text
    string getSecretName();
    string getSecretDescription();
}

#endif // ACHIEVEMENTUTILITY_H
