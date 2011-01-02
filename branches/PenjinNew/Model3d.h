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

        void setPosition(const Vector3df& p){position = p;}
        void setRotation(const Vector3df& vec){rotation = vec;}
        void setScale(const Vector3df& vec){scale = vec;}
        void setScale(CRfloat s){setScale(Vector3df(s,s,s));}
        Vector3df getPosition()const{return position;}

    private:
        Model3ds* model3ds;
        ModelObj* modelobj;

        Vector3df position;     //  Model position
        Vector3df rotation;     //  Rotation Vector
        Vector3df scale;        //  Scale Vector

};

#endif // MODEL3D_H
