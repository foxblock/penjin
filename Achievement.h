#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

///------------------------------
/// Base Achievement class
/// by foxblock 10/12/09
///
/// A base class for achievements, all functions are virtual
/// You could use this class, but it's better to create a child class and change at least the changeCount function
///------------------------------

#define ACHIEVEMENT_HEIGHT 80
#define ACHIEVEMENT_WIDTH 300

#include <vector>
#include <string>
#include "StringUtility.h"
#include "PenjinTypes.h"
#include "CountDown.h"

#include "Rectangle.h"
#include "AnimatedSprite.h"
#include "Text.h"

#include "AchievementUtility.h"

using namespace std;
using namespace AchievementUtility;

enum AchievementType
{
    atGENERAL=0,
    atBOOLEAN,
    atCOUNT,
    atTIME,
    atRESET,
    atCOMPLEX,
    atCUSTOM
};

class Achievement
{
    public:
        Achievement();
        virtual ~Achievement();

        // different wrapper functions for adding events
        virtual void addEvent(Event newE){events.push_back(newE);}
        virtual void addEvent(CRint id, CRint count=1, CRint comparison=0, CRint action=0){addEventSpecial(StringUtility::intToString(id),emptySpecial(),count,comparison,action);}
        virtual void addEvent(CRstring name, CRint count=1, CRint comparison=0, CRint action=0){addEventSpecial(name,emptySpecial(),count,comparison,action);}
        virtual void addEventSpecial(CRint id, const vector<SpecialProperty>& special, CRint count=1, CRint comparison=0, CRint action=0){addEventSpecial(StringUtility::intToString(id),special,count,comparison,action);}
        virtual void addEventSpecial(CRstring name, const vector<SpecialProperty>& special, CRint count=1, CRint comparison=0, CRint action=0);

        // getters and setters
        virtual int getLimit() const {return limit;};
        virtual void setLimit(CRint value) {limit = value;};
        virtual int getCount() const {return count;};
        virtual void setCount(CRint c){count = c; if (count >= limit) unlocked = true;};
        virtual int getTimeLimit() const {return counter.getLimit();};
        virtual void setTimeLimit(int newTime) {counter.setLimit(newTime);};
        virtual int eventCount() const {return events.size();}

        virtual int getType() const {return type;};

        virtual string getName() const {return name;};
        virtual void setName(CRstring newName) {if (newName.size() > 0) name = newName;};
        virtual string getDescription() const {return descr;};
        virtual void setDescription(CRstring newDescr) {if (newDescr.size() > 0) descr = newDescr;};
        virtual const AnimatedSprite* getIcon() const {return &icon;};
        virtual void setIcon(string fileName) {icon.loadFrames(fileName,2,1);};
        virtual bool getSecret() const {return secret;};
        virtual void setSecret(bool newState) {secret = newState;};
        virtual bool getStatus() const {return unlocked;};

        // display and layout
        #ifdef PENJIN_SDL
        virtual void render(SDL_Surface* screen, int xPos, int yPos);
        #else
        virtual void render(int xPos, int yPos);
        #endif

        // compare log with achievement events
        virtual bool check(const vector<Event>& checkEvents);

    protected:
        // increase or decrease achievement count
        virtual void changeCount(const vector<Event>& changeEvents);

        // display
        string name;
        string descr;
        AnimatedSprite icon;

        Text text;
        Rectangle bgBox;
        bool secret;

        // data
        vector<Event> events;
        int count;
        int limit;
        bool unlocked;
        int type;
        CountDown counter;
};

#endif // ACHIEVEMENT_H
