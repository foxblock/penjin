#include "Model3d.h"
#include "Model3ds.h"
#include "ModelObj.h"
#include "Parser.h"
Model3d::Model3d()
{
    //ctor
    model3ds = NULL;
    modelobj = NULL;
}

Model3d::~Model3d()
{
    //dtor
    delete model3ds;
    delete modelobj;
}


PENJIN_ERRORS Model3d::loadTexture(CRstring filename)
{
    if(model3ds)
        return model3ds->loadTexture(filename);
    else if(modelobj)
        return modelobj->loadTexture(filename);

    return PENJIN_ERROR;
}

PENJIN_ERRORS Model3d::loadModel(CRstring filename)
{
    string ext = Parser().getExtension(filename);
    ext = StringUtility::upper(ext);
    PENJIN_ERRORS result;
    if(ext == "OBJ")                    //  OBJ format 3d model
    {
        delete modelobj;
        modelobj = NULL;

        modelobj = new ModelObj;
        result = modelobj->loadModel(filename);
    }
    else if(ext == "3DS")               //  3dStudio Max model
    {
        delete model3ds;
        model3ds = NULL;

        model3ds = new Model3ds;
        result = model3ds->loadModel(filename);
    }
    else if(ext == "MD2")               //  Quake2 Model format
    {

    }
    else
        return PENJIN_ERROR;      //  unknown format
    return result;
}

void Model3d::render()
{
    if(model3ds)
        model3ds->render();
    else if(modelobj)
        modelobj->render();
}
void Model3d::update()
{
    if(model3ds)
        model3ds->update();
    else if(modelobj)
        modelobj->update();
}
