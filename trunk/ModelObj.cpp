#include "ModelObj.h"

ModelObj::ModelObj()
{
    //ctor
    normals = NULL;
    vertices = NULL;
    texCoords = NULL;
}

ModelObj::~ModelObj()
{
    //dtor
    if(normals)
        delete [] normals;
    if(vertices)
        delete [] vertices;
    if(texCoords)
        delete [] texCoords;
}

int ModelObj::loadModel(CRstring fName)
{

}

void ModelObj::render()
{
    glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, normals);
	glTexCoordPointer(2, GL_FLOAT, 0, coords);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());

	glDrawArrays(GL_TRIANGLES, 0, numFaces*3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisable(GL_TEXTURE_2D);
}

