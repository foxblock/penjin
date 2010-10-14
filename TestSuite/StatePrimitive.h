#ifndef STATEPRIMITIVE_H
#define STATEPRIMITIVE_H

#include "PenjinStates.h"

class Pixel;//#include "Pixel.h"
class Line;//#include "Line.h"
class Rectangle;//#include "Rectangle.h"
#include "Random.h"
class Text;//#include "Text.h"

/*
ABOUT: This class is designed to test the 2D Primitive provided by Penjin.
A
L
R
B
SELECT - Clear Screen
UP/DOWN - Line Thickness
LEFT/RIGHT - Primitive Type
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
        Text* text;
        Pixel* pix;
        Line* line;
        Rectangle* rect;
        //Ellipse elli;
        PRIM_MODE primMode;
        uint numPrims;
        int thickness;
};

#endif // STATEPRIMITIVE_H
