#ifndef STATEPRIMITIVE_H
#define STATEPRIMITIVE_H

#include "PenjinStates.h"

#include "Pixel.h"
#include "Line.h"
#include "Rectangle.h"
#include "Random.h"
#include "Text.h"

/*
ABOUT: This class is designed to test the 2D Primitive provided by Penjin.
A
L
R
B
*/

class StatePrimitive : public BaseState
{
    public:
        StatePrimitive();
        virtual ~StatePrimitive();

        virtual void init();

        virtual void render();
        virtual void userInput();
        virtual void update();

    private:
        enum PRIM_MODE
        {
            PIXEL,
            LINE,
            RECT,
            //ELLIPSE,
            RAND_PRIM,
            NO_PRIM
        };
        Text text;
        Pixel pix;
        Line line;
        Rectangle rect;
        //Ellipse elli;
        PRIM_MODE primMode;
        uint numPrims;
};

#endif // STATEPRIMITIVE_H
