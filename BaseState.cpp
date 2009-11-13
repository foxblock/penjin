#include "BaseState.h"

BaseState::BaseState()
{
    isPaused = false;
    firstPaused = false;
    nullify = false;
    needInit = true;
    nextState = 0;
    #ifdef PENJIN_SDL
        screen = SDL_GetVideoSurface();
    #endif
}

BaseState::~BaseState()
{
    /// Tidy up
}

void BaseState::pauseUpdate()
{

}

#ifdef PENJIN_SDL
    void BaseState::pauseScreen(SDL_Surface* screen)
    {
        pauseSymbol(screen);
    }
    void BaseState::pauseSymbol(SDL_Surface* screen)
    {
        SDL_Rect pauseSymbol;
        pauseSymbol.x = pauseSymbol.y = 50;
        pauseSymbol.w = 50;
        pauseSymbol.h = 100;
        SDL_FillRect(screen, &pauseSymbol,SDL_MapRGB(screen->format, 96,96,96));

        pauseSymbol.x +=1;
        pauseSymbol.y +=1;
        pauseSymbol.h -=2;
        pauseSymbol.w -=2;
        SDL_FillRect(screen, &pauseSymbol,SDL_MapRGB(screen->format, 240,240,240));

        pauseSymbol.x +=88;
        pauseSymbol.y -=2;
        pauseSymbol.w +=2;
        pauseSymbol.h +=2;
        SDL_FillRect(screen, &pauseSymbol,SDL_MapRGB(screen->format, 96,96,96));

        pauseSymbol.x +=1;
        pauseSymbol.y +=1;
        pauseSymbol.h -=2;
        pauseSymbol.w -=2;
        SDL_FillRect(screen, &pauseSymbol,SDL_MapRGB(screen->format, 240,240,240));
    }
    void BaseState::render(SDL_Surface* screen)
    {
        // Clear screen
        GFX::clearScreen(screen);

        // Drawing commands here
        // update to screen performed automatically
    }
#else
    void BaseState::pauseScreen()
    {

    }
    void BaseState::pauseSymbol()
    {
    }
    void BaseState::render()
    {
        //	Clear Screen
        GFX::clearScreen();

/*
        //	Draw objects
        glBegin(GL_POLYGON);
            glVertex2f(xStart,yStart);
            glVertex2f(xStart,yStart+100.0f);
            glVertex2f(xStart+100.0f,yStart+100.0f);
            glVertex2f(xStart+100.0f,yStart);
        glEnd();
*/
        //	update to screen is performed automaticaly
    }
#endif
/*   */
void BaseState::update()
{
    // Perform physics ops here
}

void BaseState::unlimitedUpdate()
{

}

void BaseState::init()
{
    #ifdef PENJIN_GL
        #ifdef PENJIN3D
            GFX::init3DRendering(*xRes,*yRes);
        #else
            GFX::init2DRendering(*xRes,*yRes);
        #endif

	#else
        // Do any setup here
	#endif
}

void BaseState::userInput()
{
    // Perform input handling here - This template should be suitable for most needs.
    /// Only override if you need to do some strange stuff! :)
    //	run through all events
    while(SDL_PollEvent(&event))
	{
        switch(event.type)
		{
		case SDL_KEYDOWN:
			keyDown(event.key.keysym.sym);
		break;
		case SDL_KEYUP:
			keyUp(event.key.keysym.sym);
		break;
		case SDL_JOYAXISMOTION:
			joyMotion(event.jaxis.axis, event.jaxis.value);
		break;
		case SDL_JOYBUTTONDOWN:
			joyButtonDown(event.jbutton.button);
		break;
		case SDL_JOYBUTTONUP:
			joyButtonUp(event.jbutton.button);
		break;
		case SDL_MOUSEBUTTONDOWN:
			mouseButtonDown(event.button.x, event.button.y);
		break;
		case SDL_MOUSEBUTTONUP:
            mouseButtonUp(event.button.x, event.button.y);
		case SDL_MOUSEMOTION:
            mouseMotion(event.motion.xrel, event.motion.yrel);
        break;
        case SDL_QUIT:
			nullifyState();
        break;
        }
	}
}

void BaseState::pauseInput()
{
    userInput();
}

void BaseState::joyButtonDown(const Uint8& button)
{
}

void BaseState::joyButtonUp(const Uint8& button)
{
}

void BaseState::joyMotion(const Uint8& axis, const Sint16& value)
{

}

void BaseState::keyDown(const SDLKey& key)
{
    switch(key)
    {
        case SDLK_ESCAPE: nullifyState(); break;
        case SDLK_PAUSE: isPaused = !isPaused;  break;
    }
}

void BaseState::keyUp(const SDLKey&  key)
{
}

void BaseState::mouseButtonDown(const Uint16& x,const Uint16& y)
{

}

void BaseState::mouseButtonUp(const Uint16& x,const Uint16& y)
{
}

void BaseState::mouseMotion(const Uint16& x, const Uint16& y)
{
}
