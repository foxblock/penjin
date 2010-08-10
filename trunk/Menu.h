#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <vector>
using std::vector;

#include "PenjinErrors.h"
#include "MenuItem.h"
#include "StringMenuItem.h"
#include "DirMenuItem.h"

#ifndef PENJIN_ASCII
    #include "AnimationStringMenuItem.h"
    #include "AnimationMenuItem.h"
    #include "ImageMenuItem.h"
    #include "ImageStringMenuItem.h"
#endif


class Menu
{
    public:

        Menu();
        virtual ~Menu();

        /// process menu operations and draw to screen respectively.
        void update();

        //  No need to pass a surface pointer in OpenGL
        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);
            void render(){render(screen);}
        #else
            void render();
        #endif

        /// Change active selection
        void menuUp();
        void menuDown();

        /// Report active selection
        int getSelection()
        {
            #ifdef PENJIN_ASCII
                cout << "Enter Selection:";
                cin >> currentSelection;
            #endif
            return currentSelection;
        }

        void setSelection(CRint curr){currentSelection = curr;}
        bool setMouseSelection(const Vector2di& mousePos){return setMouseSelection(mousePos.x, mousePos.y);}
        bool setMouseSelection(CRint x,CRint y);   //  Returns true if mouse is hovering over a section false otherwise
        Vector2df getSelectionPosition()const{return menuItems.at(currentSelection)->getPosition();}

        /// Set the topleft corner of the menu
        #ifndef PENJIN_3D
            void setMenuStart(const Vector2di& start){menuStart = start;}
            void setMenuStart(CRint x,CRint y){menuStart.x = x; menuStart.y = y;}
            void setMenuStart(const Vector2dx& start){menuStart.x = start.x.intValue >> 16; menuStart.y = start.y.intValue >> 16;}
            Vector2df getMenuStart() const {return menuStart;}
        #else
            void setMenu3D(CRbool menu3D){this->menu3D = menu3D;}         //  Will render all menuItems as Cuboids rather than rects
            void setAngle(CRfloat angle){this->angle = angle;}
            void setAngleDelta(CRfloat angleDelta){this->angleDelta = angleDelta;}
            void setMenuStart(const Vector3df& start){menuStart = start;}
            void setMenuStart(CRfloat x,CRfloat y){setMenuStart(x,y,0.0f);}
            void setMenuStart(CRfloat x,CRfloat y,CRfloat z){menuStart.x = x; menuStart.y = y; menuStart.z = z;}
            void setMenuItemDimensions(CRuint index,const Vector2di& dimensions);   //  Overide the size
            void setMenuItemDimensions(const Vector2di& dimensions){setMenuItemDimensions(menuItems.size()-1, dimensions);}
            Vector3df getMenuStart() const {return menuStart;}
        #endif
        Vector2di getMenuDimensions();                     //  Get the width and height of the entire menu

        /// Set the spacing that should be left in between each menu item.
        void setSpacing(CRint spacing);               //  Globally set spacing. (do after all menu options are created.)
        void setSpacing(CRuint index,CRint spacing);    //  Set an individual menuItem spacing.
        void setHorizontalOffset(CRint offset);
        void setHorizontalOffset(CRuint index, CRint offset);

        void setTextCenteringCorrection(CRint numPix){correction = numPix;}

        /// Adding menu items
        void addItem(CRint type);         //  Add a specific menu item

        /// Removing menu items
        void removeItem(CRint itemNum);                   //  Remove a specifc item from the menu
        void removeItem();                              //  Remove the last item on the menu
        void clear();                                   //  Clear the menu completely.

        /// Size operations
        size_t size()const{return menuItems.size();}
        bool empty()const{return !size();}

        /// MenuItem functions
        void setIsSelectable(CRuint item,CRbool isSelectable);
        void setIsSelectable(CRbool isSelectable);        //  Set the last menu item's selectability

        /// StringMenuItem functions
        #ifndef PENJIN_ASCII
            PENJIN_ERRORS loadFont(CRstring fontName,CRint fontSize);   //  Load a font into the shared Text
            void setTextColour(const Colour& colour);              //  Set the colour of the text
            void setTextSelectionColour(const Colour& colour){textSelectionColour = colour;}
            void setTextBgColour(const Colour& col){text->setBgColour(col);}
            void setTransparentColour(Colour c);
            Text* getTextObject() {return text;}; // use this to make advanced changes to the text, like alignment and render mode
            #ifdef PENJIN_SDL
                void setUseHardware(CRbool use);
            #endif
            /// ImageMenuItem functions
            PENJIN_ERRORS loadImage(CRuint item,CRstring fileName);      //  Load an image for a specific menu item
            PENJIN_ERRORS loadImage(CRstring fileName);                //  Load an Image for the last MenuItem
            PENJIN_ERRORS loadSelectionImage(CRstring fileName);       //  Load an selection image into the last MenuItem
            PENJIN_ERRORS loadSelectionImage(CRuint item,CRstring fileName);//  Load selection image for a specific MenuItem

            /// AnimationMenuItem functions
            PENJIN_ERRORS loadFrame(CRuint index,CRstring fileName);    //  Load an individual frame of animation in a specific menu item
            PENJIN_ERRORS loadFrame(CRstring fileName);                //
            PENJIN_ERRORS loadFrames(CRuint index,CRstring tileSheet,CRuint xTiles,CRuint yTiles);    //  load a tilesheet animation for this menu item
            PENJIN_ERRORS loadFrames(CRstring tileSheet,CRuint xTiles,CRuint yTiles);
            PENJIN_ERRORS loadSelectionFrame(CRstring fileName);   //  Load a shared image for selections
            PENJIN_ERRORS loadSelectionFrames(CRstring tileSheet,CRuint xTiles,CRuint yTiles);
            PENJIN_ERRORS loadSelectionFrame(CRuint index,CRstring fileName);
            PENJIN_ERRORS loadSelectionFrames(CRuint index,CRstring tileSheet,CRuint xTiles,CRuint yTiles);

            void setFrameRate(CRuint fps);                    //  Set the animation frame rate
            void setLooping(CRint numLoops);                  //  set num loops, -1 is infinite.
            void setLooping(CRbool shouldLoop);               // true == infinite looping, false == no looping
            void setReversePlay(CRbool reverse);              //  Reverse playback on last frame?
        #endif
        void setMenuItemText(CRstring text);              //  Set the topmost menu item text properties
        void setMenuItemText(CRuint index,CRstring text);  //  Set the display text of the menu item
        void setSelectionIndicator(CRchar c);             //  Set the character acting as a selection indicator GLOBAL
        void setSelectionIndicator(CRuint index,CRchar c); //  Set the character indicating a selection for a specific menu item
        void centreText();

    protected:
        vector <MenuItem*>   menuItems;     //  Stores the individual menu entries

    private:
        void updatePositions();

        #ifndef PENJIN_3D
            Vector2df   menuStart;              //  Stores the topleft coord of the menu
        #else
            Vector3df   menuStart;
            bool menu3D;
            float angle;
            float angleDelta;
        #endif
        #ifdef PENJIN_SDL
            SDL_Surface* screen;
        #endif
        #ifndef PENJIN_ASCII
            Text* text;                  //  Shared Text. Only created if needed
            Colour textSelectionColour;
        #endif

        int currentSelection;               //  Stores the current selection of the menu
        int correction;
};

#endif // MENU_H_INCLUDED
