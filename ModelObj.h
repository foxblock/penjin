#ifndef MODELOBJ_H
#define MODELOBJ_H

#include "PenjinTypes.h"
#include "PenjinErrors.h"
class ModelOBJ;
class Texture;
using namespace PenjinErrors;
class ModelObj
{
    public:
        ModelObj();
        ~ModelObj();

        PENJIN_ERRORS loadModel(CRstring model);
        PENJIN_ERRORS loadBumpMap(CRstring map);
        //PENJIN_ERRORS loadNormalMap(CRstring map);
        PENJIN_ERRORS loadTexture(CRstring texture);

        void render();
        void update();  //  Only relevent for animated models
    private:
        ModelOBJ* model;
        Texture* texture;
        //Texture* normalMap;
        Texture* bumpMap;

};

#endif // MODELOBJ_H
