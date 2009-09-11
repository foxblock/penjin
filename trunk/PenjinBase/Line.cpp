#include "Line.h"

Line::Line()
{
    //ctor
    start.x = start.y = 0;
    end.y = end.x = 10;
    lineWidth = 1.0f;
}

Line::~Line()
{
    //dtor
}

void Line::render()
{
        // Scale and rotate
    glPushMatrix();
/*
    #ifdef PENJIN3D
        glScalef(scale.x, scale.y, scale.z);
        glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    #else
        glScalef(scale.x,scale.y,1.0f);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    #endif
  */
    //Setup model view
    //glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glAlphaFunc(GL_GREATER,0.1f);
        glEnable(GL_ALPHA_TEST);
            //glEnable(GL_BLEND);
            //  Set OpenGL alpha and colour
                glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
                glLineWidth(lineWidth);
                glBegin(GL_LINES);
                    #ifdef PENJIN3D
                        glVertex3f(position.x, position.y,  position.z);
                    #else
                        glVertex2f(start.x,start.y);
                    #endif
                    #ifdef PENJIN3D
                        glVertex3f(position.x + dimensions.x, position.y, position.z);
                    #else
                        glVertex2f(end.x, end.y);
                    #endif
                glEnd();
            //glDisable(GL_BLEND);
        glDisable(GL_ALPHA_TEST);
    glPopMatrix();
}
