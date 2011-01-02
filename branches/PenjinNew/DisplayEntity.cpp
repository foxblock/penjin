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
#include "DisplayEntity.h"
#include "Pixel.h"
#include "Line.h"
#include "Rectangle.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Emitter.h"
DisplayEntity::DisplayEntity()
{
    //ctor
    pix = NULL;
    line = NULL;
    rect = NULL;
//    bg = NULL;
//    anim = NULL;
    sprite = NULL;
    animSpr = NULL;
    emit = NULL;
}

DisplayEntity::~DisplayEntity()
{
    //dtor
    //  We don't delete anything since pointers are passed externally
}

void DisplayEntity::setPosition(CRint x, CRint y)
{
    if(pix)
        pix->setPosition(x,y);
    else if(line)
        cout << "DisplayEntity->setPsotion -- Line unimplemented." << endl;//line->setPosition(x,y);
    else if(rect)
        rect->setPosition(x,y);
    else if(sprite)
        sprite->setPosition(x,y);
    else if(animSpr)
        animSpr->setPosition(x,y);
    else if(emit)
        emit->setPosition(Vector2di(x,y));
}

void DisplayEntity::render()
{
    if(pix)
        pix->render();
    else if(line)
        line->render();
    else if(rect)
        rect->render();
    else if(sprite)
        sprite->render();
    else if(animSpr)
        animSpr->render();
    else if(emit)
        emit->render();
}

void DisplayEntity::update()
{
    //  Update any objects that require updating.pdate();
    if(animSpr)
        animSpr->update();
    else if(emit)
        emit->update();
}

