#ifndef StateRaycast_H
#define StateRaycast_H

#include "PenjinStates.h"

#include "Raycast.h"
#include "Background.h"


class StateRaycast : public BaseState
{
    public:
        StateRaycast();
        virtual ~StateRaycast();

        virtual void init();
        virtual void render();
        virtual void userInput();

    private:

        Raycast* m_Engine;

        Background m_Border;
};

#endif // StateRaycast_H
