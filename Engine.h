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
#ifndef ENGINE_H
#define ENGINE_H

#if defined(_DEBUG) && !defined(PENJIN_CALC_FPS)
#define PENJIN_CALC_FPS
#endif

#include "PenjinIncludes.h"	//	List all inclusions in this file
#include "PenjinTypes.h"		//	All Penjin types listed here.
#include "PenjinStates.h"		//	List all game states in this file
/* This is a base engine class. You do not use this directly, it is inherited by and overridden by a child class.
This can be seen as a template for your main application.

If you look in the Engine.cpp file, you will see the sort of things you should be doing when you over ride this classes functionality.
*/

class Engine
{
	public:
		Engine();
		virtual ~Engine();

		virtual PENJIN_ERRORS argHandler(int argc, char** argv);	//	Handle the command line.
		PENJIN_ERRORS penjinInit();                                 // base init function for Penjin.
		virtual PENJIN_ERRORS init();								//	Sets up the engine, can return an error.
		virtual void stateManagement();					//	Setup next state if needed.

		virtual bool stateLoop();								//	Main game loop (true == continue execution, false == quit)

		///	Variable relaying between states
		void setVariables();
		void getVariables();

		//	Functions for engine setup
		void setInitialState(CRuint nextState);

		// Framerate
		// Pass the number of desired frames per second
		// Real framerate may differ due to device limitations and rounding errors
		// on very high framerates (>60)
		void setFrameRate(CRuint fpsDesired);

	protected:
        #ifndef PENJIN_ASCII
            string customControlMap;        //  filename for a controlmapping file
            SimpleJoy* input;
        #endif
		bool paused;
		BaseState* state;				//	The current game state
		#ifdef PENJIN_CACA
            cucul_canvas_t *canvas;
            caca_display_t *display;
		#endif
		#ifdef PLATFORM_GP2X
            bool loadMenu;
		#endif
		vector<Variable> variables;		//	Variable storage for transfer between states
		Timer* gameTimer;				//	Timer for frame regulation and event scheduling.
		uint now;
		#ifdef PENJIN_CALC_FPS
            int frameCount;
            float calcFPS()
            {
                static float fps = 0.0f;
                static float lastTime = 0.0f;
                #ifndef PENJIN_SYS_TIMER
                    float currentTime = SDL_GetTicks();
                #else
                    float currentTime = clock();
                #endif
                fps = fps*0.9f+(100.0f/max(currentTime - lastTime,1.0f));
                lastTime = currentTime;
                return fps;
            }
		#endif

        // sleeps the passed amount of milliseconds (and keeps track of rounding errors)
		void limitFPS(CRfloat sleepTime) const;
};

#endif	//	ENGINE_H
