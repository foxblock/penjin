/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
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
