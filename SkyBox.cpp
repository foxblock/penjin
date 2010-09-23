#include "SkyBox.h"
using namespace PenjinErrors;
SkyBox::SkyBox()
{
    TEX_MIN=0.0f;
    TEX_MAX=1.0f;
    currentTexture = -1;//-1 no texture loaded
   /* /// Fixes Texture direction
    glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glScalef(-1.0f, 1.0f, 1.0f);*/
}

SkyBox::~SkyBox()
{
    //dtor
}

void SkyBox::setResolution(CRuint res)
{
    TEX_MIN = 1/(float)res;
    TEX_MAX -= TEX_MIN;
}

void SkyBox::setResolution()
{
    if(currentTexture != -1)
        setResolution(textures[0].getWidth());
}

int SkyBox::loadTexture(CRstring file)
{
    int error = loadTexture(currentTexture, file);
    if(error == PENJIN_OK)
        ++currentTexture;

    return error;
}

int SkyBox::loadTexture(CRint i, CRstring file)
{
    int fileLoaded = PENJIN_ERROR;
    if(i < 5)
        fileLoaded = textures[i+1].loadTexture(file);

    return fileLoaded;
}

void SkyBox::refresh()
{

}

void SkyBox::render()
{
    glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glPushMatrix();
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);

    //  REWRITE TO USE GLES COMPATIBLE CODE
	/// Front
	glBindTexture(GL_TEXTURE_2D, textures[0].getTextureID());
	glBegin(GL_QUADS);
		glTexCoord2f(TEX_MIN, TEX_MIN);		glVertex3d(-100.0f, -100.0f, -100.0f);
		glTexCoord2f(TEX_MAX, TEX_MIN);		glVertex3d(+100.0f, -100.0f, -100.0f);
		glTexCoord2f(TEX_MAX, TEX_MAX);		glVertex3d(+100.0f, +100.0f, -100.0f);
		glTexCoord2f(TEX_MIN, TEX_MAX);		glVertex3d(-100.0f, +100.0f, -100.0f);
	glEnd();

	/// Right
	glBindTexture(GL_TEXTURE_2D, textures[1].getTextureID());
	glBegin(GL_QUADS);
		glTexCoord2f(TEX_MIN, TEX_MIN);		glVertex3d(+100.0f, -100.0f, -100.0f);
		glTexCoord2f(TEX_MAX, TEX_MIN);		glVertex3d(+100.0f, -100.0f, +100.0f);
		glTexCoord2f(TEX_MAX, TEX_MAX);		glVertex3d(+100.0f, +100.0f, +100.0f);
		glTexCoord2f(TEX_MIN, TEX_MAX);		glVertex3d(+100.0f, +100.0f, -100.0f);
	glEnd();

	/// Back
	glBindTexture(GL_TEXTURE_2D, textures[2].getTextureID());
	glBegin(GL_QUADS);
		glTexCoord2f(TEX_MIN, TEX_MIN);		glVertex3d(+100.0f, -100.0f, +100.0f);
		glTexCoord2f(TEX_MAX, TEX_MIN);		glVertex3d(-100.0f, -100.0f, +100.0f);
		glTexCoord2f(TEX_MAX, TEX_MAX);		glVertex3d(-100.0f, +100.0f, +100.0f);
		glTexCoord2f(TEX_MIN, TEX_MAX);		glVertex3d(+100.0f, +100.0f, +100.0f);
	glEnd();

	/// Left
	glBindTexture(GL_TEXTURE_2D, textures[3].getTextureID());
	glBegin(GL_QUADS);
		glTexCoord2f(TEX_MIN, TEX_MIN);		glVertex3d(-100.0f, -100.0f, +100.0f);
		glTexCoord2f(TEX_MAX, TEX_MIN);		glVertex3d(-100.0f, -100.0f, -100.0f);
		glTexCoord2f(TEX_MAX, TEX_MAX);		glVertex3d(-100.0f, +100.0f, -100.0f);
		glTexCoord2f(TEX_MIN, TEX_MAX);		glVertex3d(-100.0f, +100.0f, +100.0f);
	glEnd();

	/// Bottom
	glBindTexture(GL_TEXTURE_2D, textures[4].getTextureID());
	glBegin(GL_QUADS);
		glTexCoord2f(TEX_MIN, TEX_MIN);		glVertex3d(-100.0f, -100.0f, +100.0f);
		glTexCoord2f(TEX_MAX, TEX_MIN);		glVertex3d(+100.0f, -100.0f, +100.0f);
		glTexCoord2f(TEX_MAX, TEX_MAX);		glVertex3d(+100.0f, -100.0f, -100.0f);
		glTexCoord2f(TEX_MIN, TEX_MAX);		glVertex3d(-100.0f, -100.0f, -100.0f);
	glEnd();

	/// Top
	glBindTexture(GL_TEXTURE_2D, textures[5].getTextureID());
	glBegin(GL_QUADS);
		glTexCoord2f(TEX_MIN, TEX_MIN);		glVertex3d(-100.0f, +100.0f, -100.0f);
		glTexCoord2f(TEX_MAX, TEX_MIN);		glVertex3d(+100.0f, +100.0f, -100.0f);
		glTexCoord2f(TEX_MAX, TEX_MAX);		glVertex3d(+100.0f, +100.0f, +100.0f);
		glTexCoord2f(TEX_MIN, TEX_MAX);		glVertex3d(-100.0f, +100.0f, +100.0f);
	glEnd();
    glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}
