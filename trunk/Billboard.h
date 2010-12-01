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
