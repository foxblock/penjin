#ifndef STATEJOYMAP_H
#define STATEJOYMAP_H

#include "PenjinStates.h"
class AnimatedSprite;
class Text;
class Parser;
class Timer;
class Line;
class Rectangle;

class StateJoyMap : public BaseState
{
    public:
        StateJoyMap();
        virtual ~StateJoyMap();

        virtual void init();

        virtual void render();
        virtual void update();
        virtual void userInput();

    private:
        void renderCross(Vector2di centre, CRint size);
        Vector2di cursorPos;        //  Mouse cursor
        Vector2di joyPos[2];        //  joystick positions
        Vector2di lastJoyPos[2];    //  The last positions
        Vector2di joyBoxStart[2];   //  Box Area for joyBox
        Vector2di joyBoxEnd[2];   //  "" "" "" ""
        AnimatedSprite* buttons;
        Text* text;
        Parser* parse;
        Timer* timer;
        Line* line;
        Rectangle* rect;
        uint currentButton;
        bool testMode;          //  toggles test mode to test the joy mapping.

        Vector2di joyCentre[2];    //  centre position for each joy test area
};

#endif // STATEJOYMAP_H
