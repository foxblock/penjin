/*
	Pirate Games 2008 (and beyond...)
	The source is free for modification.
	Any changes should be emailed back to the Pirate Games team
		(team@pirate-games.co.uk)
*/#ifndef MODEL3D_H
#define MODEL3D_H
#include "PenjinTypes.h"
#include "PenjinErrors.h"
using namespace PenjinErrors;
#include "Model3dBase.h"
#include "Parser.h"
#include "StringUtility.h"
class Model3d
{
    public:
        Model3d();
        Model3d(CRstring filename);
        Model3d(CRstring modelName,CRstring textureName);
        ~Model3d();

        int loadTexture(CRstring filename);
        int loadModel(CRstring filename);

        void render();
        void update();      //  if the model supports animation you can call this.

    private:
        Model3dBase* model;
};

#endif // MODEL3D_H
