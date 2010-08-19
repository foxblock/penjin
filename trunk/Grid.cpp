#include "Grid.h"
#ifdef PENJIN_GL
    #include <SDL/SDL_opengl.h>
#elif defined (PENJIN_SDL) || defined (PENJIN_SOFT) || defined (PENJIN_ES) || defined (PENJIN_ES2)
    #include <SDL/SDL.h>
#endif
#if defined (PENJIN_ES) || defined (PENJIN_ES2)
    #ifdef PENJIN_ES
        #include <GLES/gl.h>
    #elif PENJIN_ES2
        #include <GLES2/gl2.h>
    #endif
    #include <EGL/egl.h>
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xatom.h>
#endif
Grid::Grid()
{
    //ctor
    numTiles.x = numTiles.y = 10;
    colour = GREEN;
    refresh();
}

Grid::~Grid()
{
    //dtor
}

void Grid::render()
{
    //  Setup vertex pointers
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_INT, 0, &lines.front());
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    glDrawArrays(GL_LINES,0,lines.size());
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Grid::refresh()
{
    //  gen lines
    lines.clear();
    //  TODO Change to 3df and swap Y abd Z values.
    for (int i = origin.x - numTiles.x; i <= origin.x + numTiles.x; ++i)
    {
        Point3di t;
        t.x = i;
        t.y=0;
        t.z = origin.y - numTiles.y;
        lines.push_back(t);
        t.x = i;
        t.z = origin.y + numTiles.y;
        lines.push_back(t);
    }
    for(int j = origin.y - numTiles.y; j <= origin.y + numTiles.y; ++j)
    {
        Point3di t;
        t.x = origin.x - numTiles.x;
        t.y = 0;
        t.z = j;
        lines.push_back(t);
        t.x = origin.x + numTiles.x;
        t.z = j;
        lines.push_back(t);
    }
}
