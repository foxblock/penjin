#include "KeyMapper.h"

KeyMapper::KeyMapper()
{
    //ctor
}

KeyMapper::~KeyMapper()
{
    //dtor
    for(int i = keys.size()-1; i>=0; --i)
    {
        if(keys[i])
            delete keys[i];
        keys[i]=NULL;
    }
    keys.clear();
}

PENJIN_ERRORS KeyMapper::loadControlMap(CRstring file)
{
    PENJIN_ERRORS result = parse.loadParserConfigFile(parse.getParentDirectory(file) + parse.getExtension(file) + ".prs");
    if(result != PENJIN_OK)
    {
        defaultMap();
        return result;
    }
    result = parse.createCommandList(file);
    if(result != PENJIN_OK)
    {
        defaultMap();
        return result;
    }
    Command temp;
    while(temp.commandType != CMF_END)
    {
        temp = parse.getNextCommand();
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

void KeyMapper::defaultMap()
{
#if defined(PLATFORM_PANDORA) || defined(PLATFORM_PC)
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("UP","UP",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("DOWN","DOWN",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("LEFT","LEFT",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("RIGHT","RIGHT",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapMouseAxis(0,"MOUSE_X",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapMouseAxis(1,"MOUSE_Y",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapMouseButton(0,"MOUSE_LEFT",0);
#endif

#ifdef PLATFORM_PC
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("A","X",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("B","Z",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("X","A",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("Y","S",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("L","Q",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("R","W",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("SELECT","RIGHT_SHIFT",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapSDLKey("START","RETURN",0);
#elif PLATFORM_GP2X
    int i = -1;
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"UP",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"UPLEFT",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"LEFT",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"DOWNLEFT",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"DOWN",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"DOWNRIGHT",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"RIGHT",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"UPRIGHT",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"START",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"SELECT",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"L",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"R",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"A",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"B",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"Y",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"X",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"VOLUP",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"VOLDOWN",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(++i,"CLICK",0);
#elif PLATFORM_PANDORA
//0 TOP/X,1 RIGHT/A,2 BOTTOM/B,3 LEFT/Y,4 SELECT,5 START,6 PANDORA,7 L,8 R,9 L2,10 R2,11 HOLD
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(0,"X",0);// TOP
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(1,"A",0);// RIGHT
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(2,"B",0);// BOTTOM
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(3,"Y",0);// LEFT
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(4,"SELECT",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(5,"START",0);
    keys.push_back(NULL);
    // TODO: Add Pandora Menu button support.! This is button 6
    keys[keys.size()-1] = new KeyMapJoyButton(7,"L",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyButton(8,"R",0);
    keys.push_back(NULL);
    //  NOTE: Buttons 9 and 10 are the Secondary Shoulder buttons. 
    //  These do not exist physically on a standard Pandora and for this reason are ommited.
    keys[keys.size()-1] = new KeyMapJoyAxis(0,"LEFTSTICK_X",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyAxis(1,"LEFTSTICK_Y",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyAxis(2,"RIGHTSTICK_X",0);
    keys.push_back(NULL);
    keys[keys.size()-1] = new KeyMapJoyAxis(3,"RIGHTSTICK_Y",0);
#endif
}

PENJIN_ERRORS KeyMapper::mapKey(CRuchar id)
{
    Command temp;
    PENJIN_ERRORS result;
    while(temp.commandType != CMF_DEVICE_END)
    {
        temp = parse.getNextCommand();
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
    PENJIN_ERRORS result;
    while(temp.commandType != CMF_DEVICE_END)
    {
        temp = parse.getNextCommand();
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
    PENJIN_ERRORS result;
    while(temp.commandType != CMF_DEVICE_END)
    {
        temp = parse.getNextCommand();
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
