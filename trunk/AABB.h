#ifndef INC_AABB_H
#define INC_AABB_H

#include "PenjinTypes.h"
#include "Vector3d.h"
#include <list>
using namespace std;
#ifdef PENJIN3D
    #ifdef __linux__
        #include <SDL_opengl.h>
    #else
        #include <SDL/SDL_opengl.h>
    #endif
#endif

class AABB
{
	public :

		Vector3df centre;
		Vector3df halfLength;

		list<AABB*> subList;

        AABB();
        AABB(const float& xpos,const float& ypos,const float& zpos,const float& halfLength);
        AABB(const float& xpos,const float& ypos,const float& zpos,const float& xlen,const float& ylen,const float& zlen);
        ~AABB();

        void setAABB(const float& xpos,const float& ypos,const float& zpos,const float& halfLength);
        void setAABB(const float& xpos,const float& ypos,const float& zpos,const float& xlen,const float& ylen,const float& zlen);

        bool collided(const AABB& target, GLfloat rotMat[16]);
        void render(GLfloat rotMat[16]);

	private :
		Vector3df defCentre;
        void renderBox(const Vector3df& centre,const Vector3df& halfLength);
};

#endif
