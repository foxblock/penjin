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
#include "Engine.h"

#include "StringUtility.h"
#ifndef PENJIN_ASCII
    #include "Sound.h"
    #include "Text.h"
#else
    #include "Random.h"
#endif
#ifdef USE_ACHIEVEMENTS
    #include "AchievementSystem.h"
    #define ACHIEVEMENTS (AchievementSystem::GetSingleton())
#endif

using namespace StringUtility;

Engine::Engine()
{
	///	Default constructor
	Penjin::setApplicationName("Penjin");
    #if PLATFORM_GP2X
        loadMenu = false;
    #endif

    state = NULL;
	state = new BaseState;
	setInitialState(STATE_BASE);

	gameTimer = new Timer;

#ifndef PENJIN_ASCII
    input = NULL;
    customControlMap = "NULL";
#endif
}

Engine::~Engine()
{
    if(state)
    {
        delete state;
        state = NULL;
    }
    delete gameTimer;
    #ifndef PENJIN_ASCII
        if(input)
        {
            delete input;
            input = NULL;
        }
        SoundClass::deInit();
        TextClass::deInit();
	#endif
	#ifdef PENJIN_CACA
        caca_free_display(display);
        cucul_free_canvas(canvas);
    #elif PENJIN_ASCII
        endwin();
	#endif
	#ifdef PLATFORM_GP2X
        MMUHack::deInit();
        if(loadMenu)	//	Quit to GP2X menu if required to do so by commandline.
		{
			chdir("/usr/gp2x");
			execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
		}
    #elif   PLATFORM_WII
        Penjin::deInitFileSystem(); // shutdown FAT
	#endif
	#if defined(PENJIN_SDL) || defined(PENJIN_GL)
        #ifdef PENJIN_SCALE2X
            GFX::shutdown();
        #endif
        SDL_Quit();
    #elif defined (PENJIN_ES) || defined (PENJIN_ES2)
        GFX::shutdown();
        SDL_Quit();
	#endif
}

void Engine::setInitialState(CRuint nextState)
{
    if(!state)
    {
        state = NULL;
        state = new BaseState;
    }
    state->setNextState(nextState);
}

void Engine::setFrameRate(CRuint fpsDesired)
{
    gameTimer->setScaler(1000 / (float)fpsDesired);
}

PENJIN_ERRORS Engine::argHandler(int argc, char **argv)
{
	//	This is just an example of how to handle commandlines, you would override this depending on actual needs.
	if(argc <= 1)
		return	PENJIN_NO_COMMANDLINE;
	else
	{
		//	Do further CMD processing
		for (int arg = 1; arg < argc; ++arg)
		{
			//	Check for commandline escape chars
			if(argv[arg][0] == '-' || argv[arg][0] == '/')
			{
				//	Look for arguements
				switch(argv[arg][1])
				{
                    //  Load CMF - Custom controls
				    case 'C':
				    {
				        customControlMap = argv[arg+1];
				        break;
                    }
					//	Set Fullscreen
					#ifndef PENJIN_ASCII
					case 'F':
					{

						GFX::setFullscreen(true);
						break;
					}
					#endif
/*					//	Set xRes
					case 'x':
					case 'X':
					{
						xRes = cStringToInt(argv[arg+1]);
						break;
					}
					//  Set yRes
					case 'y':
					case 'Y':
					{
                        yRes = cStringToInt(argv[arg+1]);
					    break;
					}
*/
					#ifdef PLATFORM_GP2X
                    case 'M':
                    case 'm':
				    {
				        loadMenu = true;
				        break;
                    }
					#endif
					default:
					{
						return PENJIN_INVALID_COMMANDLINE;
					}
				}
			}
		}
	}
	return	PENJIN_OK;
}

void Engine::getVariables()
{
    if(state)
    {
        variables.clear();
        uint iMax = (uint)state->variables.size();
        for(uint i = 0; i < iMax;++i)
            variables.push_back(state->variables[i]);
    }

}

void Engine::setVariables()
{
    if(state)
    {
        state->variables.clear();
        uint iMax = (uint)variables.size();
        for(uint i = 0; i < iMax;++i)
            state->variables.push_back(variables[i]);
        #ifndef PENJIN_ASCII
            state->setSimpleJoy(input);
        #endif
    }
}

PENJIN_ERRORS Engine::init()
{
    #ifndef PENJIN_ASCII
        return GFX::resetScreen();
    #else
        return PENJIN_OK;
    #endif
}

