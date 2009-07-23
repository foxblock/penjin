#ifndef KEYMAPJOYBUTTON_H
#define KEYMAPJOYBUTTON_H

#include "KeyMap.h"

class KeyMapJoyButton : public KeyMap
{
    public:
        KeyMapJoyButton();
        KeyMapJoyButton(CRint button,CRstring SJ,CRuchar devID);
        virtual ~KeyMapJoyButton();

        void setBind(CRint b,const SIMPLEJOY_MAP& t,CRuchar devID){joyButton=b;target=t;deviceID = devID;}
        int getButton()const{return joyButton;}

    private:
        int joyButton;
};

#endif // KEYMAPJOYBUTTON_H
