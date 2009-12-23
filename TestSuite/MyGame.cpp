#include "MyGame.h"

MyGame::MyGame()
{
	//	Default constructor
	Penjin::setApplicationName("TestSuite");
#if defined (PLATFORM_PANDORA) || defined(PLATFORM_GP2X)
	GFX::setFullscreen(true);
#else
    GFX::setFullscreen(false);
#endif
}


PENJIN_ERRORS MyGame::init()
{
    setInitialState(STATE_TITLE);
    #ifdef PLATFORM_PC
        GFX::setResolution(800,600);
    #else
        GFX::setResolution();
    #endif
    return GFX::resetScreen();
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

/*
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
*/
