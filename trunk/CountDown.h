#ifndef COUNTDOWN_H_INCLUDED
#define COUNTDOWN_H_INCLUDED

#include "Timer.h"

enum RewindModes
{
    STOP_AND_REWIND,
    REWIND,
    STOP,
    DONT_REWIND
};

class CountDown : public Timer
{
    public:
        CountDown();
        void init(const int& newLimit, const TimerScalers& newMode, void* object=NULL, void (*newCallback)(void*)=NULL);

        int getLimit(){return limit;}
        int getTimeLeft(){return limit - getScaledTicks();}
        RewindModes getRewind(){return rewind;}
        bool hasFinished(){return getTimeLeft() <= 0;}
        void setCallback(void* object, void (*newCallback)(void*)){obj = object; callback = newCallback;}
        void setLimit(const int& newLimit){limit = newLimit;}
        void setRewind(const RewindModes& rew){rewind = rew;}

        void start(){Timer::start();}
        void start(int newLimit){limit = newLimit; start();}
        void update();
    private:
        void (*callback)(void*);
        void* obj;
        int limit;
        RewindModes rewind;
};

#endif // COUNTDOWN_H_INCLUDED
