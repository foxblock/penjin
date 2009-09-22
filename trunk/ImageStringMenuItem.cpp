#include "ImageStringMenuItem.h"

ImageStringMenuItem::~ImageStringMenuItem()
{
}

void ImageStringMenuItem::init()
{
    setType(MENU_IMAGE_STRING_ITEM);
    position.x = 0;
    position.y = 0;
    #ifdef PENJIN3D
        position.z = 0.0f;
    #endif
    dimensions.x = 0;
    dimensions.y = 0;
    isSelected = false;
    isSelectable = true;
    verticalSpacing = 0;
    horizontalOffset = 0;
    text.setSelectionIndicator('-');
    menuImage.setHorizontalOffset(horizontalOffset);
    text.setHorizontalOffset(horizontalOffset);
}

void ImageStringMenuItem::update()
{
    menuImage.setIsSelected(isSelected);
    menuImage.update();

    text.setIsSelected(isSelected);
    text.update();
}

void ImageStringMenuItem::render()
{
    menuImage.render();
    text.render();
}

#ifdef PENJIN_SDL
void ImageStringMenuItem::render(SDL_Surface* screen)
{
    menuImage.render(screen);
    text.render(screen);
}
#endif

Vector2di ImageStringMenuItem::getDimensions()
{
    Vector2di dims, txtDims;
    dims = menuImage.getDimensions();
    txtDims = text.getDimensions();

    if(dims.x >= txtDims.x)
        dimensions.x = dims.x;
    else
        dimensions.x = txtDims.x;

    if(dims.y >= txtDims.y)
        dimensions.y = dims.y;
    else
        dimensions.y = txtDims.y;

    return dimensions;
}

#ifndef PENJIN3D
    void ImageStringMenuItem::setPosition(const Vector2df& pos)
    {
        position = pos;
        menuImage.setPosition(pos);
        text.setPosition(pos);
    }
#else
    void ImageStringMenuItem::setPosition(const Vector3df& pos)
    {
        position = pos;
        menuImage.setPosition(pos);
        text.setPosition(pos);
    }
#endif

void ImageStringMenuItem::centreText()
{
    /// Get the difference of the text and the animFrame
    #ifndef PENJIN3D
        Vector2di diff = text.getDimensions()-menuImage.getDimensions();
    #else
        Vector3df temp;
        Vector2di iTemp = text.getDimensions();
        temp.x = (float)iTemp.x;
        temp.y = (float)iTemp.y;
        Vector3df mTemp;
        iTemp = menuImage.getDimensions();
        mTemp.x = (float)iTemp.x;
        mTemp.y = (float)iTemp.y;
        Vector3df diff = temp-mTemp;
    #endif

    diff.x *= 0.5f;
    diff.y *= 0.5f;
    diff.x+=25;
    text.setPosition(position - diff);
}
