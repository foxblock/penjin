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
#ifndef BASESTATE_H
#define BASESTATE_H

/*
A Template game state. This should not be used directly. It should only be used as a template for your own custom states
through inheritence
*/

#include <vector>
using std::vector;
#include "PenjinTypes.h"

#ifndef PENJIN_ASCII
    #include "SimpleJoy.h"
    #include "GFX.h"
#endif

#ifdef PENJIN_SDL
    #include <SDL/SDL.h>
#elif PENJIN_GL
    #include <SDL/SDL_opengl.h>
#elif PENJIN_ES || defined(PENJIN_ES2)
#endif

#ifdef USE_ACHIEVEMENTS
    #include "AchievementSystem.h"
    #define ACHIEVEMENTS (AchievementSystem::GetSingleton())
#endif

#ifndef STATE_NULL
	#define STATE_NULL 0	//	Exit the program
#endif	//	STATE_NULL
#ifndef STATE_BASE
	#define	STATE_BASE 1	//	Standard state
#endif	//	STATE_BASE

class BaseState
{
	public:
		BaseState();
		virtual ~BaseState();

		//  These virtual functions will be overridden depending on use
		#ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
            virtual void render(){render(GFX::getVideoSurface());}
            virtual void pauseScreen(SDL_Surface* screen);
            virtual void pauseScreen(){pauseScreen(GFX::getVideoSurface());}
		#else
            virtual void render();		//	Draw all objects
            virtual void pauseScreen();
        #endif
        virtual void pauseUpdate();     //  Update to run when paused

        virtual void onPause(){;}       //  Do stuff when just paused
        virtual void onResume(){;}      //  Do stuff when unpausing

		virtual void update();		    //	Update all objects (lited to frame rate)
		virtual void unlimitedUpdate(); //  Update not restricted by frame rate
		virtual void userInput();	    //	Take user input
		virtual void pauseInput();      //  Take user input on pauseScreen
		virtual void init();		    //	init function for states if you need to setup variables etc


        /// Pausing
        bool getIsPaused()const{return isPaused;}
        bool getFirstPaused()const{return firstPaused;}
        void setFirstPaused(CRbool pause){firstPaused = pause;}

		/// State Management
		uint getNextState()const{return nextState;}
		void setNextState(CRuint next){nextState = next;needInit = true;}
		bool getNeedInit()const{return needInit;}
		void setNeedInit(CRbool init){needInit = init;}
		bool getNullifyState()const{return nullify;}
		void nullifyState(){nullify = true;nextState = STATE_NULL;}
		#ifndef PENJIN_ASCII
            void setSimpleJoy(SimpleJoy* sj);//{input = sj;}
            SimpleJoy* getInput() {return input;};
        #endif
		//	This is used to pass variables between states!
		vector<Variable> variables;

	protected:
        #ifndef PENJIN_ASCII
            SimpleJoy* input;
            SDL_Event event;
        #endif
		bool nullify;
		bool needInit;
		uint nextState;
		bool firstPaused;
        bool isPaused;
    #ifdef PENJIN_SDL
        virtual void pauseSymbol(SDL_Surface* screen);
        virtual void pauseSymbol(){pauseSymbol(GFX::getVideoSurface());}
    #else
        virtual void pauseSymbol();
    #endif
        void pauseToggle(){isPaused = !isPaused;}
};
#endif	// BASESTATE_H
