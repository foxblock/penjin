#ifndef KEYMAPSDLKEY_H
#define KEYMAPSDLKEY_H

#include "KeyMap.h"


class KeyMapSDLKey : public KeyMap
{
    public:
        KeyMapSDLKey();
        KeyMapSDLKey(CRstring SJ,CRstring SDL,CRuchar devID){setSDLKey(SDL);setSJMap(SJ);setDeviceID(devID);device = DEV_KEYBOARD;}
        virtual ~KeyMapSDLKey();

        void setBind(const SDLKey& k,const SIMPLEJOY_MAP& t,CRuchar devID){key=k;target=t;deviceID = devID;}
        SDLKey getkey()const{return key;}


    private:
        void setSDLKey(CRstring key);
        SDLKey key;
};

#endif // KEYMAPSDLKEY_H
