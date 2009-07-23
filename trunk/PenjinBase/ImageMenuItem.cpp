#include "ImageMenuItem.h"

ImageMenuItem::~ImageMenuItem()
{
    if(selected)
    {
        delete selected;
        selected = NULL;
    }
}

void ImageMenuItem::init()
{
    selected = NULL;
    position.x = 0;
    position.y = 0;
    #ifdef PENJIN3D
        position.z = 0.0f;
        menu3D = false;
        angle = NULL;
    #endif
    dimensions.x = 0;
    dimensions.y = 0;
    isSelected = false;
    isSelectable = true;
    verticalSpacing = 0;
    horizontalOffset = 0;
    setType(MENU_IMAGE_ITEM);
}

PENJIN_ERRORS ImageMenuItem::loadSelection(CRstring fileName)
{
    if(selected == NULL)
        selected = new Image;
    return selected->loadImage(fileName);
}

#ifdef PENJIN_SDL
    void ImageMenuItem::render(SDL_Surface* screen)
    {
        Vector2di Offset(horizontalOffset,0);
        if(!isSelected)
            menuImage.renderImage(screen,position+Offset);
        else if (isSelected && selected)            //  Check for selection and check if a selection image exists
            selected->renderImage(screen, position+Offset);
    }
    void ImageMenuItem::render()
    {
        Vector2di Offset(horizontalOffset,0);
        if(!isSelected)
            menuImage.renderImage(position+Offset);
        else if (isSelected && selected)            //  Check for selection and check if a selection image exists
            selected->renderImage(position+Offset);
    }
#else
    void ImageMenuItem::render()
    {
        Vector3df Offset(horizontalOffset,0.0f,0.0f);
        if(!isSelected)
            menuImage.renderImage(position + Offset);
        else if (isSelected && selected)
            selected->renderImage(position + Offset);
    }
    #ifdef PENJIN3D
        void ImageMenuItem::update()
        {
            if(menu3D)
                if(isSelected)
                    selected->setRotation(Vector3df(*angle, 0.0f, 0.0f));
        }
    #endif
#endif

Vector2di ImageMenuItem::getDimensions(){return Vector2di(menuImage.getWidth(),menuImage.getHeight());}
