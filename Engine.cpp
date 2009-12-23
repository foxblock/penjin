#include "Engine.h"

Engine::Engine()
{
	///	Default constructor
	Penjin::setApplicationName("Penjin");
    #if PLATFORM_GP2X
        loadMenu = false;
    #endif

	gameTimer.setMode(SIXTY_FRAMES);
    input = NULL;
    now = SDL_GetTicks();
    state = NULL;
	state = new BaseState;
	setInitialState(STATE_BASE);
	gameTimer.start();
	Random::randSeed();
    input = NULL;
    input = new SimpleJoy();
    customControlMap = "NULL";
}

Engine::~Engine()
{
    if(state)
    {
        delete state;
        state = NULL;
    }
    if(input)
	{
        delete input;
        input = NULL;
	}
	SoundClass::deInit();
	TextClass::deInit();
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
					//	Set Fullscreen
					case 'F':
					{
						GFX::setFullscreen(true);
						break;
					}
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
        state->setSimpleJoy(input);
    }
}

PENJIN_ERRORS Engine::init()
{
    return GFX::resetScreen();
}

PENJIN_ERRORS Engine::penjinInit()
{
	GFX::setResolution();
#if defined (PENJIN_SDL) || defined(PENJIN_GL)
    //Initialize SDL's subsystems.
    if( SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0 )
		return PENJIN_SDL_SOMETHING_FAILED;
#endif
    PENJIN_ERRORS err = init();
    if(err != PENJIN_OK)
        return err;
	#ifdef _DEBUG
        GFX::showVideoInfo();
	#endif
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    GFX::showCursor(false);
    //  Can't display window title on a GP2X
    #ifndef PLATFORM_GP2X
        string appName = Penjin::getApplicationName();
        #if defined(PENJIN_SDL) || defined(PENJIN_GL)
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
    if(customControlMap != "NULL")
        input->loadControlMap(customControlMap);

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
    SoundClass::init();
    TextClass::init();
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
        if(state->getNeedInit())
            return true;
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
            if(gameTimer.getScaledTicks() > 1)
            {
                state->pauseInput();
                state->pauseUpdate();
                GFX::lockSurface();
                state->pauseScreen();
                GFX::unlockSurface();
                //	Flush the cache on GP2X just before the screen is flipped
                GFX::forceBlit();
                gameTimer.start();
            }
            else
                SDL_Delay(50);
        }
        else if(!state->getIsPaused() && state->getFirstPaused())
        {
            state->onResume();
            state->setFirstPaused(false);
        }
		else if(gameTimer.getScaledTicks() > 1)
		{
			gameTimer.start();
			state->userInput();
			state->update();
			#ifdef USE_ACHIEVEMENTS
			ACHIEVEMENTS->update();
			#endif

			if(state->getNeedInit())
                return true;
			//  Render objects
			GFX::lockSurface();
            state->render();
            #ifdef USE_ACHIEVEMENTS
            ACHIEVEMENTS->render(GFX::getVideoSurface());
            #endif
            GFX::unlockSurface();
            GFX::forceBlit();
            #ifdef _DEBUG
                int frameCount = calcFPS();
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
		}
		else
		{
            SDL_Delay(timeRemaining((uint)gameTimer.getScaler()));  // Release CPU briefly
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
		state->setNeedInit(false);  // Set that we have performed the init
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


