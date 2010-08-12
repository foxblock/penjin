#include "Background.h"


Background::Background()
{
	bg = 0;
	position.x = 0;
	position.y = 0;
	#ifdef PENJIN_SDL
        screen = GFX::getVideoSurface();
    #endif
}

Background::~Background(){};

PENJIN_ERRORS Background::loadBackground(CRstring file){return img.loadImageNoKey(file);}
#ifdef PENJIN_SDL
    void Background::render(SDL_Surface *scr){img.renderImage(bg,scr,position.x,position.y);}
#else
    void Background::render(){img.renderImage(bg,position.x,position.y);}
#endif
uint Background::getBG()const{return bg;}

void Background::setBG(CRuint bg){this->bg = bg;}

void Background::toGreyScale()
{
    img.toGreyScale();
}


