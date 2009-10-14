#include "CountDown.h"

CountDown::CountDown() : Timer()
{
    limit = 1000;
    callback = NULL;
    obj = NULL;
    rewind = STOP_AND_REWIND;
}

void CountDown::init(const int& newLimit, const TimerScalers& newMode, void* object, void (*newCallback)(void*))
{
    limit = newLimit;
    setMode(newMode);
    callback = newCallback;
    obj = object;
    if (!callback)
        rewind = STOP;
    is_Started = false;
    is_Paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void CountDown::update()
{
    if (limit - getScaledTicks() <= 0 && is_Started)
    {
        if (callback)
            (*callback)(obj);
        if (rewind == STOP_AND_REWIND)
        {
            stop();
        }
        else if (rewind == REWIND)
        {
            start();
        }
        else if (rewind == STOP)
        {
            pause();
        }
    }
}

/**--------------------------------

How to implement:
- Create a static member function of a class with the following implementation
void CLASS::FUNCTIONNAME(void* object)
{
    CLASS* self = (CLASS*) object;
    // do stuff here use self-> to access class datamembers and functions
}

- This usually acts as a wrapper function, you can do stuff in there or make it private and
    redirect the function call to another (public) function

- initialize the countdown like this:
    ctr.init(2000,MILLI_SECONDS,(void*) this, &CLASS::FUNCTIONNAME); // 2000 milliseconds countdown

- The counter has to be updated in order for the callback to take place, so the update() function has
    to be called on a regular basis (in a state update function for example)

--------------------------------**/
