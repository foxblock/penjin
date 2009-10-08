#ifndef INC_MODEL3DS_H
#define INC_MODEL3DS_H


#include <SDL/SDL_opengl.h>

#include <lib3ds/file.h>
#include <lib3ds/mesh.h>
#include <string>
using namespace std;

#include "PenjinTypes.h"
#include "PenjinErrors.h"
#include "Texture.h"
#include "Model3dBase.h"

class Model3ds : public Model3dBase
{
	public :
        Model3ds();
        ~Model3ds();

        virtual int loadModel(const string& fileName);

        virtual void render();

	private :
		uint numFaces;		//Total number of faces model has over all meshes
		Lib3dsVector* vertices;		//Vertex array
		Lib3dsVector* normals;		//Normal array
		GLfloat* coords;			//Texture coordinate array

		void setNULL();
		void clear();
};

#endif
