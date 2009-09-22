#include "ParticleCollider.h"

ParticleCollider::ParticleCollider()
{
    //ctor
    colour = RED;
    position.x = position.y = 0;
    dimensions.x = dimensions.y = 1;
}

ParticleCollider::~ParticleCollider()
{
    //dtor
}

#ifdef PENJIN_SDL
void ParticleCollider::render(SDL_Surface* screen)
{
    SDL_Rect t;
    t.x = position.x;
    t.y = position.y;
    t.w = dimensions.x;
    t.h = dimensions.y;
    SDL_FillRect(screen, &t, SDL_MapRGB(screen->format,colour.red,colour.green,colour.blue));
}
#else

void ParticleCollider::render()
{
#ifdef PENJIN_OGL

#endif
}
#endif
