#ifndef TILEMAP_H
#define TILEMAP_H

#include "Image.h"

/* This class loads a tilesheet and a map file
The map has info on the properties of each tile in the tilesheet
and also their arrangement in a grid

*/
class TileMap : public Image
{
    public:
        TileMap();
        ~TileMap();
    protected:
    private:
};

#endif // TILEMAP_H
