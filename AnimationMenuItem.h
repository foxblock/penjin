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
#ifndef ANIMATIONMENUITEM_H_INCLUDED
#define ANIMATIONMENUITEM_H_INCLUDED

#include "MenuItem.h"
#include "AnimatedSprite.h"

class AnimationMenuItem : public MenuItem
{
    public:
        AnimationMenuItem(){init();}
        AnimationMenuItem(CRstring tilesheet,CRuint xTiles,CRuint yTiles){init();anim.loadFrames(tilesheet,xTiles,yTiles);}
        AnimationMenuItem(AnimatedSprite* selectedAnim){init();selection = selectedAnim;}

        virtual ~AnimationMenuItem();

        virtual void update();
        virtual  Vector2di getDimensions();

        #ifdef PENJIN_SDL
            void setUseHardware(CRbool use);
            virtual void render(SDL_Surface* screen);
        #else
            virtual void render();
        #endif

        /// Animation specific functions
        PENJIN_ERRORS loadFrame(CRstring fileName);
        PENJIN_ERRORS loadFrames(CRstring tileSheet,CRuint xTiles,CRuint yTiles);
        PENJIN_ERRORS loadSelectionFrame(CRstring fileName);
        PENJIN_ERRORS loadSelectionFrames(CRstring tileSheet,CRuint xTiles,CRuint yTiles);
        void setFrameRate(const TimerScalers& fps){anim.setFrameRate(fps);}
        void setLooping(CRint numLoops){anim.setLooping(numLoops);}
        void setLooping(CRbool shouldLoop){anim.setLooping(shouldLoop);}
        void setReversePlay(CRbool reverse){anim.setReversePlay(reverse);}
        void setPulsePlay(CRbool pulse){anim.setPulsePlay(pulse);}

    protected:
        virtual void init();

    private:
        AnimatedSprite anim;
        AnimatedSprite* selection;
};

#endif // ANIMATIONMENUITEM_H_INCLUDED
