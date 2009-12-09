#ifndef STATECOLOUR_H
#define STATECOLOUR_H

#include "PenjinStates.h"

#include "GFX.h"
#include "Text.h"
#include "Rectangle.h"

class StateColour : public BaseState
{
    public:
        StateColour();
        virtual ~StateColour();

        virtual void init();
        virtual void render();
        virtual void userInput();
        virtual void update();

    private:
        Colour col;
        Rectangle rect;
        Text text;
        int current;
};

#endif // STATECOLOUR_H
