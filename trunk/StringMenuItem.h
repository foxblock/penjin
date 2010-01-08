#ifndef STRINGMENUITEM_H_INCLUDED
#define STRINGMENUITEM_H_INCLUDED

#ifndef PENJIN_ASCII
    #include "Text.h"
#else
    #include <iostream>
    using std::cout;
    using std::endl;
#endif
#include "MenuItem.h"

class StringMenuItem : public MenuItem
{
    public:
        StringMenuItem(){init();}
        StringMenuItem(CRstring menuItemText){init(); this->menuItemText = menuItemText;}
        #ifndef PENJIN_ASCII
            StringMenuItem(Text* pointer){init(); setTextHandler(pointer);}
        virtual Vector2di getDimensions();                   // renderstoa null surfaxe in order to get the dims
        #endif
        virtual ~StringMenuItem();

        virtual void update(){;}                          //  We just return since there is nothing to update for this type


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

    protected:
        virtual void init();

    private:
        string menuItemText;
        #ifndef PENJIN_ASCII
            Text* text;             //   Pointer to a Text the actual Text is shared through the menu items
            Colour selectedColour;
        #endif
        char selectionIndicator;
};

#endif // STRINGMENUITEM_H_INCLUDED
