#include "Timer.h"

#ifdef PENJIN_FIXED
Fixed Timer::calcScaler(const TimerScalers& mode)
#else
float Timer::calcScaler(const TimerScalers& mode)
#endif
{
    #ifdef PENJIN_FIXED
        Fixed divider;
        if (mode == FIFTEEN_FRAMES)
        {
            divider = 15;
            return (Fixed(MY_CLOCKS) / divider);
        }
        else if (mode == THIRTY_FRAMES)
        {
            divider = 30;
            return (Fixed(MY_CLOCKS) / divider);
        }
        else if (mode == FIFTY_FRAMES)
        {
            divider = 50;
            return (Fixed(MY_CLOCKS) / divider);
        }
        else if (mode == SIXTY_FRAMES)
        {
            divider = 60;
            return (Fixed(MY_CLOCKS) / divider);
        }
    #else
        if (mode == FIFTEEN_FRAMES)
            return ((float)MY_CLOCKS / 15.0f);
        else if (mode == THIRTY_FRAMES)
            return ((float)MY_CLOCKS / 30.0f);
        else if (mode == FIFTY_FRAMES)
            return ((float)MY_CLOCKS / 50.0f);
        else if (mode == SIXTY_FRAMES)
            return ((float)MY_CLOCKS / 60.0f);
    #endif
        else if (mode == MILLI_SECONDS)
            return (MY_CLOCKS / 1000);
        else if (mode == CENTI_SECONDS)
            return (MY_CLOCKS / 100);
        else if (mode == DECI_SECONDS)
            return (MY_CLOCKS / 10);
        else if (mode == SECONDS)
            return MY_CLOCKS;
        else if (mode == MINUTES)
            return (MY_CLOCKS * 60);
        else if (mode == HOURS)
            return (MY_CLOCKS * 60 * 60);
        else
            return MY_CLOCKS;
}

