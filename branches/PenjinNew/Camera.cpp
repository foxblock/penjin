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
#include "Camera.h"

Camera::Camera(Vector3df *target, Quaternion* targetRot,const float& roll,const float& pitch,const float& yaw,const float& z)
{
	this->target = target;
	targetRotation = targetRot;
	this->z = z;

	camRoll = camPitch = camYaw = 0;

	rotation = Quaternion(roll, pitch, yaw);

	rotUpdate = true;
	cameraReset = false;
}

Camera::Camera()
{
	this->target =0;

	this->z = 1.0f;

	camRoll = camPitch = camYaw = 0;

    rotation = Quaternion(camRoll, camPitch, camYaw);
    targetRotation = &rotation;


	rotUpdate = true;
	cameraReset = false;
}

Camera::~Camera()
{}

void Camera::render()
{
    pos.x = 0.0;
    pos.y = 0.0;
    pos.z = z;

    Vector3df centre;
    centre.x = 0.0f;
    centre.y = 0.0f;
    centre.z = 0.0f;

    Vector3d up;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;

    if(cameraReset)
    {
        Quaternion tempRotation;
        GLfloat tempRotMat[16];
        tempRotation = tempRotation.Slerp(rotation, *targetRotation, slerpAmount);
        slerpAmount += 0.01f;
        tempRotation.convertToMatrix(tempRotMat);
        pos *= tempRotMat;
        up *= tempRotMat;
        if(slerpAmount >= 1.0f)
        {
            cameraReset = false;
            rotation = tempRotation;
            rotUpdate = true;
        }
    }
    else
    {
        slerpAmount = 0.0f;
        pos *= rotMat;
        up *= rotMat;
    }
    gluLookAt(pos.x, pos.y, pos.z, centre.x, centre.y, centre.z, up.x, up.y, up.z);
    glTranslated(-target->x, -target->y, -target->z);
}

void Camera::update()
{
	rotation = rotation * Quaternion(camPitch, camYaw, camRoll);
	rotUpdate = true;

	if(rotUpdate)
	{
		rotation.convertToMatrix(rotMat);
		rotUpdate = false;
	}
}

void Camera::zoom(const float& z)
{
	this->z += z;
	if(this->z <= camZoomMin) this->z = camZoomMin;
	if(this->z >= camZoomMax) this->z = camZoomMax;
}
