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
#ifndef KEYBOARDDEFINES_H_INCLUDED
#define KEYBOARDDEFINES_H_INCLUDED

#include <SDL/SDL.h>

	//	The below defines correspond to the buttons on the GP2X
#ifdef PLATFORM_GP2X
	/* GP2X button mapping */
enum MAP_KEY
{
	KEYMAP_UP         , // 0
	KEYMAP_UPLEFT    , // 1
	KEYMAP_LEFT       , // 2
	KEYMAP_DOWNLEFT  , // 3
	KEYMAP_DOWN       , // 4
	KEYMAP_DOWNRIGHT , // 5
	KEYMAP_RIGHT      , // 6
	KEYMAP_UPRIGHT   , // 7
	KEYMAP_START      , // 8
	KEYMAP_SELECT     , // 9
	KEYMAP_L         , // 10
	KEYMAP_R         , // 11
	KEYMAP_A         , // 12
	KEYMAP_B         , // 13
	KEYMAP_Y         , // 14
	KEYMAP_X         , // 15
	KEYMAP_VOLUP     , // 16
	KEYMAP_VOLDOWN   , // 17
	KEYMAP_CLICK       // 18
};
#elif PLATFORM_PANDORA
enum MAP_KEY
{
    /// DPAD
	KEYMAP_UP=110,
	KEYMAP_LEFT=96,
	KEYMAP_DOWN=103,
	KEYMAP_RIGHT=98,

	KEYMAP_START=100,
	KEYMAP_SELECT=104,
	KEYMAP_L=102,
	KEYMAP_R=105,
	KEYMAP_A=111,
	KEYMAP_B=106,
	KEYMAP_Y=101,
	KEYMAP_X=109,
	KEYMAP_HOLD=176,
	KEYMAP_LID=108
};
#elif PLATFORM_PC
	#define KEYMAP_START           (SDLK_RETURN)
	#define KEYMAP_SELECT          (SDLK_RSHIFT)
	#define KEYMAP_UP              (SDLK_UP)
	#define KEYMAP_DOWN            (SDLK_DOWN)
	#define KEYMAP_LEFT            (SDLK_LEFT)
	#define KEYMAP_RIGHT           (SDLK_RIGHT)
	#define KEYMAP_UPLEFT          (SDLK_KP7)
	#define KEYMAP_UPRIGHT         (SDLK_KP9)
	#define KEYMAP_DOWNLEFT        (SDLK_KP1)
	#define KEYMAP_DOWNRIGHT       (SDLK_KP3)
	#define KEYMAP_CLICK           (SDLK_SPACE)
	#define KEYMAP_A               (SDLK_z)
	#define KEYMAP_B               (SDLK_x)
	#define KEYMAP_X               (SDLK_a)
	#define KEYMAP_Y               (SDLK_s)
	#define KEYMAP_L               (SDLK_q)
	#define KEYMAP_R               (SDLK_w)
	#define KEYMAP_VOLUP           (SDLK_v)
	#define KEYMAP_VOLDOWN         (SDLK_b)
#endif

#endif // KEYBOARDDEFINES_H_INCLUDED
