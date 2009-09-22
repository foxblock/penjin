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
