#ifndef STRINGMENUITEM_H_INCLUDED
#define STRINGMENUITEM_H_INCLUDED


#include "Text.h"
#include "MenuItem.h"

class StringMenuItem : public MenuItem
{
    public:
        StringMenuItem(){init();}
        StringMenuItem(CRstring menuItemText){init(); this->menuItemText = menuItemText;}
        StringMenuItem(Text* pointer){init(); setTextHandler(pointer);}

        virtual ~StringMenuItem();

        virtual void update();                          //  We just return since there is nothing to update for this type
        virtual Vector2di getDimensions();                   // renderstoa null surfaxe in order to get the dims

        virtual void render();
        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
        #endif

        /// Set text properties - inherited from the text handler passed in
        void setTextHandler(Text* pointer){text = pointer;}
        void setMenuItemText(CRstring text){menuItemText = text;}
        void setTextSelectionColour(const Colour& c){selectedColour = c;}
        void setSelectionIndicator(CRchar c){selectionIndicator = c;}

    protected:
        virtual void init();

    private:
        string menuItemText;
        Text* text;             //   Pointer to a Text the actual Text is shared through the menu items
        Colour selectedColour;
        char selectionIndicator;
};

#endif // STRINGMENUITEM_H_INCLUDED
