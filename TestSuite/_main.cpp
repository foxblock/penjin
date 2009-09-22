#include "MyGame.h"

int main(int argc, char** argv)
{
    Engine* game = NULL;
	ErrorHandler error;

	//	Setup game engine
	game = new MyGame("Penjin - TestSuite", 800, 480, false);

	cout << error.getErrorString(game->argHandler(argc,argv));
	cout << error.getErrorString(game->init());

	while(game->stateLoop());	//	Perform main loop until shutdown
	cout << error.getErrorString(PENJIN_SHUTDOWN);

	//	Tidy up
    if(game)
    {
        delete game;
        game = NULL;
    }
    cout << error.getErrorString(PENJIN_GOODBYE);
    SDL_Quit();		//	Shut down SDL tidyly
	return 0;	//	Normal program termination.
}
