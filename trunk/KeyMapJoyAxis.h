#ifndef KEYMAPJOYAXIS_H
#define KEYMAPJOYAXIS_H

#include "KeyMap.h"


class KeyMapJoyAxis : public KeyMap
{
    public:
        KeyMapJoyAxis();
        virtual ~KeyMapJoyAxis();

        KeyMapJoyAxis(CRint axis,CRstring SJ,CRuchar devID);
        void setBind(CRint a,const SIMPLEJOY_MAP& t,CRuchar devID){joyAxis=a;target=t;deviceID = devID;}
        int getAxis()const{return joyAxis;}
    private:
        int joyAxis;
};

#endif // KEYMAPJOYAXIS_H
