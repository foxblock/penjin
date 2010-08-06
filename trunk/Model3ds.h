#ifndef INC_MODEL3DS_H
#define INC_MODEL3DS_H
#include "PenjinTypes.h"
#include "PenjinErrors.h"
class Texture;
using namespace PenjinErrors;
class Model3ds
{
	public :
        Model3ds();
        ~Model3ds();

        PENJIN_ERRORS loadTexture(CRstring filename);
        PENJIN_ERRORS loadModel(CRstring filename);

        void render();
        void update();

	private :
        Texture* texture;
        uint numFaces;	            //  Total number of faces model has over all meshes
		ModelVector3f* vertices;		//  Vertex array
		ModelVector3f* normals;		//  Normal array
		float* coords;			    //  Texture coordinate array
        void normalise();
        void setNULL();
		void clear();
};

#endif
