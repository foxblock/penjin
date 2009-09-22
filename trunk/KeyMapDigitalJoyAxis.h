#ifndef KEYMAPDIGITALJOYAXIS_H
#define KEYMAPDIGITALJOYAXIS_H

#include "KeyMap.h"

class KeyMapDigitalJoyAxis : public KeyMap
{
    public:
        KeyMapDigitalJoyAxis();
        virtual ~KeyMapDigitalJoyAxis();

        KeyMapDigitalJoyAxis(CRstring SJ,CRint axis,CRint tiggerVal,CRuchar devID);

        void setBind(const SIMPLEJOY_MAP& t,CRint a,CRint tiggerVal,CRuchar devID){axis=a;target=t;deviceID = devID;}
        int getAxis()const{return axis;}
        int getTrigger()const{return trigger;}
    private:
        int axis;
        int trigger;
};

#endif // KEYMAPDIGITALJOYAXIS_H
