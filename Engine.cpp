#include "Engine.h"

Engine::Engine()
{
	///	Default constructor
	appName = "Default Penjin Project";

	#ifdef PLATFORM_PC
        xRes = 1024;
        yRes = 768;
        fullScreen = false;
    #elif PLATFORM_WII
        xRes = 640;
        yRes = 480;
        fullScreen = true;
    #elif PLATFORM_PANDORA
        xRes = 800;
        yRes = 480;
        fullScreen = true;
    #elif PLATFORM_GP2X
        xRes = 320;
        yRes = 240;
        fullScreen = true;
    #else // Penjin 2D project
        xRes = 1024;
        yRes = 768;
        fullScreen = false;
    #endif

	gameTimer.setMode(SIXTY_FRAMES);
    input = NULL;
    now = SDL_GetTicks();
}

Engine::Engine(CRstring appName,CRint xRes,CRint yRes,CRbool fullScreen)
{
	this->appName = appName;
	this->xRes = xRes;
	this->yRes = yRes;
	this->fullScreen = fullScreen;
	gameTimer.setMode(SIXTY_FRAMES);
	input = NULL;
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
						fullScreen = true;
						break;
					}
					//	Set xRes
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
    #ifdef PENJIN_GL
        //	Clear Accumulation buffer to avoid garbage pixels
        glClear(GL_ACCUM_BUFFER_BIT);
    #endif
    state = NULL;
	state = new BaseState;

	const SDL_VideoInfo* info = NULL;	//Information about the current video settings
    int flags = 0;						//Flags for SDL_SetVideoMode

    //Initialize SDL's video subsystem.
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		return PENJIN_SDL_VIDEO_INIT_FAILED;
    }

    //Get some video information
    info = SDL_GetVideoInfo();
    if(!info)
	{
		return PENJIN_SDL_VIDEO_QUERY_FAILED;
    }

#ifdef PENJIN_GL
        //Setup OpenGL window attributes
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    #ifdef __linux__
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    #else
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 16);
    #endif
        flags = SDL_OPENGL;
#else
    flags = SDL_SWSURFACE;
#endif
	if(fullScreen)
		flags = flags | SDL_FULLSCREEN;
    screen = NULL;
    screen = SDL_SetVideoMode(xRes, yRes, info->vfmt->BitsPerPixel, flags);
	if(screen  == NULL )
	{
		return PENJIN_SDL_SETVIDEOMODE_FAILED;
    }
#ifdef PENJIN_SDL
    GFX::initVideoSurface(SDL_GetVideoSurface());
#endif

    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	SDL_ShowCursor(SDL_DISABLE);

    //  Can't display window title on a GP2X
    #ifndef PLATFORM_GP2X
        SDL_WM_SetCaption((appName + " V" + AutoVersion::FULLVERSION_STRING + AutoVersion::STATUS_SHORT).c_str(), NULL);
    #endif

	setInitialState(STATE_BASE);
	gameTimer.start();

	#ifdef _DEBUG
        GFX::showVideoInfo();
	#endif

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
        //  Take input
        if(!state->getIsPaused())
            state->userInput();
        else
            state->pauseInput();

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
                state->pauseUpdate();
                state->pauseScreen();
                //	Flush the cache on GP2X just before the screen is flipped
                #ifdef PLATFORM_GP2X
                    hack.flushCache(screen->pixels, (char*)screen->pixels + *xRes * *yRes);
                #endif
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
			state->update();
			if(state->getNeedInit())
                return true;
			//  Render objects
            state->render();
            #ifdef PLATFORM_GP2X
                hack.flushCache(screen->pixels, (char*)screen->pixels + *xRes * *yRes);
            #endif
            GFX::forceBlit();
            #ifdef _DEBUG
                int frameCount = calcFPS();
                if(frameCount>=20)//only update if there are a reasonable number of redundant updates
                {
                    //  This code seems to slow down Linux builds majorly.
                    SDL_WM_SetCaption((appName + " V" + AutoVersion::FULLVERSION_STRING
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
            SDL_Delay(/*timeRemaining((uint)gameTimer.getScaler())*/1);  // Release CPU briefly
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
		state->setStateResolution(&xRes, &yRes);
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


