#include "MyGame.h"

MyGame::MyGame()
{
	//	Default constructor
	appName = "Penjin - TestSuite";
	xRes = 800;
	yRes = 480;
#ifdef PLATFORM_PANDORA
	fullScreen = true;
#else
    fullScreen = false;
#endif
	gameTimer.setMode(SIXTY_FRAMES);
	Random::randSeed();
	input = NULL;
	customControlMap = "NULL";
}

MyGame::MyGame(CRstring appName, CRint xRes, CRint yRes, CRbool fullScreen)
{
	this->appName = appName;
	this->xRes = xRes;
	this->yRes = yRes;
	this->fullScreen = fullScreen;
	gameTimer.setMode(SIXTY_FRAMES);
	Random::randSeed();
	input = NULL;
	customControlMap = "NULL";
}

MyGame::~MyGame()
{
    TTF_Quit();
	//Mix_CloseAudio();							// sutdown SDL_mixer
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
	#ifdef PLATFORM_GP2X
		MMUHack hack;
		hack.closeHack();
		if(loadMenu)	//	Quit to GP2X menu if required to do so by commandline.
		{
			chdir("/usr/gp2x");
			execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
		}
	#endif
}

PENJIN_ERRORS MyGame::init()
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
    if( SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0 )
		return PENJIN_SDL_SOMETHING_FAILED;

    //Get some video information
    info = SDL_GetVideoInfo();
    if(!info)
		return PENJIN_SDL_VIDEO_QUERY_FAILED;

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
    if(!screen)
        return PENJIN_SDL_SETVIDEOMODE_FAILED;
#ifdef PENJIN_SDL
    GFX::initVideoSurface(SDL_GetVideoSurface());
#endif
	//SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	SDL_ShowCursor(SDL_DISABLE);

    //  Can't display window title on a GP2X
    #ifndef PLATFORM_GP2X
        SDL_WM_SetCaption(appName.c_str(), 0);
    #endif

	SDL_JoystickEventState(SDL_ENABLE);

	TTF_Init();
	//Sound().init();
	setInitialState(STATE_TITLE);
	gameTimer.start();

    input = NULL;
    input = new SimpleJoy();
    if(customControlMap != "NULL")
        input->loadControlMap(customControlMap);
	#ifdef _DEBUG
        GFX::showVideoInfo();
	#endif

	#ifdef PENJIN_GL
        #ifdef PENJIN3D
            GFX::init3DRendering(xRes,yRes);
        #else
            GFX::init2DRendering(xRes,yRes);
        #endif
	#endif
	Text().initialise();
	return PENJIN_OK;
}

void MyGame::stateManagement()
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
    else if(next == STATE_ANIMATION)
        state = new StateAnimation;
    else if(next == STATE_PRIMITIVE)
        state = new StatePrimitive;
    else if(next == STATE_RAYCAST)
        state = new StateRaycast;
    else if(next == STATE_COLOUR)
        state = new StateColour;
    else if(next == STATE_TITLE)
		state = new StateTitle;
	/* EXAMPLE OF STATE CHECKING
	else if(next == STATE_TITLE)
		state = new StateTitle;*/
    else
    {
        cout << ErrorHandler().getErrorString(PENJIN_UNDEFINED_STATE);
        exit(PENJIN_UNDEFINED_STATE);
    }
}

PENJIN_ERRORS MyGame::argHandler(int argc, char **argv)
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
