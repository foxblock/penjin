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
#include "Game2d.h"
#include "ApplicationState.h"
using Penjin::Game2d;
using Penjin::ApplicationState;

Game2d::Game2d()
{
    //ctor
}

Game2d::~Game2d()
{
    //dtor
}


void Game2d::loop()
{
    while(!state->shouldQuit())
    {
        state->input();
        state->update();
        state->render();
    }
}
