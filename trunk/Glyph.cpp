#include "Glyph.h"

Glyph::Glyph()
{
    //ctor
    fontSize = 0;       // no font.
    position = NULL;
    character = '\0';
    #ifdef PENJIN_SDL
        renderMode = GlyphClass::QUICK;
    #else
        renderMode = GlyphClass::NICE;
    #endif
}

Glyph::~Glyph()
{
    //dtor
}


#ifdef PENJIN_SDL
void Glyph::render(SDL_Surface* scr)
{
    glyph.renderImage(scr,*position);
}
#endif

void Glyph::refresh()
{
    if(position == NULL || !isprint(character) || fontSize == 0)        //  No cursor position is invalid usage.
        return;
#ifndef PENJIN_GL
    if(glyph.size())
        glyph.clear();
#endif
    char t[2];
    t[0] = character;
    t[1] = '\0';
    SDL_Surface* tS;
    if(renderMode == QUICK)
        tS = TTF_RenderText_Solid(font,t,colour.getSDL_Colour());
    else if(renderMode == BOXED)
        tS = TTF_RenderText_Shaded(font,t,colour.getSDL_Colour(),bgColour.getSDL_Colour());
    else
        tS = TTF_RenderText_Blended(font,t,colour.getSDL_Colour());
#ifndef PENJIN_GL
    glyph.loadImage(tS);
#else
    glyph.loadSurface(tS);
#endif
}

void Glyph::render()
{
    #ifndef PENJIN_GL
        glyph.renderImage(*position);
    #else
        //  With the surface now converted to a texture we can render it to a quad
        glColor4f(1.0f, 1.0f, 1.0f, colour.alpha);
        glBindTexture (GL_TEXTURE_2D, glyph.getTextureID());
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        //glEnable(GL_ALPHA_TEST);
        //glAlphaFunc(GL_GREATER, 0.5);
            glEnable(GL_TEXTURE_2D);
                glBegin(GL_QUADS);
                    glTexCoord2f (0.0f, 0.0f);
                    #ifdef PENJIN3D
                        glVertex3f(position->x, position->y, position->z);
                    #else
                        glVertex2f(position->x,position->y);
                    #endif
                    glTexCoord2f (1.0f, 0.0f);
                    #ifdef PENJIN3D
                        glVertex3f(position->x + glyph.getWidth(), position->y, position->z);
                    #else
                        glVertex2f(position->x + glyph.getWidth(), position->y);
                    #endif
                    glTexCoord2f (1.0f,  1.0f);
                    #ifdef PENJIN3D
                        glVertex3f(position->x + glyph.getWidth(), position->y + glyph.getHeight(), position->z);
                    #else
                        glVertex2f(position->x + glyph.getWidth(), position->y + glyph.getHeight());
                    #endif
                    glTexCoord2f (0.0f, 1.0f);
                    #ifdef PENJIN3D
                        glVertex3f(position->x, position->y + glyph.getHeight(), position->z);
                    #else
                        glVertex2f(position->x, position->y + glyph.getHeight());
                    #endif
                glEnd();
            glDisable(GL_TEXTURE_2D);
        //glDisable(GL_ALPHA_TEST);
        glDisable(GL_BLEND);
    #endif
}
