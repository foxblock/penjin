#ifndef KEYMAPMOUSEBUTTON_H
#define KEYMAPMOUSEBUTTON_H

#include "KeyMap.h"
namespace MouseButtons
{
    enum SDL_MOUSE_BUTTONS
    {
        SDL_MOUSE_NONE,
        SDL_MOUSE_LEFT,
        SDL_MOUSE_CENTRE,
        SDL_MOUSE_RIGHT
    };
}
using namespace MouseButtons;

class KeyMapMouseButton : public KeyMap
{
    public:
        KeyMapMouseButton();
        KeyMapMouseButton(CRuchar button,CRstring SJ,CRuchar devID);
        virtual ~KeyMapMouseButton();

        void setBind(const SDL_MOUSE_BUTTONS& b,const SIMPLEJOY_MAP& t,CRuchar devID){mouseButton=b;target=t;deviceID = devID;}
        SDL_MOUSE_BUTTONS getButton()const{return mouseButton;}

    private:
        void setMouseButton(CRuchar button);
        SDL_MOUSE_BUTTONS mouseButton;
};

#endif // KEYMAPMOUSEBUTTON_H
