#ifndef BASESTATE_H
#define BASESTATE_H

/*
A Template game state. This should not be used directly. It should only be used as a template for your own custom states
through inheritence
*/

#include <vector>
using std::vector;
#include "PenjinTypes.h"
#include "SimpleJoy.h"
#include "GFX.h"

#ifdef PENJIN_SDL
    #include <SDL/SDL.h>
#endif
#ifdef PENJIN_GL
    #include <SDL/SDL_opengl.h>
#endif

#ifndef STATE_NULL
	#define STATE_NULL 0	//	Exit the program
#endif	//	STATE_NULL
#ifndef STATE_BASE
	#define	STATE_BASE 1	//	Standard state
#endif	//	STATE_BASE

class  BaseState
{
	public:
		BaseState();
		virtual ~BaseState();

		//  These virtual functions will be overridden depending on use
		#ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
            virtual void render(){render(screen);}
            virtual void pauseScreen(SDL_Surface* screen);
            virtual void pauseScreen(){pauseScreen(screen);}
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

        /// Resolution
		void setStateResolution(uint* xRes, uint* yRes){this->xRes = xRes;this->yRes = yRes;}
		uint getStateXResolution()const{return *xRes;}
		uint getStateYResolution()const{return *yRes;}

		void setSimpleJoy(SimpleJoy* sj){input = sj;}

		//	This is used to pass variables between states!
		vector<Variable> variables;

	protected:
        SimpleJoy* input;
		bool nullify;
		bool needInit;
		uint nextState;
		bool firstPaused;
        bool isPaused;

		uint* xRes;		//	Points to the engines resolutions
		uint* yRes;
		SDL_Event event;

        virtual void keyDown(const SDLKey& key);
        virtual void keyUp(const SDLKey& key);
        virtual void joyMotion(const Uint8& axis,const Sint16& value);
        virtual void joyButtonDown(const Uint8& button);
        virtual void joyButtonUp(const Uint8& button);
        virtual void mouseButtonDown(const Uint16& x,const Uint16& y);
        virtual void mouseButtonUp(const Uint16& x,const Uint16& y);
        virtual void mouseMotion(const Uint16& x,const Uint16& y);
    #ifdef PENJIN_SDL
        virtual void pauseSymbol(SDL_Surface* screen);
        SDL_Surface* screen;
    #else
        virtual void pauseSymbol();
    #endif
        void pauseToggle(){isPaused = !isPaused;}
};
#endif	// BASESTATE_H
