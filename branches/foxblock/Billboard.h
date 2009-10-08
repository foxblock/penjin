#ifndef INC_BILLBOARD_H
#define INC_BILLBOARD_H

#include "Texture.h"
#include "Quaternion.h"
#include "Vector3d.h"
#include "Video.h"

#include <iostream>

class Billboard
{
	public :

		Vector3d centre;
		Vector3d halfLength;
		Quaternion rotation;
		Texture *texture;

		bool video;
//		Video *vid;
		string filename;

		bool textured;

		bool cullBack;

	public : Billboard();
	public : Billboard(double xpos, double ypos, double zpos, double halfLength);
	public : Billboard(double xpos, double ypos, double zpos, double xlen, double ylen, double zlen);
	public : ~Billboard();

	public : void loadTexture(std::string faceTexture);
	public : void render();

	public : void setVideo(string filename);
	public : void loadVideo();
};

#endif
