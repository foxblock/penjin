#include "Background.h"


Background::Background()
{
	bg = 0;
	position.x = 0;
	position.y = 0;
	#ifdef PENJIN_SDL
        screen = SDL_GetVideoSurface();
    #endif
}

Background::~Background(){};

PENJIN_ERRORS Background::loadBackground(CRstring file)
{
    PENJIN_ERRORS t;
    t = img.loadImageNoKey(file);
    #ifdef PENJIN_SDL
    if(t == PENJIN_OK)
        img.setUseHardware(true);
    #endif
    return t;
}
#ifdef PENJIN_SDL
    void Background::render(SDL_Surface *scr){img.renderImage(bg,scr,position.x,position.y);}
#else
    void Background::render(){img.renderImage(bg,position.x,position.y);}
#endif
uint Background::getBG()const{return bg;}

void Background::setBG(CRuint bg){this->bg = bg;}


