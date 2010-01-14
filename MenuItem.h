#ifndef MENUITEM_H_INCLUDED
#define MENUITEM_H_INCLUDED

#include "PenjinTypes.h"
#if defined(PENJIN_SDL) || defined(PENJIN_GL)
    #include <SDL/SDL.h>
#endif
namespace MenuItems
{
    enum MENU_TYPES
    {
        MENU_ITEM = 0,
        MENU_STRING_ITEM,
        #ifndef PENJIN_ASCII
        MENU_IMAGE_ITEM,
        MENU_ANIM_ITEM,
        MENU_IMAGE_STRING_ITEM,
        MENU_ANIM_STRING_ITEM,
        #endif
        MENU_DIR_ITEM
    };
}

using namespace MenuItems;

class MenuItem
{
    public:
        MenuItem()
        {
            type = MENU_ITEM;
            verticalSpacing = horizontalOffset = 0;
        }
        virtual ~MenuItem();

        virtual void update();

        //  No need to pass Surface pointer to render function in OpenGL
        #ifdef PENJIN3D
            //  3D Menu Effects
            void setMenu3D(CRbool menu3D){this->menu3D = menu3D;}
            void setAngle(float* angle){this->angle = angle;}
        #endif
        virtual void render();
        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
        #endif
        void setIsSelectable(CRbool isSelectable){this->isSelectable = isSelectable;}
        bool getIsSelectable()const{return isSelectable;}
        void setIsSelected(CRbool isSelected){this->isSelected = isSelected;}
        bool isMouseSelected(CRint x,CRint y);
        void setDimensions(const Vector2di& dim){dimensions = dim;}
        virtual Vector2di getDimensions();
        #ifdef PENJIN3D
            virtual void setPosition(const Vector3df& pos){position = pos;}
            Vector3df getPosition()const{return position;}
        #else
            virtual void setPosition(const Vector2df& pos){position = pos;}
            Vector2df getPosition()const{return position;}
        #endif

        void setHorizontalOffset(CRint offset){horizontalOffset = offset;}
        int getHorizontalOffset()const{return horizontalOffset;}
        void setSpacing(CRint spacing){verticalSpacing = spacing;}
        int getSpacing()const{return verticalSpacing;}
        MENU_TYPES getType()const{return type;}
        void setType(const MENU_TYPES& type){this->type = type;}
        virtual void init();
    protected:
        bool isSelected;        //  Is this option currently selected in the menu
        bool isSelectable;      //  Is this option able to be selected in the menu

        #ifdef PENJIN3D
            Vector3df position;     //  The start position of the menu.
            bool menu3D;
            float* angle;            //  Angle of rotation for current selection
        #else
            Vector2df position;
        #endif

        Vector2di dimensions;   //  The width and height of the menu.
        int verticalSpacing;    //  This value is the space to leave above the menu item before renderring
        int horizontalOffset;   //  This corrects the position from the menu startPos
        MENU_TYPES type;
};

#endif // MENUITEM_H_INCLUDED
