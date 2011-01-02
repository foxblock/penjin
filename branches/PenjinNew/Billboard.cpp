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
#include "Billboard.h"

Billboard::Billboard()
{}

Billboard::Billboard(double xpos, double ypos, double zpos, double halfLength)
{
	centre.x = xpos;
	centre.y = ypos;
	centre.z = zpos;

	this->halfLength.x = halfLength;
	this->halfLength.y = halfLength;
	this->halfLength.z = halfLength;

	video = false;

	cullBack = true;

	texture = new Texture();
	textured = false;
}

Billboard::Billboard(double xpos, double ypos, double zpos, double xlen, double ylen, double zlen)
{
	centre.x = xpos;
	centre.y = ypos;
	centre.z = zpos;

	halfLength.x = xlen;
	halfLength.y = ylen;
	halfLength.z = zlen;

	video = false;

	cullBack = true;

	texture = new Texture();
	textured = false;
}

Billboard::~Billboard()
{
	delete texture;
	/*if(video)
		delete vid;*/
}

void Billboard::loadTexture(std::string faceTexture)
{
	textured = true;
	texture->loadTexture(faceTexture.c_str());
}

void Billboard::render()
{
	if(!cullBack)
		glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1,1,1,0.5);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	if(video)
	{
/*		vid->setTexture();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(centre.x+halfLength.x, centre.y-halfLength.y, centre.z+halfLength.z);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(centre.x-halfLength.x, centre.y-halfLength.y, centre.z-halfLength.z);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(centre.x-halfLength.x, centre.y+halfLength.y, centre.z-halfLength.z);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(centre.x+halfLength.x, centre.y+halfLength.y, centre.z+halfLength.z);
		glEnd();*/
	}
	else if(textured)
	{
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(centre.x+halfLength.x, centre.y-halfLength.y, centre.z+halfLength.z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(centre.x-halfLength.x, centre.y-halfLength.y, centre.z-halfLength.z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(centre.x-halfLength.x, centre.y+halfLength.y, centre.z-halfLength.z);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(centre.x+halfLength.x, centre.y+halfLength.y, centre.z+halfLength.z);
		glEnd();
	}
	else
		return;



	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Billboard::setVideo(string filename)
{
	this->filename = filename;
}

void Billboard::loadVideo()
{/*
	video = true;
	vid = new Video(filename, true);*/
}
