#include "Sphere.h"
#ifdef PENJIN_GL
    #include <GL/gl.h>
#elif PENJIN_ES
    #include <GLES/gl.h>
#elif PENJIN_ES2
    #include <GLES2/gl2.h>
#endif
Sphere::Sphere()
{
    //ctor
    Vsegs = 10;
    Hsegs = 10;
    radius = 1.0f;
    refresh();
}

Sphere::~Sphere()
{
    //dtor
}

void Sphere::refresh()
{
    verts.clear();
    int i, j;
    for(i = 0; i <= Hsegs; ++i)
    {
        float lat0 = M_PI * (-0.5f + (float) (i - 1) / Hsegs);
        float z0  = sin(lat0);
        float zr0 =  cos(lat0);

        float lat1 = M_PI * (-0.5f + (float) i / Hsegs);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        for(j = 0; j <= Vsegs; ++j)
        {
            float lng = 2 * M_PI * (float) (j - 1) / Vsegs;
            float x = cos(lng);
            float y = sin(lng);

            //glNormal3f(x * zr0, y * zr0, z0);
            //glVertex3f(x * zr0, y * zr0, z0);
            //glNormal3f(x * zr1, y * zr1, z1);
            //glVertex3f(x * zr1, y * zr1, z1);
            verts.push_back(x*zr0);
            verts.push_back(y*zr0);
            verts.push_back(z0);
            verts.push_back(x*zr1);
            verts.push_back(y*zr1);
            verts.push_back(z1);
        }
    }
}

void Sphere::render()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &verts.front());
	//glNormalPointer(GL_FLOAT, 0, normals);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, verts.size());

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
}
