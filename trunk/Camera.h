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
/*
	Project:	Atrox Space Game
	File:		Camera Class
	Author:		Gordon McLean
	Date:		31st December 2006
	Version:	0.1

	Description:
	/// Optimisations made by Kevin Winfield-Pantoja
*/

#ifndef INC_CAMERA_H
#define INC_CAMERA_H

#include "Quaternion.h"
#include "Vector3d.h"
#include "PenjinTypes.h"

class Camera
{
	public :
		Vector3d pos;

		//Movement variables: negative movement < 0 < positive movement
		float camRoll, camPitch, camYaw;
        Camera();
        Camera(Vector3df* targetPos, Quaternion* targetRotation,const float& roll,const float& pitch,const float& yaw,const float& z);
        ~Camera();
/////
        void setTargetPosition(Vector3df* target){this->target = target;}
        void setTargetRotation(Quaternion* target){targetRotation = target;}
        float* getRotationMatrix(){return rotMat;}

        void render();
        void update();
        void zoom(const float& z);
        void reset(){cameraReset = true;}

	private:
		const static int camZoomMin = 1;
		const static int camZoomMax = 100;

		Vector3df* target;
        Quaternion* targetRotation;
		float z;

		Quaternion rotation;
		GLfloat rotMat[16];

		bool rotUpdate;
		bool cameraReset;

		float slerpAmount;
};
#endif
