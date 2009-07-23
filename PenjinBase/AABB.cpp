#include "AABB.h"
#include <SDL/SDL_opengl.h>

AABB::AABB()
{}

AABB::AABB(const float& xpos,const float& ypos,const float& zpos,const float& halfLength)
{
	centre.x = xpos;
	centre.y = ypos;
	centre.z = zpos;

	this->halfLength.x = halfLength;
	this->halfLength.y = halfLength;
	this->halfLength.z = halfLength;

	defCentre = centre;
}

AABB::AABB(const float& xpos,const float& ypos,const float& zpos,const float& xlen,const float& ylen,const float& zlen)
{
	centre.x = xpos;
	centre.y = ypos;
	centre.z = zpos;

	halfLength.x = xlen;
	halfLength.y = ylen;
	halfLength.z = zlen;

	defCentre = centre;
}

AABB::~AABB()
{
	std::list<AABB*>::iterator iter;
	for(iter = subList.begin() ; iter != subList.end() ; ++iter)
	{
		delete *iter;
	}
	subList.clear();
}

void AABB::setAABB(const float& xpos,const float& ypos,const float& zpos,const float& halfLength)
{
	centre.x = xpos;
	centre.y = ypos;
	centre.z = zpos;

	this->halfLength.x = halfLength;
	this->halfLength.y = halfLength;
	this->halfLength.z = halfLength;
}

void AABB::setAABB(const float& xpos,const float& ypos,const float& zpos,const float& xlen,const float& ylen,const float& zlen)
{
	centre.x = xpos;
	centre.y = ypos;
	centre.z = zpos;

	halfLength.x = xlen;
	halfLength.y = ylen;
	halfLength.z = zlen;
}

bool AABB::collided(const AABB& target, GLfloat rotMat[16])
{
	//Check for collision in 3 planes
	if(centre.x-halfLength.x < target.centre.x+target.halfLength.x && centre.x+halfLength.x > target.centre.x-target.halfLength.x)
	{
		if(centre.y-halfLength.y < target.centre.y+target.halfLength.y && centre.y+halfLength.y > target.centre.y-target.halfLength.y)
		{
			if(centre.z-halfLength.z < target.centre.z+target.halfLength.z && centre.z+halfLength.z > target.centre.z-target.halfLength.z)
			{
				//If this AABB has no sublist then depth of AABB tree has been reached and collision has occured
				if(subList.size() == 0)
					return true;
				//Else check for collision with sublist members
				else
				{
					for(std::list<AABB*>::iterator iter = subList.begin() ; iter != subList.end() ; ++iter)
					{
					    Vector3d temp= Vector3d((*iter)->defCentre) * rotMat;
						(*iter)->centre = temp.getVector3df();
						(*iter)->centre += centre;
						if((*iter)->collided(target, rotMat))
							return true;
					}
				}
			}
		}
	}
	return false;
}

void AABB::render(GLfloat rotMat[16])
{
	std::list<AABB*>::iterator iter;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);

	glColor4f(0.0f, 1.0f, 0.0f, 0.3f);

	for(iter = subList.begin() ; iter != subList.end() ; ++iter)
	{
	    Vector3d temp = Vector3d((*iter)->defCentre) * rotMat;
		(*iter)->centre = temp.getVector3df();

		glBegin(GL_QUADS);
			renderBox(centre+(*iter)->centre, (*iter)->halfLength);
		glEnd();
	}

	glDisable(GL_BLEND);

	glEnable(GL_CULL_FACE);
}

void AABB::renderBox(const Vector3df& centre,const Vector3df& halfLength)
{
	glVertex3f(centre.x+halfLength.x, centre.y+halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y+halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y+halfLength.y, centre.z-halfLength.z);
	glVertex3f(centre.x+halfLength.x, centre.y+halfLength.y, centre.z-halfLength.z);
	glVertex3f(centre.x+halfLength.x, centre.y-halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y-halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y-halfLength.y, centre.z-halfLength.z);
	glVertex3f(centre.x+halfLength.x, centre.y-halfLength.y, centre.z-halfLength.z);

	glVertex3f(centre.x+halfLength.x, centre.y+halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x+halfLength.x, centre.y-halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x+halfLength.x, centre.y-halfLength.y, centre.z-halfLength.z);
	glVertex3f(centre.x+halfLength.x, centre.y+halfLength.y, centre.z-halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y+halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y-halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y-halfLength.y, centre.z-halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y+halfLength.y, centre.z-halfLength.z);

	glVertex3f(centre.x+halfLength.x, centre.y+halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x+halfLength.x, centre.y-halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y-halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y+halfLength.y, centre.z+halfLength.z);
	glVertex3f(centre.x+halfLength.x, centre.y+halfLength.y, centre.z-halfLength.z);
	glVertex3f(centre.x+halfLength.x, centre.y-halfLength.y, centre.z-halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y-halfLength.y, centre.z-halfLength.z);
	glVertex3f(centre.x-halfLength.x, centre.y+halfLength.y, centre.z-halfLength.z);
}
