/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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
#include "Widget.h"
#include "Line.h"
#include "SimpleJoy.h"
using Penjin::Widget;
using Penjin::Line;

Widget::Widget() : lowLight(NULL), highLight(NULL), active(false), selected(false)
{
    //ctor
    lowLight = new Line;
    highLight = new Line;
}

Widget::~Widget()
{
    //dtor
    delete lowLight;
    delete highLight;
}

void Widget::render()
{
    Rectangle::render();
    Vector2d<int> t;
    // left highlight
    highLight->setPosition(Rectangle::position);
    t.x = Rectangle::position.x;
    t.y = Rectangle::position.y + dimensions.y;
    highLight->setEndPosition(t);
    highLight->render();
    // bottom low light
    lowLight->setPosition(t);
    t.x = Rectangle::position.x + dimensions.x;
    lowLight->setEndPosition(t);
    lowLight->render();
    // right low light
    lowLight->setPosition(t);
    t.y = Rectangle::position.y;
    lowLight->setEndPosition(t);
    lowLight->render();
    // top high light
    highLight->setEndPosition(t);
    highLight->render();
}

void Widget::setHighLightColour(const Colour& c)
{
    highLight->setColour(c);
}

void Widget::setLowLightColour(const Colour& c)
{
    lowLight->setColour(c);
}

void Widget::setActive(const bool& a)
{
    active = a;
}

bool Widget::isActive()
{
    return active || isMouseActive();
}

bool Widget::isMouseSelected()
{
    Vector2d<int> m = Joy::getInstance()->getMouse();
    if( m.x > position.x &&
        m.x < position.x + dimensions.x &&
        m.y > position.y &&
        m.y < position.y + dimensions.y
    )
        return true;
    return false;
}

bool Widget::isMouseActive()
{
    return (isMouseSelected() && Joy::getInstance()->isLeftClick());
}

void Widget::setSelected(const bool& s)
{
    selected = s;
}

bool Widget::isSelected()
{
    return (isMouseSelected() || selected);
}