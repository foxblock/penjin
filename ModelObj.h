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

        void setPosition(const Vector3df& p){position = p;}
        void setRotation(const Vector3df& vec){rotation = vec;}
        void setScale(const Vector3df& vec){scale = vec;}
        void setScale(CRfloat s){setScale(Vector3df(s,s,s));}
        Vector3df getPosition()const{return position;}
    private:
        ModelOBJ* model;
        Texture* texture;
        //Texture* normalMap;
        Texture* bumpMap;

        Vector3df position;     //  Model position
        Vector3df rotation;     //  Rotation Vector
        Vector3df scale;        //  Scale Vector

};

#endif // MODELOBJ_H
