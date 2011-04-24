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
#ifndef ANIMATION_H
#define ANIMATION_H

#include "AnimatedSprite.h"
namespace Penjin
{
    class Animation : public AnimatedSprite // same as AnimatedSprite, but without auto-keying
    {
        public:
            virtual PENJIN_ERRORS loadFrame(CRstring fileName);     // adds a frame of animation for this sprite
            virtual PENJIN_ERRORS loadFrames(CRstring fileName,CRuint xTiles,CRuint yTiles); // loads a spritesheet for animations
    };
}
#endif	//	ANIMATION_H
