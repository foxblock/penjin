#ifndef KEYMAPMOUSEAXIS_H
#define KEYMAPMOUSEAXIS_H

#include "KeyMap.h"
namespace MouseAxes
{
    enum SDL_MOUSE_AXES
    {
        SDL_MOUSE_NONE=-1,
        SDL_MOUSE_X,
        SDL_MOUSE_Y
        //SDL_MOUSE_WHEEL,
    };
}
using namespace MouseAxes;

class KeyMapMouseAxis : public KeyMap
{
    public:
        KeyMapMouseAxis();
        KeyMapMouseAxis(CRuchar axis,CRstring SJ,CRuchar devID);
        virtual ~KeyMapMouseAxis();

        void setBind(CRuchar a,const SIMPLEJOY_MAP& t,CRuchar devID){mouseAxis=a;target=t;deviceID = devID;}
        uchar getAxis()const{return mouseAxis;}
    private:
        uchar mouseAxis;

};

#endif // KEYMAPMOUSEAXIS_H
