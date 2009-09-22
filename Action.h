#ifndef ACTION_HEADER
#define ACTION_HEADER

#include "actions.h"

#ifdef __linux__
    #include <SDL.h>
#else
    #include <SDL/SDL.h>
#endif

class Action
{
	public:
		Action()
		{
			action = ACTION_NONE;
			key = NULL;
			wiiBitMask = NULL;
			wiimoteMode = false;
		}
		~Action()
		{
			clear();
		}

		int getAction(){return action;}						//	Get the actual ingame action
		SDL_Event getEvent(){if(key) return *key;}			//	Get an SDL keyboard, joystick or mouse event
		int getWiivent(){if(wiiBitMask) return *wiiBitMask;}	//	Get events related to wiimote events

		void setAction(int action){this->action = action;}	//	Set the ingame action
		void setEvent(SDL_Event key)						//	Set the event to map the action to
		{
			if(!this->key)
			{
				this->key = new SDL_Event;
			}
			*this->key = key;
			wiimoteMode = false;
		}
		void setWiivent(int event)							// Set the  Wii Event to map the action to
		{
			if(!wiiBitMask)
			{
				wiiBitMask = new int;
			}
			*wiiBitMask = event;
			wiimoteMode = true;
		}

		bool isWiimoteAction(){return wiimoteMode;}

		void clear()
		{
			if(key)
				delete key;
			if(wiiBitMask)
				delete wiiBitMask;
		}
	private:
		int action;			//	Stores the mapped action
		SDL_Event* key;			//	Store a key assignment (joy,mouse or keyboard)
		int* wiiBitMask;		//	Stores the bitmask relating to the wiimote states and presses
		bool wiimoteMode;		//	Is the action using a wiimote event rather than an SDL_Event
};
#endif //	ACTION_HEADER
