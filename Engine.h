#ifndef ENGINE_H
#define ENGINE_H

#include "PenjinIncludes.h"	//	List all inclusions in this file
#include "PenjinStates.h"		//	List all game states in this file
#include "PenjinTypes.h"		//	All Penjin types listed here.
#include "StringUtility.h"
using namespace StringUtility;

/* This is a base engine class. You do not use this directly, it is inherited by and overridden by a child class.
This can be seen as a template for your main application.

If you look in the Engine.cpp file, you will see the sort of things you should be doing when you over ride this classes functionality.
*/

class Engine
{
	public:
		Engine();
		Engine(CRstring appName,CRint xRes,CRint yRes,CRbool fullScreen);
		virtual ~Engine();

		virtual PENJIN_ERRORS argHandler(int argc, char** argv);	//	Handle the command line.
		virtual PENJIN_ERRORS init();								//	Sets up the engine, can return an error.
		virtual void stateManagement();					//	Setup next state if needed.

		bool stateLoop();								//	Main game loop (true == continue execution, false == quit)

		///	Variable relaying between states
		void setVariables();
		void getVariables();

		//	Functions for engine setup
		void setAppName(CRstring name){appName = name;}
		void setScreenResolution(CRuint xRes,CRuint yRes){this->xRes = xRes;this->yRes = yRes;}
		void setInitialState(CRuint nextState)
		{
			if(!state)
			{
				state = NULL;
				state = new BaseState;
			}
			state->setNextState(nextState);
		}
		void setFullScreen(CRbool fs){this->fullScreen = fs;}	//	true == fullscreen	false == windowed

	protected:
		string appName;					//	The application's name
		uint xRes;						//	Screen dimensions
		uint yRes;
		bool fullScreen;				//	Fullscreen == true, Windowed == false
		bool paused;
		BaseState* state;				//	The current game state
		SDL_Surface* screen;
		vector<Variable> variables;		//	Variable storage for transfer between states
		Timer gameTimer;				//	Timer for frame regulation and event scheduling.
		SimpleJoy* input;
		#ifdef _DEBUG
            int frameCount;             //  Keeps track of the num updates...
		#endif
};

#endif	//	ENGINE_H

