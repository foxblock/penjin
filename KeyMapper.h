#ifndef KEYMAPPER_H
#define KEYMAPPER_H

namespace cmfFile
{
    enum CMF_FILE
    {
        CMF_DEVICE,
        CMF_BUTTON,
        CMF_KEY,
        CMF_AXIS,
        CMF_DIGITAL_AXIS,
        CMF_HAT,
        CMF_DEVICE_END,
        CMF_END
    };
}

#include "KeyMapSDLKey.h"
#include "KeyMapMouseButton.h"
#include "KeyMapMouseAxis.h"
#include "KeyMapJoyButton.h"
#include "KeyMapJoyAxis.h"
#include "KeyMapDigitalJoyAxis.h"
#include "KeyMapHat.h"

#include "Parser.h"
using namespace PenjinErrors;
using namespace cmfFile;
#include <vector>

class KeyMapper
{
    public:
        KeyMapper();
        ~KeyMapper();

        int size(){return keys.size();}
        KeyMap* getKeyMap(const CRuint mapping){return keys[mapping];}
        KeyMap* getKeyMap(const SIMPLEJOY_MAP& key);    //  Returns the keymap for this Command


        PENJIN_ERRORS loadControlMap(CRstring filename);
        void loadDefaultMap(){defaultMap();}
        std::vector <KeyMap*> keys;
    private:
        PENJIN_ERRORS mapMouse(CRuchar id);
        PENJIN_ERRORS mapJoy(CRuchar id);
        PENJIN_ERRORS mapKey(CRuchar id);
        PENJIN_ERRORS mapWii(CRuchar id);
        PENJIN_ERRORS mapWiiClassic(CRuchar id);
        PENJIN_ERRORS mapWiitar(CRuchar id);
        void defaultMap();

        Parser parse;
};

#endif // KEYMAPPER_H
