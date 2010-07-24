#ifndef MODEL3D_H
#define MODEL3D_H
#include "PenjinTypes.h"
#include "PenjinErrors.h"
using namespace PenjinErrors;

class Model3ds;
class ModelObj;

class Model3d
{
    public:
        Model3d();
        Model3d(CRstring filename);
        Model3d(CRstring modelName,CRstring textureName);
        ~Model3d();

        PENJIN_ERRORS loadTexture(CRstring filename);
        PENJIN_ERRORS loadModel(CRstring filename);

        void render();
        void update();      //  if the model supports animation you can call this.

        void setRotation(const Vector3df& vec){rotation = vec;}
        void setScale(const Vector3df& vec){scale = vec;}

    private:
        Model3ds* model3ds;
        ModelObj* modelobj;

        Vector3df rotation;     //  Rotation Vector
        Vector3df scale;        //  Scale Vector

};

#endif // MODEL3D_H
