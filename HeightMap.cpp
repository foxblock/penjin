#include "HeightMap.h"

HeightMap::HeightMap()
{
    //ctor
    mapWidth=0;
    vertices = NULL;
}

HeightMap::HeightMap(CRuint width)
{
    setMapWidth(width);
}

HeightMap::~HeightMap()
{
    //dtor
    clear();
}

void HeightMap::clear()
{
    for(int i = mapWidth-1; i >= 0; --i)
    {
        if(vertices[i])
        {
            delete [] vertices[i];
            vertices[i] = NULL;
        }
    }
    if(vertices)
    {
        delete [] vertices;
        vertices = NULL;
    }
    mapWidth = 0;
}

void HeightMap::generateRandom(CRint min, CRint max)
{
    Random::setLimits(min,max);

    for(int i = mapWidth-1; i >=0; --i)
        for(int j = mapWidth-1; j >=0; --j)
            setHeight(i,j,Random::nextFloat());
}

float HeightMap::getInterpolatedHeight(CRfloat x, CRfloat y)
{
    /*
	p1--p2
	|    |
	p4--p3
	*/
	if(x >= mapWidth-1 || y >= mapWidth-1 || x < 0 || x < 0)
        return 0.0f;
	float p1 = vertices[(int)x][(int)y+1];
	float p2 = vertices[(int)x+1][(int)y+1];
	//float p3 = vertices[((int)x+1)+((int)y*mapWidth)];
	float p4 = vertices[(int)x][(int)y];

    float stepX = x - (int)x;
	float stepY = y - (int)y;

    float resultA = NumberUtility::linearInterpolate(p1,p2,stepX);
    float resultB = NumberUtility::linearInterpolate(p1,p4,stepY);

    return ((resultA + resultB) * 0.5f);
}
void HeightMap::render()
{
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
	glScalef(1.0,1.0,-1.0);

	glBegin(GL_TRIANGLES);
        for (uint x = 0; x < mapWidth-1; x++)
        {
            for (uint z = 0; z < mapWidth-1; z++)
            {
                    // draw two triangles
                    //1
                    glTexCoord2f((float)x/(float)mapWidth,(float)(z+1)/(float)mapWidth);
                    glVertex3f(x,vertices[x][z+1],z+1);
                    //4
                    glTexCoord2f((float)x/(float)mapWidth,(float)z/(float)mapWidth);
                    glVertex3f(x,vertices[x][z],z);
                    //2
                    glTexCoord2f((float)(x+1)/(float)mapWidth,(float)(z+1)/(float)mapWidth);
                    glVertex3f(x+1,vertices[x+1][z+1],(z+1));




                    // next triangle
                    //3
                    glTexCoord2f((float)(x+1)/(float)mapWidth,(float)z/(float)mapWidth);
                    glVertex3f(x+1,vertices[x+1][z],z);
                    //2
                    glTexCoord2f((float)(x+1)/(float)mapWidth,(float)(z+1)/(float)mapWidth);
                    glVertex3f(x+1,vertices[x+1][z+1],(z+1));
                    //4
                    glTexCoord2f((float)x/(float)mapWidth,(float)z/(float)mapWidth);
                    glVertex3f(x,vertices[x][z],z);




            }
        }
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
