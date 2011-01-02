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
#ifndef WIIJOY_H
#define WIIJOY_H

#ifdef PLATFORM_WII
    #include <wiiuse/wpad.h>
#else
    #include <SDL/SDL.h> // used for testing PC versions of code
#endif
class WiiJoy
{
    public:
        WiiJoy();
        ~WiiJoy();
        void init()
        {
            #ifdef PLATFORM_WII
                WPAD_Init();
            #endif
        }
        void deInit()
        {
            #ifdef PLATFORM_WII
                WPAD_Shutdown();
            #endif
        }

        void update();					//	Get current status of input
        #ifdef PLATFORM_PC
            void keyDown(const SDLKey& key);
            void keyUp(const SDLKey& key);
        #endif

        /// Wiimote
        //  0 - not pressed
        //  1 - pressed
        //  2 - held
        int isUp(){return Up;}
        int isDown(){return Down;}
        int isLeft(){return Left;}
        int isRight(){return Right;}
        int isA(){return A;}
        int isB(){return B;}
        int isOne(){return One;}
        int isTwo(){return Two;}
        int isPlus(){return Plus;}
        int isMinus(){return Minus;}
        int isStart(){return Plus;}
        int isSelect(){return Minus;}
        int isHome(){return Home;}

        void resetKeys();

    protected:
    private:
        #ifdef PLATFORM_WII
            void checkPressed();
            void checkHeld();
        #endif
        int Up, Down, Left, Right, A, B, One, Two, Plus, Minus, Home;
};

#endif // WIIJOY_H
