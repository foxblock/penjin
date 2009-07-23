#ifndef PENJINSTATES_H_INCLUDED
#define PENJINSTATES_H_INCLUDED

//  Modify this file to tailor the states needed by this game
//  NOTE: Please do not remove the STATE_NULL unless you have good reason to!
//  STATE_TITLE is considered to be the default state it is advised to leave this also
//  #include all state files which correspond to these modes

//	GLOBAL DEFINED FOR ALL STATES

#include "BaseState.h"

#ifdef MEMWATCH
    #include "Memwatch.h"      // In debug mode will check for mem alloc errors etc.
#endif

//STATE_NULL     // 0 Exit the program, this is declared in the basestate
//STATE_BASE     // 1

#include "userStates.h"

#endif // PENJINSTATES_H_INCLUDED
