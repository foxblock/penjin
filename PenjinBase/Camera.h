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
