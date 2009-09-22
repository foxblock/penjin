#include "Model3dBase.h"

Model3dBase::Model3dBase()
{
    //ctor
    texture = NULL;
}

Model3dBase::~Model3dBase()
{
    //dtor
    if(texture)
        delete texture;
    texture = NULL;
}

int Model3dBase::loadModel(CRstring filename)
{
    //  This model type is invalid so an error is triggered.
    return PENJIN_ERROR;
}

int Model3dBase::loadTexture(CRstring filename)
{
    if(texture)
        delete texture;
    texture = NULL;
    texture = new Texture;
    return texture->loadTexture(filename);
}

void Model3dBase::render()
{}

void Model3dBase::update()
{}
