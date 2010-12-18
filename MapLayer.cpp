/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/#include "MapLayer.h"
#include "PenjinTile.h"
MapLayer::MapLayer()
{
    //ctor
}

MapLayer::~MapLayer()
{
    //dtor
}

void MapLayer::render()
{
    // run through all indices
    //  TODO: work out which fall in screen range
    for(uint x = 0; x < data.size(); ++x)
    {
        for(uint y = 0; y < data.at(x).size(); ++y)
        {
            tiles.at(data.at(x,y))->render();
        }
    }
}

void MapLayer::update()
{
    //  We run through and update each tile once only
    int i = 0;
    while(tiles.at(i))
    {
        tiles.at(i)->update();
        ++i;
    }
}

