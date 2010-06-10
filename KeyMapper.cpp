#include "KeyMapper.h"
#include "Parser.h"
KeyMapper::KeyMapper()
{
    //ctor
    parse = new Parser;
}

KeyMapper::~KeyMapper()
{
    //dtor
    clearKeys();
    delete parse;
}

void KeyMapper::clearKeys()
{
    for(int i = keys.size()-1; i>=0; --i)
    {
        if(keys[i])
            delete keys[i];
        keys[i]=NULL;
    }
    keys.clear();
}

PENJIN_ERRORS KeyMapper::loadControlMap(vector<string> lines)
{
    parse->loadCommandList(lines);
    return parseData();
}

PENJIN_ERRORS KeyMapper::loadControlMap(CRstring file)
{
    PENJIN_ERRORS result = parse->loadParserConfig(parse->getParentDirectory(file) + parse->getExtension(file) + ".prs");
    if(result != PENJIN_OK)
    {
        setupParser();
        result = PENJIN_OK;
        //defaultMap();
        //return result;
    }
    result = parse->loadCommandList(file);
    if(result != PENJIN_OK)
    {
        defaultMap();
        result = PENJIN_OK;
        //return result;
    }
    return parseData();
}

PENJIN_ERRORS KeyMapper::parseData()
{
    PENJIN_ERRORS result = PENJIN_OK;
    Command temp;
    while(temp.commandType != CMF_END)
    {
        temp = parse->getNextCommand();
        if(temp.commandType != CMF_DEVICE)
            break;
        else
        {
            if(!temp.params.empty())
            {
                string dev = temp.params[0].getString();
                #ifdef PENJIN_FIXED
                    uchar devID = fixedpoint::fix2int(temp.params[1].getFloat());
                #else
                    uchar devID = temp.params[1].getFloat();
                #endif
                if(dev == "KEYBOARD")
                    result = mapKey(devID);
                else if(dev == "MOUSE")
                    result = mapMouse(devID);
                else if(dev == "JOYSTICK")
                    result = mapJoy(devID);
                else if(dev == "WII_REMOTE")
                    result = mapWii(devID);
                else if(dev == "WII_CLASSIC")
                    result = mapWiiClassic(devID);
                else if(dev == "WII_GUITAR")
                    result = mapWiitar(devID);
                if(result != PENJIN_OK)
                    return result;
            }
        }
    }
    return result;
}

PENJIN_ERRORS KeyMapper::saveControlMap(CRstring file)
{
    return parse->saveCommandList(file);
}

PENJIN_ERRORS KeyMapper::saveParserConfig(CRstring file)
{
    return parse->saveParserConfig(file);
}

void KeyMapper::setupParser()
{
    //  first spit out the standard CMF data
    vector<string> CMF;
    CMF.push_back(";   Control Map Parser Config File");
    CMF.push_back("DEVICE:1,1;");
    CMF.push_back("BUTTON:1,1;");
    CMF.push_back("KEY:2,0;");
    CMF.push_back("AXIS:1,1;");
    CMF.push_back("DIGITAL_AXIS:1,2;");
    CMF.push_back("HAT:2,0;");
    CMF.push_back("DEVICE_END:0,0;");
    CMF.push_back("END:0,0;");
    parse->loadParserConfig(CMF);
    //defaultMap();
}

