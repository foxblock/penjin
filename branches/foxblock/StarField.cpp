#include "StarField.h"

StarField::StarField()
{
    //ctor
}

StarField::~StarField()
{
    //dtor
}

void StarField::setColour(const Colour& c)
{
    for(int i = emit.size()-1; i>=0; --i)
        emit.at(i).setColour(c);
}

void StarField::update()
{
    for(int i = emit.size()-1; i>=0; --i)
        emit.at(i).update();
}

#ifdef PENJIN_SDL
void StarField::render(SDL_Surface* screen)
{
    for(int i = emit.size()-1; i>=0; --i)
        emit.at(i).render(screen);
}
#else
void StarField::render()
{
    for(int i = emit.size()-1; i>=0; --i)
        emit.at(i).render();
}
#endif
