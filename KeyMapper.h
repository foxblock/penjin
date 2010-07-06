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

#include "KeyMapKey.h"
#include "KeyMapMouseButton.h"
#include "KeyMapMouseAxis.h"
#include "KeyMapJoyButton.h"
#include "KeyMapJoyAxis.h"
#include "KeyMapDigitalJoyAxis.h"
#include "KeyMapHat.h"

#include "PenjinErrors.h"
class Parser;
using namespace PenjinErrors;
using namespace cmfFile;
#include <vector>

class KeyMapper
{
    public:
        KeyMapper();
        ~KeyMapper();

        size_t size()const{return keys.size();}
        KeyMap* getKeyMap(const CRuint mapping){return keys[mapping];}
        KeyMap* getKeyMap(const SIMPLEJOY_MAP& key);    //  Returns the keymap for this Command


        PENJIN_ERRORS loadControlMap(CRstring filename);    //  Save and load the actual mapping
        PENJIN_ERRORS loadControlMap(vector<string> lines);
        PENJIN_ERRORS saveControlMap(CRstring filename);

        PENJIN_ERRORS saveParserConfig(CRstring filename);  //  Save the parser validation file

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
        void setupParser();
        PENJIN_ERRORS parseData();
        void clearKeys();

        Parser* parse;
};

#endif // KEYMAPPER_H
