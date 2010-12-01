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
