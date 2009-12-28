#ifndef KEYMAPDIGITALJOYAXIS_H
#define KEYMAPDIGITALJOYAXIS_H

#include "KeyMap.h"

class KeyMapDigitalJoyAxis : public KeyMap
{
    public:
        KeyMapDigitalJoyAxis();
        virtual ~KeyMapDigitalJoyAxis();

        KeyMapDigitalJoyAxis(CRstring SJ,CRint axis,CRint triggerVal,CRuchar devID);

        void setBind(const SIMPLEJOY_MAP& t,CRint a,CRint triggerVal,CRuchar devID){axis=a;target=t;trigger=triggerVal;deviceID = devID;}
        int getAxis()const{return axis;}
        int getTrigger()const{return trigger;}
    private:
        int axis;
        int trigger;
};

#endif // KEYMAPDIGITALJOYAXIS_H
