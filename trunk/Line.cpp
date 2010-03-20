#include "Line.h"

Line::Line()
{
    //ctor
    start.x = start.y = 0;
    end.y = end.x = 10;
    lineWidth = 1.0f;
    #ifdef PENJIN_SDL
    screen = SDL_GetVideoSurface();
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
#ifdef PENJIN_GL
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
        //glAlphaFunc(GL_GREATER,0.1f);
        //glEnable(GL_ALPHA_TEST);
            glEnable(GL_BLEND);
            //  Set OpenGL alpha and colour
                glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
                glLineWidth(lineWidth);

                glEnableClientState(GL_VERTEX_ARRAY);
                    #ifdef PENJIN3D
                        float verts[] = {   start.x, start.y, start.z,
                                            end.x, end.y, end.z};
                        glVertexPointer(3, GL_FLOAT, 0,verts);
                    #else
                        float verts[] = {   start.x, start.y,
                                            end.x, end.y};
                        glVertexPointer(2, GL_FLOAT, 0,verts);
                    #endif
                    glDrawArrays(GL_LINES,0,2);
                glDisableClientState(GL_VERTEX_ARRAY);
            glDisable(GL_BLEND);
        //glDisable(GL_ALPHA_TEST);
    glPopMatrix();
#else
    render(screen);
#endif
}