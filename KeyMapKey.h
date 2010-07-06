#ifndef KEYMAPKEY_H
#define KEYMAPKEY_H

#include "KeyMap.h"


class KeyMapKey : public KeyMap
{
    public:
        KeyMapKey();
        KeyMapKey(CRstring SJ,CRstring k,CRuchar devID){setKey(k);setSJMap(SJ);setDeviceID(devID);device = DEV_KEYBOARD;}
        KeyMapKey(CRstring k);
        #if defined(PLATFORM_PANDORA) && (defined(PENJIN_ES) || defined(PENJIN_ES2))
            KeyMapKey(__u16 k);
        #else
            KeyMapKey(SDLKey k);
        #endif
        virtual ~KeyMapKey();

        #if defined(PLATFORM_PANDORA) && (defined(PENJIN_ES) || defined(PENJIN_ES2))
            void setBind(const __u16& k,const SIMPLEJOY_MAP& t,CRuchar devID){key=k;target=t;deviceID = devID;}
            __u16 getKey()const{return key;}
        #else
            void setBind(const SDLKey& k,const SIMPLEJOY_MAP& t,CRuchar devID){key=k;target=t;deviceID = devID;}
            SDLKey getKey()const{return key;}
        #endif

    private:
        void setKey(CRstring key);
        #if defined(PLATFORM_PANDORA) && (defined(PENJIN_ES) || defined(PENJIN_ES2))
            __u16 key;
        #else
            SDLKey key;
        #endif
};

#endif // KEYMAPKEY_H
