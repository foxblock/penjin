/*
	Pirate Games 2008 (and beyond...)
	The source is free for modification.
	Any changes should be emailed back to the Pirate Games team
		(team@pirate-games.co.uk)
*/#ifndef MODELOBJ_H
#define MODELOBJ_H
#include "Model3dBase.h"
#include "PenjinTypes.h"
#include "TextDoc.h"

class ModelObj : public Model3dBase
{
    public:
        ModelObj();
        virtual ~ModelObj();

        virtual int loadModel(CRstring model);

        virtual void render();
        //virtual void update();  //  Only relevent for animated models
    private:
        GLfloat* vertices;
        GLfloat* normals;
        GLfloat* texCoords;
};

#endif // MODELOBJ_H
