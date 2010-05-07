#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

///------------------------------
/// Base Achievement class
/// by foxblock 10/12/09
///
/// A base class for achievements, all functions are virtual
/// You could use this class, but it's better to create a child class and change at least the changeCount function
///------------------------------

#define DEFAULT_HEIGHT 74
#define DEFAULT_WIDTH 300
#define BORDER 5

#include <vector>
#include <string>
#include "StringUtility.h"
#include "PenjinTypes.h"
#include "CountDown.h"

#include "Vector2di.h"
#include "Rectangle.h"
#include "AnimatedSprite.h"
#include "Text.h"
#include "Colour.h"

#include "Event.h"

using namespace std;

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
        virtual void addEvent(Event* newE){events.push_back(newE);}
        virtual void addEvent(CRint id, CRint count=1, CRint comparison=0, CRint action=0){addEventSpecial(StringUtility::intToString(id),NULL,count,comparison,action);}
        virtual void addEvent(CRstring name, CRint count=1, CRint comparison=0, CRint action=0){addEventSpecial(name,NULL,count,comparison,action);}
        virtual void addEventSpecial(CRint id, vector<SpecialProperty>* special, CRint count=1, CRint comparison=0, CRint action=0){addEventSpecial(StringUtility::intToString(id),special,count,comparison,action);}
        virtual void addEventSpecial(CRstring name, vector<SpecialProperty>* special, CRint count=1, CRint comparison=0, CRint action=0);

        // getters and setters
        virtual int getLimit() const {return limit;};
        virtual void setLimit(CRint value) {limit = value; if (limit > 1) showProgress = true;};
        virtual int getCount() const {return count;};
        virtual void setCount(CRint value);
        virtual int getTimeLimit() const {return counter.getLimit();};
        virtual void setTimeLimit(CRint value) {counter.setLimit(value);};
        virtual int eventCount() const {return events.size();};
        virtual void addMilestone(CRint value) {milestones.push_back(value);};

        virtual int getType() const {return type;};

        virtual string getName() const {return name;};
        virtual void setName(CRstring newName) {if (newName.size() > 0) name = newName;};
        virtual string getDescription() const {return descr;};
        virtual void setDescription(CRstring newDescr) {if (newDescr.size() > 0) descr = newDescr;};
        virtual const AnimatedSprite* getIcon() const {return &icon;};
        virtual void setIcon(string fileName) {icon.loadFrames(fileName,2,1); icon.disableTransparentColour();};

        virtual bool getSecret() const {return secret;};
        virtual void setSecret(bool newState) {secret = newState;};
        virtual bool getStatus() const {return unlocked;};
        virtual Vector2di getPosition() const {return position;};
        virtual void setPosition(CRint newX, CRint newY) {setPosition(Vector2di(newX,newY));};
        virtual void setPosition(const Vector2di& newPos);
        virtual Vector2di getSize() const {return size;};
        virtual void setSize(CRint newW, CRint newH) {setSize(Vector2di(newW,newH));};
        virtual void setSize(const Vector2di& newSize) {size = newSize;};
        virtual void setShowProgress(CRbool newShow) {showProgress = newShow;};

        virtual void setParent(void* newParent) {parent = newParent;};
        virtual void* getParent() {return parent;};

        // display and layout
        #ifdef PENJIN_SDL
        virtual void render(SDL_Surface* screen);
        #else
        virtual void render();
        #endif

        // compare log with achievement events
        virtual bool check(const vector<Event*>& checkEvents);

    protected:
        // increase or decrease achievement count
        virtual void changeCount(const vector<Event*>& changeEvents);
        #ifdef PENJIN_SDL
        virtual void renderProgress(SDL_Surface* screen);
        #else
        virtual void renderProgress();
        #endif

        // display
        string name;
        string descr;
        AnimatedSprite icon;

        Vector2di position;
        Vector2di size;
        Text text;
        Rectangle bgBox;
        bool secret;
        bool showProgress;

        // data
        vector<Event*> events;
        int count;
        int limit;
        vector<int> milestones;
        bool unlocked;
        int type;
        CountDown counter;
        void* parent;
};

#endif // ACHIEVEMENT_H
