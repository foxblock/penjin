/*
	Pirate Games 2008 (and beyond...)
	The source is free for modification.
	Any changes should be emailed back to the Pirate Games team
		(team@pirate-games.co.uk)
*/
#ifndef WIIJOY_H
#define WIIJOY_H

#ifdef PLATFORM_WII
    #include <wiiuse/wpad.h>
#else
    #include <SDL/SDL.h> // used for testing PC versions of code
#endif
class WiiJoy
{
    public:
        WiiJoy();
        ~WiiJoy();
        void init()
        {
            #ifdef PLATFORM_WII
                WPAD_Init();
            #endif
        }
        void deInit()
        {
            #ifdef PLATFORM_WII
                WPAD_Shutdown();
            #endif
        }

        void update();					//	Get current status of input
        #ifdef PLATFORM_PC
            void keyDown(const SDLKey& key);
            void keyUp(const SDLKey& key);
        #endif

        /// Wiimote
        //  0 - not pressed
        //  1 - pressed
        //  2 - held
        int isUp(){return Up;}
        int isDown(){return Down;}
        int isLeft(){return Left;}
        int isRight(){return Right;}
        int isA(){return A;}
        int isB(){return B;}
        int isOne(){return One;}
        int isTwo(){return Two;}
        int isPlus(){return Plus;}
        int isMinus(){return Minus;}
        int isStart(){return Plus;}
        int isSelect(){return Minus;}
        int isHome(){return Home;}

        void resetKeys();

    protected:
    private:
        #ifdef PLATFORM_WII
            void checkPressed();
            void checkHeld();
        #endif
        int Up, Down, Left, Right, A, B, One, Two, Plus, Minus, Home;
};

#endif // WIIJOY_H
