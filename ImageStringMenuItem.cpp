/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ImageStringMenuItem.h"

ImageStringMenuItem::~ImageStringMenuItem()
{
}

void ImageStringMenuItem::init()
{
    setType(MENU_IMAGE_STRING_ITEM);
    position.x = 0;
    position.y = 0;
    #ifdef PENJIN_3D
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

#ifndef PENJIN_3D
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

void ImageStringMenuItem::centreText(CRint corr)
{
    /// Get the difference of the text and the animFrame
    #ifndef PENJIN_3D
        Vector2di diff = menuImage.getDimensions()-text.getDimensions();
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
    diff.x+=corr;
    text.setPosition(position + diff);
}
