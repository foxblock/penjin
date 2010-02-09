#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Image.h"

class Background
{
public:
	Background();
	~Background();

	PENJIN_ERRORS loadBackground(CRstring file);
	void setPosition(Vector2di pos){position = pos;}
    #ifdef PENJIN_SDL
        void render(SDL_Surface *screen);	//	The destination surface the animation should be rendered to
        void render(){render(screen);}
        void setUseHardware(CRbool useHW){img.setUseHardware(useHW);}
    #else
        void render();
    #endif
        PENJIN_ERRORS setTransparentColour(const Colour& c){return img.setTransparentColour(c);}
        PENJIN_ERRORS setTransparentColour(const PENJIN_COLOURS& c){return setTransparentColour(c);}
        void disableTransparentColour(){img.disableTransparentColour();}
        void setBG(CRuint bg);	                //	Assigns a background ID
        uint getBG()const;			            //	Returns an assigned background ID
        void toGreyScale();
        void clear(){img.clear();}              //  Clear out all images
        size_t size()const{return img.size();}  //  The number of stored backgrounds.
    private:
        #ifdef PENJIN_SDL
            SDL_Surface* screen;
        #endif
        uint bg;				//	The stored bg ID, used with the image draw function to draw a specific bg.
        Image img;
        Vector2di position;
};

#endif	//	BACKGROUND_H

