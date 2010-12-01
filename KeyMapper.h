/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
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
        PENJIN_ERRORS loadControlMap(const vector<string>& lines);
        PENJIN_ERRORS saveControlMap(CRstring filename);

        PENJIN_ERRORS saveParserConfig(CRstring filename);  //  Save the parser validation file

        void loadDefaultMap(){defaultMap();}
        std::vector <KeyMap*> keys;
    private:
        // Disabled to prevent double freed pointers.
        KeyMapper(const KeyMapper& BlingRef);
        KeyMapper& operator=(const KeyMapper& BlingRef);
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
