#include "Model3ds.h"
#include <lib3ds/mesh.h>
#include <lib3ds/file.h>
#include <string.h>
#include "Texture.h"
using namespace PenjinErrors;
Model3ds::Model3ds()
{
    setNULL();
}

Model3ds::~Model3ds()
{
    clear();
}

void Model3ds::setNULL()
{
    vertices = NULL;
    normals = NULL;
    coords = NULL;
}

void Model3ds::clear()
{
    if(vertices)
    {
        delete [] vertices;
        vertices = NULL;
    }
	if(normals)
	{
        delete [] normals;
        normals = NULL;
	}
	if(coords)
	{
        delete [] coords;
        coords = NULL;
	}
}

PENJIN_ERRORS Model3ds::loadModel(const string& filename)
{
	Lib3dsFile* file = NULL;
	file = lib3ds_file_load(filename.c_str());

    if(!file)
        return PENJIN_FILE_NOT_FOUND;
	//Count number of faces
	numFaces = 0;
	for(Lib3dsMesh* mesh = file->meshes ; mesh != NULL ; mesh = mesh->next)
		numFaces += mesh->faces;

	//Allocate memory for vertex and normal arrays
	if(vertices)
	{
	    clear();
	    setNULL();
    }
        vertices = new ModelVector3f[numFaces * 3];
        normals = new ModelVector3f[numFaces * 3];
        coords = new float[numFaces * 3 * 2];

	//Fill vertex and normal arrays
	uint finishedFaces = 0;
	uint uvCounter = 0;
	for(Lib3dsMesh* mesh = file->meshes ; mesh != NULL ; mesh = mesh->next)
	{
		lib3ds_mesh_calculate_normals(mesh, &normals[finishedFaces*3]);
		for(uint currentFace = 0 ; currentFace < mesh->faces ; ++currentFace)
		{
			Lib3dsFace* face = &mesh->faceL[currentFace];
			for(uint i = 0 ; i < 3 ; ++i)
			{
				memcpy(&vertices[finishedFaces*3 + i], mesh->pointL[face->points[i]].pos, sizeof(Lib3dsVector));
				coords[uvCounter    ] = mesh->texelL[face->points[i]][0];
				coords[uvCounter + 1] = mesh->texelL[face->points[i]][1];
				uvCounter += 2;
			}
			++finishedFaces;
		}
	}

    if(file)
        lib3ds_file_free(file);

    return PENJIN_OK;
}

PENJIN_ERRORS Model3ds::loadTexture(CRstring filename)
{
    if(texture)
        delete texture;
    texture = NULL;
    texture = new Texture;
    return texture->loadTexture(filename);
}

void Model3ds::render()
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

void Model3ds::update()
{}
