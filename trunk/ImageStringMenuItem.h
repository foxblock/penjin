#ifndef IMAGESTRINGMENUITEM_H_INCLUDED
#define IMAGESTRINGMENUITEM_H_INCLUDED

#include "ImageMenuItem.h"
#include "StringMenuItem.h"

class ImageStringMenuItem : public MenuItem
{
    public:
        ImageStringMenuItem(){init();}
        virtual ~ImageStringMenuItem();

        virtual void update();
        virtual Vector2di getDimensions();

        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
        #endif
        virtual void render();

        #ifdef PENJIN3D
            virtual void setPosition(const Vector3df& pos);
        #else
            virtual void setPosition(const Vector2df& pos);
        #endif



        /// Set text properties - inherited from the text handler passed in
        void setTextHandler(Text* pointer){text.setTextHandler(pointer);}
        void setMenuItemText(CRstring txt){text.setMenuItemText(txt);}
        void setSelectionIndicator(CRchar c){text.setSelectionIndicator(c);}
        void setTextSelectionColour(const Colour& colour){text.setTextSelectionColour(colour);}

        ///  Image loading and properties
        PENJIN_ERRORS loadImage(CRstring fileName){return menuImage.loadImage(fileName);}
        PENJIN_ERRORS loadSelection(CRstring fileName){return menuImage.loadSelection(fileName);}
        #ifdef PENJIN_SDL
            void setUseHardware(CRbool shouldUse){menuImage.setUseHardware(shouldUse);}
        #endif
        void centreText(CRint corr);
    protected:
        virtual void init();

    private:
        StringMenuItem text;
        ImageMenuItem menuImage;
};
#endif // IMAGESTRINGMENUITEM_H_INCLUDED
