/*
	Pirate Games 2008 (and beyond...)
	The source is free for modification.
	Any changes should be emailed back to the Pirate Games team
		(team@pirate-games.co.uk)
*/
#include "Model3ds.h"
#include "ModelObj.h"

#ifndef MODEL3DBASE_H
#define MODEL3DBASE_H
#include "PenjinTypes.h"
#include "PenjinErrors.h"
using namespace PenjinErrors;

//  This base class is not intended to actually be used directly
class Model3dBase
{
    public:
        Model3dBase();
        virtual ~Model3dBase();

        int loadTexture(CRstring texture);
        virtual int loadModel(CRstring model);

        virtual void render();
        virtual void update();  //  Only relevent for animated models

    protected:
        Texture* texture;
};

#endif // MODEL3DBASE_H
