#ifndef GRID_H
#define GRID_H

//  A simple class to draw gridlines in X and Z directions to help with spacial visualisation
#include "PenjinTypes.h"
#include "Colour.h"
#include <vector>

class Grid
{
    public:
        Grid();
        ~Grid();

        template <class T>
        void setOrigin(const T& o){origin.x = o.x; origin.y = o.y;}

        template <class T>
        void setNumTiles(const T& t){numTiles.x = t.x; numTiles.y = t.y;}

        void setColour(const Colour& c){colour = c;}

        void render();
        void refresh();

    private:
        Vector2di origin;       //  This is the nearest whole point where the gridlines will originate from
        Point2di numTiles;      //  This is the number of tiles in each direction to render
        Colour colour;
        vector <Point3di> lines;
};

#endif // GRID_H