PENJIN_ERRORS Engine::penjinInit()
{
    #ifndef PENJIN_ASCII
        GFX::setResolution();
	#endif
    #if defined (PENJIN_SDL) || defined(PENJIN_GL)
        //Initialize SDL's subsystems.
        if( SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0 )
            return PENJIN_SDL_SOMETHING_FAILED;
    #elif defined (PENJIN_ES) || defined (PENJIN_ES2)
        if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0 )
            return PENJIN_SDL_SOMETHING_FAILED;
    #endif
    gameTimer->setMode(SIXTY_FRAMES); // default framerate (60)
    PENJIN_ERRORS err = init();
    if(err != PENJIN_OK)
        return err;
	#ifdef _DEBUG
        #ifndef PENJIN_ASCII
            GFX::showVideoInfo();
        #endif
	#endif
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    #ifndef PENJIN_ASCII
        GFX::showCursor(false);
    #endif
    //  Can't display window title on a GP2X
    #ifndef PLATFORM_GP2X
        string appName = Penjin::getApplicationName();
        #if defined(PENJIN_SDL) || defined(PENJIN_GL) || defined(PENJIN_ES) || defined(PENJIN_ES2)
            SDL_WM_SetCaption((appName + " V" + AutoVersion::FULLVERSION_STRING + AutoVersion::STATUS_SHORT).c_str(), NULL);
        #endif
        #ifdef PENJIN_CACA
            caca_set_display_title(display, (appName + " V" + AutoVersion::FULLVERSION_STRING + AutoVersion::STATUS_SHORT).c_str());
        #endif
    #endif
    #ifdef PENJIN_GL
        //	Clear Accumulation buffer to avoid garbage pixels
        glClear(GL_ACCUM_BUFFER_BIT);
    #endif
    #ifdef PLATFORM_WII
        PENJIN_ERRORS e = Penjin::initFileSystem();
        if(e != PENJIN_OK)
        {
            //  Tidy up if we didn't fully mount FAT
            Penjin::deInitFileSystem();
            ErrorHandler().killApp(e);
        }
        Penjin::setWorkingDirectory("sd:/" + Penjin::getApplicationName() + "/");
    #endif

    /// TODO: add error handling for other intialisation.
    #ifndef PENJIN_ASCII
        SoundClass::init();
        TextClass::init();
        input = NULL;
        input = new SimpleJoy();
        if(customControlMap != "NULL")
            input->loadControlMap(customControlMap);
    #endif
    #ifndef PENJIN_SYS_TIMER
        now = SDL_GetTicks();
    #else
        now = clock();
	#endif
	gameTimer->start();
	Random::randSeed();

	return PENJIN_OK;
}

bool Engine::stateLoop()
{
	//  Check state for exit condition
	if(state->getNullifyState())
	{
		state->nullifyState();
		return false;  // End program execution
	}
	else if (state->getNeedInit() == false)
	{
        //  Update physics
        state->unlimitedUpdate();
        if(state->getNeedInit())
            return true;
		//  Update timer and check if ticks have passed
		if(state->getIsPaused())
		{
		    // check if it is only just paused and run tasks on pausing
		    if(!state->getFirstPaused())
		    {
		        state->onPause();
		        state->setFirstPaused(true);
            }

            // the following will always last at least the time of one frame
            gameTimer->start();
            state->pauseInput();
            state->pauseUpdate();
            #ifdef PENJIN_SDL
                //GFX::lockSurface();
            #endif
            state->pauseScreen();
            #ifdef PENJIN_SDL
                //GFX::unlockSurface();
            #endif
            #ifndef PENJIN_ASCII
                GFX::forceBlit();
            #endif
			// if done in time, wait for the rest of the frame
			limitFPS(gameTimer->getScaler() - gameTimer->getTicks());
        }
        else if(!state->getIsPaused() && state->getFirstPaused())
        {
            state->onResume();
            state->setFirstPaused(false);
        }
		else
		{
            // the following will always last at least the time of one frame
			gameTimer->start();
			state->userInput();
			state->update();
			#ifdef USE_ACHIEVEMENTS
                ACHIEVEMENTS->update();
			#endif

			if(state->getNeedInit())
                return true;
			//  Render objects
            #ifdef PENJIN_SDL
                //GFX::lockSurface();
            #endif
            state->render();
            #ifdef USE_ACHIEVEMENTS
                #ifdef PENJIN_SDL
                    ACHIEVEMENTS->render(GFX::getVideoSurface());
                #else
                    ACHIEVEMENTS->render();
                #endif
            #endif
            #ifdef PENJIN_SDL
                //GFX::unlockSurface();
            #endif
            #ifndef PENJIN_ASCII
                GFX::forceBlit();
            #endif
            #ifdef _DEBUG
                frameCount = calcFPS();
                #ifdef PENJIN_SDL
                    if(frameCount>=20)//only update if there are a reasonable number of redundant updates
                    {
                        //  This code seems to slow down Linux builds majorly.
                        SDL_WM_SetCaption((Penjin::getApplicationName() + " V" + AutoVersion::FULLVERSION_STRING
                        + AutoVersion::STATUS_SHORT
                        + " "
                        + intToString(frameCount)
                        + " DEBUG "
                        + AutoVersion::DATE + "-"
                        + AutoVersion::MONTH + "-"
                        + AutoVersion::YEAR).c_str(), NULL );
                        //frameCount = 0;
                    }
                #endif
			#endif
			// if done in time, wait for the rest of the frame
			limitFPS(gameTimer->getScaler() - gameTimer->getTicks());
		}
		return true;   // Continue program execution
	}
	else
	{
		// check and change states
		getVariables();
		stateManagement();
		setVariables();

		// Initialise the changed state
		state->init();
		state->setNeedInit(false);    // Set that we have performed the init
		return true;                  // Continue program execution
	}
	//  Should never reach here
	return false;
}

void Engine::stateManagement()
{
	//	Check if the state itself wants to change states
	uint next = state->getNextState();
	if(state)
	{
		delete state;
		state = NULL;
	}
	if(next == STATE_BASE)
		state = new BaseState;
	/* EXAMPLE OF STATE CHECKING
	else if(next == STATE_TITLE)
		state = new StateTitle;*/
    else
    {
        cout << ErrorHandler().getErrorString(PENJIN_UNDEFINED_STATE);
        exit(PENJIN_UNDEFINED_STATE);
    }
}

inline void Engine::limitFPS(CRfloat sleepTime) const
{
    static float diff = 0; // value compensating the precision loss due to float-int conversions
    if (sleepTime > 0)
    {
        diff += sleepTime - (int)sleepTime;
#ifndef PENJIN_SYS_TIMER
        SDL_Delay((int)sleepTime + (int)diff);  // Release CPU briefly
#else
        sleep((int)sleepTime + (int)diff);  // Release CPU briefly
#endif
        while ((int)diff > 0)
            --diff;
    }
}

