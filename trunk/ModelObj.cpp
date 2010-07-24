#include "ModelObj.h"
#include "objloader/model_obj.h"

#ifdef PENJIN_GL
    #include <SDL/SDL_opengl.h>
#endif
#if defined (PENJIN_ES) || defined (PENJIN_ES2)
    #ifdef PENJIN_ES
        #include <GLES/gl.h>
    #elif PENJIN_ES2
        #include <GLES2/gl2.h>
    #endif
#endif

#include "Texture.h"
ModelObj::ModelObj()
{
    //ctor
    model = NULL;
    texture = NULL;
    bumpMap = NULL;
   // normalMap = NULL;
}

ModelObj::~ModelObj()
{
    //dtor
    if(model)
        model->destroy();
    delete model;
    delete texture;
    delete bumpMap;
   // delete normalMap;
}

PENJIN_ERRORS ModelObj::loadModel(CRstring fName)
{
    if(model)
            model->destroy();
    delete model;
    model = new ModelOBJ;
    if(!model->import(fName.c_str()))
        return PENJIN_ERROR;

    model->normalize();

    //  now check for textures
    const ModelOBJ::Material *pMaterial = 0;
    std::string::size_type offset = 0;
    std::string filename;
    for (int i = 0; i < model->getNumberOfMaterials(); ++i)
    {
        pMaterial = &model->getMaterial(i);

        // Look for and load any diffuse color map textures.

        if (pMaterial->colorMapFilename.empty())
            continue;

        // Try load the texture using the path in the .MTL file.
        loadTexture(pMaterial->colorMapFilename);

        if (!texture)
        {
            offset = pMaterial->colorMapFilename.find_last_of('\\');

            if (offset != std::string::npos)
                filename = pMaterial->colorMapFilename.substr(++offset);
            else
                filename = pMaterial->colorMapFilename;

            // Try loading the texture from the same directory as the OBJ file.
            loadTexture((model->getPath() + filename));
        }

        // Look for and load any bump map textures.
        if (pMaterial->bumpMapFilename.empty())
            continue;

        // Try load the texture using the path in the .MTL file.
        loadBumpMap(pMaterial->bumpMapFilename);

        if (!bumpMap)
        {
            offset = pMaterial->bumpMapFilename.find_last_of('\\');

            if (offset != std::string::npos)
                filename = pMaterial->bumpMapFilename.substr(++offset);
            else
                filename = pMaterial->bumpMapFilename;

            // Try loading the texture from the same directory as the OBJ file.
            loadBumpMap(model->getPath() + filename);
        }

    }
}

PENJIN_ERRORS ModelObj::loadTexture(CRstring fName)
{
    delete texture;
    texture = NULL;
    texture = new Texture;
    return texture->loadTexture(fName);
}

PENJIN_ERRORS ModelObj::loadBumpMap(CRstring fName)
{
    delete bumpMap;
    bumpMap = NULL;
    bumpMap = new Texture;
    return bumpMap->loadTexture(fName);
}

void ModelObj::render()
{
    const ModelOBJ::Mesh *pMesh = 0;
    const ModelOBJ::Material *pMaterial = 0;
    const ModelOBJ::Vertex *pVertices = 0;
    //ModelTextures::const_iterator iter;

    for (int i = 0; i < model->getNumberOfMeshes(); ++i)
    {
        pMesh = &model->getMesh(i);
        pMaterial = pMesh->pMaterial;
        pVertices = model->getVertexBuffer();

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pMaterial->ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pMaterial->diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->shininess * 128.0f);

        if (texture)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
        }
        else
        {
            glDisable(GL_TEXTURE_2D);
        }

        if (model->hasPositions())
        {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, model->getVertexSize(),
                model->getVertexBuffer()->position);
        }

        if (model->hasTextureCoords())
        {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_FLOAT, model->getVertexSize(),
                model->getVertexBuffer()->texCoord);
        }

        if (model->hasNormals())
        {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT, model->getVertexSize(),
                model->getVertexBuffer()->normal);
        }

        glDrawElements(GL_TRIANGLES, pMesh->triangleCount * 3, GL_UNSIGNED_INT,
            model->getIndexBuffer() + pMesh->startIndex);

        if (model->hasNormals())
            glDisableClientState(GL_NORMAL_ARRAY);

        if (model->hasTextureCoords())
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        if (model->hasPositions())
            glDisableClientState(GL_VERTEX_ARRAY);
    }
   /* glEnable(GL_TEXTURE_2D);

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

	glDisable(GL_TEXTURE_2D);*/
}

void ModelObj::update()
{}
