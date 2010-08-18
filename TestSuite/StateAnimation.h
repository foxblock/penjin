#ifndef STATEANIMATION_H
#define STATEANIMATION_H

#include "PenjinStates.h"

class AnimatedSprite;
#include "Text.h"
/*
ABOUT: This class is designed to test all animated functionality.
A button toggles through the different animation objects and frame load methods
L button toggles looping
R button toggles reverse play
B cycles fps scalers in timer.
*/

class StateAnimation : public BaseState
{
    public:
        StateAnimation();
        virtual ~StateAnimation();

        virtual void init();

        virtual void render();
        virtual void userInput();
        virtual void unlimitedUpdate();

    private:
        // Animation object
        AnimatedSprite* anim;

        //  Animation properties
        bool looping;       //  looping on or off.
        int playMode;       //  play normal, reversed or pulsing
        bool paused;        //  paused state
        enum ANIM_MODE
        {
            ANIM_TILE=0,
            ANIM_FRAMES,
            SPR_TILE,
            SPR_FRAMES
        };
        int animMode; // current mode to display.
        int fpsMode;

        Text text;          //  Status text.

        void changeAnimMode();
        void setLooping();
        void cyclePlayMode();
        void cycleTimerMode();
        void setFPS();
        void togglePause();
        void rewind();
        void clear();
};

#endif // STATEANIMATION_H
