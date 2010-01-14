#ifndef DIRMENUITEM_H
#define DIRMENUITEM_H

#include "MenuItem.h"
#include "Text.h"

class DirMenuItem : public MenuItem
{
    public:
        DirMenuItem();
        #ifndef PENJIN_ASCII
            DirMenuItem(Text* pointer){init(); setTextHandler(pointer);}
            virtual Vector2di getDimensions();                   // renderstoa null surfaxe in order to get the dims
        #endif
        virtual ~DirMenuItem();


        virtual void update(){;}


        virtual void render();
        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
        #endif

        /// Set text properties - inherited from the text handler passed in
        #ifndef PENJIN_ASCII
            void setTextHandler(Text* pointer){text = pointer;}
            void setTextSelectionColour(const Colour& c){selectedColour = c;}
        #endif
        void setMenuItemText(CRstring text){menuItemText = text;}
        void setSelectionIndicator(CRchar c){selectionIndicator = c;}
        void setDirType(CRint t){dirType = t;}
        int getDirType()const{return dirType;}

    protected:
        virtual void init();

    private:
        string menuItemText;
        int dirType;
        #ifndef PENJIN_ASCII
            Text* text;             //   Pointer to a Text the actual Text is shared through the menu items
            Colour selectedColour;
        #endif
        char selectionIndicator;
};

#endif // DIRMENUITEM_H
