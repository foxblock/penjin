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
#include "Line.h"
#include "GFX.h"
Line::Line()
{
    //ctor
    start.x = start.y = 0;
    end.y = end.x = 10;
    lineWidth = 1.0f;
    #ifdef PENJIN_SDL
    screen = GFX::getVideoSurface();
    #endif
}

Line::~Line()
{
    //dtor
}

#ifdef PENJIN_SDL
void Line::render(SDL_Surface* scr)
{
lineRGBA(scr,
             start.x, start.y,
             end.x, end.y,
             colour.red, colour.green, colour.blue, colour.alpha);
}
#endif

void Line::render()
{
#ifdef PENJIN_SDL
    render(screen);
#else
    // Scale and rotate
    glPushMatrix();
/*
    #ifdef PENJIN_3D
        glScalef(scale.x, scale.y, scale.z);
        glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    #else
        glScalef(scale.x,scale.y,1.0f);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    #endif
  */
    glLoadIdentity( );
            glEnable(GL_BLEND);
            //  Set OpenGL alpha and colour
                glLineWidth(lineWidth);
                glEnableClientState(GL_VERTEX_ARRAY);
                    #ifdef PENJIN_3D
                        float verts[] = {   start.x, start.y, start.z,
                                            end.x, end.y, end.z};
                        glVertexPointer(3, GL_FLOAT, 0,verts);
                    #else
                        float verts[] = {   start.x, start.y,
                                            end.x, end.y};
                        glVertexPointer(2, GL_FLOAT, 0,verts);
                    #endif
                glEnableClientState(GL_COLOR_ARRAY);
                    float c[] = {   colour.red, colour.green, colour.blue, colour.alpha ,colour.red, colour.green, colour.blue, colour.alpha};
                    glColorPointer(4, GL_FLOAT, 0,c);
                    glDrawArrays(GL_LINES,0,2);
                glDisableClientState(GL_VERTEX_ARRAY);
                glDisableClientState(GL_COLOR_ARRAY);
            glDisable(GL_BLEND);
    glPopMatrix();
#endif
}
