#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Image.h"

class Background
{
public:
	Background();
	~Background();

	PENJIN_ERRORS loadBackground(CRstring file);
	template <class T>
	void setPosition(const T& pos){position.x = pos.x;position.y = pos.y;}
    #ifdef PENJIN_SDL
        void render(SDL_Surface *screen);	//	The destination surface the animation should be rendered to
        void render(){render(screen);}
    #else
        void render();
    #endif
        PENJIN_ERRORS setTransparentColour(const Colour& c){return img.setTransparentColour(c);}
        PENJIN_ERRORS setTransparentColour(const PENJIN_COLOURS& c){return setTransparentColour(Colour(c));}
        void disableTransparentColour(){img.disableTransparentColour();}
        void setBG(CRuint bg);	                //	Assigns a background ID
        uint getBG()const;			            //	Returns an assigned background ID
        void toGreyScale();                     //  Permanently convert Background to B&W
        void clear(){img.clear();bg=0;}              //  Clear out all images
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