void KeyMapper::defaultMap()
{
    clearKeys();
    setupParser();
    vector<string> CMF;
    CMF.push_back(";   Default Penjin Control Map");
/*
;   FAILSAFE - uses keyboard
;   DEVICE:type,id;
DEVICE:KEYBOARD,0;
;   KEY:action,key;
KEY:UP,UP;
KEY:DOWN,DOWN;
KEY:LEFT,LEFT;
KEY:RIGHT,RIGHT;
KEY:A,x;
KEY:B,z;
KEY:X,a;
KEY:Y,s;
KEY:L,q;
KEY:R,w;
KEY:SELECT,RIGHT_SHIFT;
KEY:START,RETURN;
DEVICE_END:;
DEVICE:MOUSE,0;
BUTTON:MOUSE_LEFT,0;
AXIS:MOUSE_X,0;
AXIS:MOUSE_Y,1;
DEVICE_END:;
END:;
*/
#if defined(PLATFORM_PANDORA) || defined(PLATFORM_PC)
    CMF.push_back("DEVICE:KEYBOARD,0;");
            CMF.push_back("KEY:UP,UP;");
            CMF.push_back("KEY:DOWN,DOWN;");
            CMF.push_back("KEY:LEFT,LEFT;");
            CMF.push_back("KEY:RIGHT,RIGHT;");
    CMF.push_back("DEVICE_END:;");
    CMF.push_back("DEVICE:MOUSE,0;");
        CMF.push_back("BUTTON:MOUSE_LEFT,0;");
        CMF.push_back("AXIS:MOUSE_X,0;");
        CMF.push_back("AXIS:MOUSE_Y,1;");
    CMF.push_back("DEVICE_END:;");
#endif

#ifdef PLATFORM_PC
    CMF.push_back("DEVICE:KEYBOARD,0;");
            CMF.push_back("KEY:A,x;");
            CMF.push_back("KEY:B,z;");
            CMF.push_back("KEY:X,a;");
            CMF.push_back("KEY:Y,s;");
            CMF.push_back("KEY:L,q;");
            CMF.push_back("KEY:R,w;");
            CMF.push_back("KEY:SELECT,RIGHT_SHIFT;");
            CMF.push_back("KEY:START,RETURN;");
    CMF.push_back("DEVICE_END:;");
#elif PLATFORM_GP2X
    CMF.push_back("DEVICE:JOYSTICK,0;");
            CMF.push_back("BUTTON:UP,0;");
            CMF.push_back("BUTTON:UPLEFT,1;");
            CMF.push_back("BUTTON:LEFT,2;");
            CMF.push_back("BUTTON:DOWNLEFT,3;");
            CMF.push_back("BUTTON:DOWN,4;");
            CMF.push_back("BUTTON:DOWNRIGHT,5;");
            CMF.push_back("BUTTON:RIGHT,6;");
            CMF.push_back("BUTTON:UPRIGHT,7;");
            CMF.push_back("BUTTON:START,8;");
            CMF.push_back("BUTTON:SELECT,9;");
            CMF.push_back("BUTTON:L,10;");
            CMF.push_back("BUTTON:R,11;");
            CMF.push_back("BUTTON:A,12;");
            CMF.push_back("BUTTON:B,13;");
            CMF.push_back("BUTTON:X,14;");
            CMF.push_back("BUTTON:Y,15;");
            CMF.push_back("BUTTON:VOLUP,16;");
            CMF.push_back("BUTTON:VOLDOWN,17;");
            CMF.push_back("BUTTON:CLICK,18;");
    CMF.push_back("DEVICE_END:;");
#elif PLATFORM_PANDORA
//0 TOP/X,1 RIGHT/A,2 BOTTOM/B,3 LEFT/Y,4 SELECT,5 START,6 PANDORA,7 L,8 R,9 L2,10 R2,11 HOLD
/*
 EvilDragon: Buttons are: START = LALT, SELECT = LCTRL, L = RSHIFT, R = RCTRL and on the button side:
EvilDragon: Top Button = Page Up, Lower Button = Page Down, Left Button = Prior, Right Button = Next
EvilDragon: DPad works, that's Cursor Up, Down, Left, Right.
*/
    CMF.push_back("DEVICE:KEYBOARD,0;");
            CMF.push_back("KEY:A,HOME;");
            CMF.push_back("KEY:B,END;");
            CMF.push_back("KEY:X,PAGEDOWN;");
            CMF.push_back("KEY:Y,PAGEUP;");
            CMF.push_back("KEY:L,RIGHT_SHIFT;");
            CMF.push_back("KEY:R,RIGHT_CTRL;");
            CMF.push_back("KEY:SELECT,LEFT_CTRL;");
            CMF.push_back("KEY:START,LEFT_ALT;");
    CMF.push_back("DEVICE_END:;");
    CMF.push_back("DEVICE:JOYSTICK,0;");
            CMF.push_back("AXIS:LEFTSTICK_X,0;");
            CMF.push_back("AXIS:LEFTSTICK_Y,1;");
            CMF.push_back("AXIS:RIGHTSTICK_X,2;");
            CMF.push_back("AXIS:RIGHTSTICK_Y,3;");
    CMF.push_back("DEVICE_END:;");
#elif PLATFORM_WII
    #ifdef PENJIN_SDL_INPUT
        int i = -1;
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"A",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"B",0);
        /*keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"1",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"2",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"+",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"-",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"HOME",0);*/

        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapHat("UP","UP",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapHat("DOWN","DOWN",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapHat("LEFT","LEFT",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapHat("RIGHT","RIGHT",0);
    #else
        // Use the Wii controls directly.
    #endif
#endif
    CMF.push_back("END:;");
    loadControlMap(CMF);
}

PENJIN_ERRORS KeyMapper::mapKey(CRuchar id)
{
    Command temp;
    PENJIN_ERRORS result = PENJIN_OK;
    while(temp.commandType != CMF_DEVICE_END)
    {
        temp = parse->getNextCommand();
        if(temp.commandType == CMF_DEVICE_END)
            break;
        result = PENJIN_ERROR;
        if(temp.commandType == CMF_KEY)
        {
            if(!temp.params.empty())
            {
                KeyMapSDLKey* t = NULL;
                t = new KeyMapSDLKey(temp.params[0].getString(),temp.params[1].getString(),id);
                keys.push_back(t);
                result = PENJIN_OK;
            }
        }
    }
    return result;
}

PENJIN_ERRORS KeyMapper::mapMouse(CRuchar id)
{
    Command temp;
    PENJIN_ERRORS result = PENJIN_OK;
    while(temp.commandType != CMF_DEVICE_END)
    {
        temp = parse->getNextCommand();
        if(temp.commandType == CMF_DEVICE_END)
            break;
        result = PENJIN_ERROR;
        if(temp.commandType == CMF_BUTTON)
        {
            if(!temp.params.empty())
            {
                KeyMapMouseButton* t = NULL;
                #ifdef PENJIN_FIXED
                    t = new KeyMapMouseButton(fixedpoint::fix2int(temp.params[1].getFloat()),temp.params[0].getString(),id);
                #else
                    t = new KeyMapMouseButton(temp.params[1].getFloat(),temp.params[0].getString(),id);
                #endif
                keys.push_back(t);
                result = PENJIN_OK;
            }
        }
        else if(temp.commandType == CMF_AXIS)
        {
            if(!temp.params.empty())
            {
                KeyMapMouseAxis* t = NULL;
                #ifdef PENJIN_FIXED
                    t = new KeyMapMouseAxis(fixedpoint::fix2int(temp.params[1].getFloat()),temp.params[0].getString(),id);
                #else
                    t = new KeyMapMouseAxis(temp.params[1].getFloat(),temp.params[0].getString(),id);
                #endif
                keys.push_back(t);
                result = PENJIN_OK;
            }
        }
    }
    return result;
}

PENJIN_ERRORS KeyMapper::mapJoy(CRuchar id)
{
    Command temp;
    PENJIN_ERRORS result = PENJIN_OK;
    while(temp.commandType != CMF_DEVICE_END)
    {
        temp = parse->getNextCommand();
        if(temp.commandType == CMF_DEVICE_END)
            break;
        result = PENJIN_ERROR;
        if(!temp.params.empty())
        {
            if(temp.commandType == CMF_BUTTON)
            {
                KeyMapJoyButton* t = NULL;
                #ifdef PENJIN_FIXED
                    t = new KeyMapJoyButton(fixedpoint::fix2int(temp.params[1].getFloat()),temp.params[0].getString(),id);
                #else
                    t = new KeyMapJoyButton(temp.params[1].getFloat(),temp.params[0].getString(),id);
                #endif
                keys.push_back(t);
                result = PENJIN_OK;
            }
            else if(temp.commandType == CMF_AXIS)
            {
                KeyMapJoyAxis* t = NULL;
                #ifdef PENJIN_FIXED
                    t = new KeyMapJoyAxis(fixedpoint::fix2int(temp.params[1].getFloat()),temp.params[0].getString(),id);
                #else
                    t = new KeyMapJoyAxis(temp.params[1].getFloat(),temp.params[0].getString(),id);
                #endif
                keys.push_back(t);
                result = PENJIN_OK;
            }
            else if(temp.commandType == CMF_HAT)
            {
                KeyMapHat* t = NULL;
                t = new KeyMapHat(temp.params[1].getString(),temp.params[0].getString(),id);
                keys.push_back(t);
                result = PENJIN_OK;
            }
            else if(temp.commandType == CMF_DIGITAL_AXIS)
            {
                KeyMapDigitalJoyAxis* t = NULL;
                #ifdef PENJIN_FIXED
                    t = new KeyMapDigitalJoyAxis(temp.params[0].getString(),fixedpoint::fix2int(temp.params[1].getFloat()),fixedpoint::fix2int(temp.params[2].getFloat()),id);
                #else
                    t = new KeyMapDigitalJoyAxis(temp.params[0].getString(),temp.params[1].getFloat(),temp.params[2].getFloat(),id);
                #endif
                keys.push_back(t);
                result = PENJIN_OK;
            }
        }
    }
    return result;
}

PENJIN_ERRORS KeyMapper::mapWii(CRuchar id)
{
    //  TODO Add Wiimapping
    return PENJIN_FUNCTION_IS_STUB;
}

PENJIN_ERRORS KeyMapper::mapWiiClassic(CRuchar id)
{
    //  TODO Add Wiimapping
    return PENJIN_FUNCTION_IS_STUB;
}

PENJIN_ERRORS KeyMapper::mapWiitar(CRuchar id)
{
    //  TODO Add Wiimapping
    return PENJIN_FUNCTION_IS_STUB;
}
