#ifndef IMAGEMENUITEM_H_INCLUDED
#define IMAGEMENUITEM_H_INCLUDED

#include "MenuItem.h"
#include "Image.h"

class ImageMenuItem : public MenuItem
{
    public:
        ImageMenuItem(){init();}
        ImageMenuItem(CRstring fileName){init(); menuImage.loadImage(fileName);}
        virtual ~ImageMenuItem();

        virtual Vector2di getDimensions();
        virtual void render();
        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
        #else
            #ifdef PENJIN_3D
                virtual void update();
            #endif
        #endif


        PENJIN_ERRORS loadImage(CRstring fileName){return menuImage.loadImage(fileName);}
        PENJIN_ERRORS loadSelection(CRstring fileName);
        #ifdef PENJIN_SDL
            void setUseHardware(CRbool shouldUse){menuImage.setUseHardware(shouldUse);}
        #endif


    protected:
         virtual void init();

    private:
        Image menuImage;
        Image* selected;        //  pointer to a shared selection image
};
#endif // IMAGEMENUITEM_H_INCLUDED
