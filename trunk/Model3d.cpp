#include "Model3d.h"

Model3d::Model3d()
{
    //ctor
    model = NULL;
    model = new Model3dBase();
}

Model3d::~Model3d()
{
    //dtor
    if(model)
        delete model;
    model = NULL;
}


int Model3d::loadTexture(CRstring filename)
{
    if(model)
        return model->loadTexture(filename);
    return PENJIN_ERROR;
}

int Model3d::loadModel(CRstring filename)
{
    string ext = Parser().getExtension(filename);
    ext = StringUtility::upper(ext);

    if(model)
        delete model;
    model = NULL;
/*
    if(ext == "OBJ")                    //  OBJ format 3d model
        model = new ModelObj();
    else*/ if(ext == "3DS")               //  3dStudio Max model
        model = new Model3ds();
    else
        model = new Model3dBase();      //  unknown format
    return model->loadModel(filename);
}

void Model3d::render()
{
    model->render();
}
void Model3d::update()
{
    model->update();
}
