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
#ifndef SKYBOX_H
#define SKYBOX_H

#include "Texture.h"
#include "PenjinTypes.h"
#include "PenjinErrors.h"
class SkyBox
{
    public:
        SkyBox();
        ~SkyBox();

        int loadTexture(CRint index, CRstring file);
        int loadTexture(CRstring file);
        //  Trys to automatically set the texture coords
        void setResolution();
        //  Manually set the texture coords to avoid borders
        void setResolution(CRuint textureResolution);

        //  Set the target that the SkyBox follows
        void setTarget(Vector3df t){target = t;}
        void setRotation(Vector3df r){rotation = r;}
        //  render the skybox to the scene before you set your camera
        void render();

        void refresh();

    private:
        Texture textures[6];
        int currentTexture;
        float TEX_MIN;
        float TEX_MAX;
        Vector3df target;
        Vector3df rotation;
        vector<Point3df> vertices;
        vector<Point2df> texCoords;
};

#endif // SKYBOX_H
