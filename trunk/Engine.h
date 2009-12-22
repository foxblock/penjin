#ifndef ENGINE_H
#define ENGINE_H

#include "PenjinIncludes.h"	//	List all inclusions in this file
#include "PenjinStates.h"		//	List all game states in this file
#include "PenjinTypes.h"		//	All Penjin types listed here.
#include "StringUtility.h"
#include "Sound.h"
#include "Text.h"
#ifdef USE_ACHIEVEMENTS
    #include "AchievementSystem.h"
    #define ACHIEVEMENTS (AchievementSystem::GetSingleton())
#endif
#ifdef PLATFORM_GP2X
#include "MMUHack.h"
#endif

using namespace StringUtility;

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

		bool stateLoop();								//	Main game loop (true == continue execution, false == quit)

		///	Variable relaying between states
		void setVariables();
		void getVariables();

		//	Functions for engine setup
		void setAppName(CRstring name){appName = name;}
		void setInitialState(CRuint nextState)
		{
			if(!state)
			{
				state = NULL;
				state = new BaseState;
			}
			state->setNextState(nextState);
		}

	protected:
        string customControlMap;        //  filename for a controlmapping file
		string appName;					//	The application's name
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
		Timer gameTimer;				//	Timer for frame regulation and event scheduling.
		uint now;
		SimpleJoy* input;
		#ifdef _DEBUG
            float calcFPS()
            {
                static float fps = 0.0f;
                static float lastTime = 0.0f;
                float currentTime = SDL_GetTicks();
                fps = fps*0.9f+(100.0f/(currentTime - lastTime));
                lastTime = currentTime;
                return fps;
            }
		#endif

        uint timeRemaining(CRuint x)
        {
            static uint nextTime = 0;
            now = SDL_GetTicks();
            if (nextTime <= now)
            {
                nextTime = now + x;
                return(0);
            }
            return(nextTime - now);
        }


};

#endif	//	ENGINE_H

