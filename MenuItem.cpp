#include "MenuItem.h"

MenuItem::~MenuItem()
{
}

#ifdef PENJIN_SDL
    void MenuItem::render(SDL_Surface* screen)
    {
    }
#endif
void MenuItem::render()
{
}
void MenuItem::update()
{}

Vector2di MenuItem::getDimensions()
{
    Vector2di t;
    t.x=0;
    t.y=0;
    return t;
}

void MenuItem::init()
{

}

bool MenuItem::isMouseSelected(CRint x,CRint y)
{
    if(isSelectable)
    {
        dimensions = getDimensions();
        #ifdef PENJIN_FIXED
        Vector2di pos(position.x,position.y);
            if(x > pos.x && x < pos.x + dimensions.x)
                if(y > pos.y && y < pos.y + dimensions.y)
        #else
            if(x > position.x && x < position.x + dimensions.x)
                if(y > position.y && y < position.y + dimensions.y)
        #endif
            return true;
    }
    return false;
}
