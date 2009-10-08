#ifndef KEYMAPHAT_H
#define KEYMAPHAT_H

#include "KeyMap.h"

class KeyMapHat : public KeyMap
{
    public:
        KeyMapHat();
        KeyMapHat(CRstring dir, CRstring SJ, CRuchar devID);
        KeyMapHat(const Uint8& dir,CRstring SJ, CRuchar devID);
        virtual ~KeyMapHat();

        void setBind(const Uint8& dir,CRstring SJ, CRuchar devID);
        Uint8 getDirection()const{return direction;}

    private:
        void setDirection(CRstring direction);
        Uint8 direction;
};

#endif // KEYMAPHAT_H
