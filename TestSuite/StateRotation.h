#ifndef STATEROTATION_H
#define STATEROTATION_H

#include "PenjinStates.h"

#include "Sprite.h"
#include "Text.h"
#include "Timer.h"

class StateRotation : public BaseState
{
    public:
        StateRotation();
        virtual ~StateRotation();

        virtual void init();

        virtual void render();
        virtual void update();
        virtual void userInput();

    private:
        Sprite spr;
        Point2di txtPos;
        Text txt;
        Timer timer;
        int angle;
        bool autoRot;
};

#endif // STATEROTATION_H
