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
*/
#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "PenjinTypes.h"
#include "Texture.h"
#include "Random.h"
#include "NumberUtility.h"
class HeightMap
{
    public:
        HeightMap();
        HeightMap(CRuint width);
        ~HeightMap();

        void render();

        void setMapWidth(CRuint width)
        {
            mapWidth = width;
            vertices = NULL;
            vertices = new float*[width];
            for(int i = width-1; i >= 0; --i)
            {
                vertices[i] = NULL;
                vertices[i] = new float[width];
            }
        }
        void setTexture(const Texture& t){texture = t;}
        int loadTexture(string file){return texture.loadTexture(file);}

        void generateRandom(CRint minH, CRint maxH);

        void setHeight(CRint x, CRint z, CRfloat h){vertices[x][z] = h;}
        float getHeight(CRint x, CRint z)
        {
           if(x >= mapWidth || z >= mapWidth || x < 0 || z < 0)
                return 0.0f;
            return vertices[x][z];
        }
        uint getWidth(){return mapWidth;};
        float getInterpolatedHeight(CRfloat x, CRfloat y);
    private:
        void clear();
        Texture texture;
        uint mapWidth;
        float** vertices;
};

#endif // HEIGHTMAP_H
