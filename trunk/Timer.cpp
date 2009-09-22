#include "Timer.h"

void Timer::calcScaler()
{
    #ifdef PENJIN_FIXED
        Fixed divider;
        scaler = 0;
        if (mode == FIFTEEN_FRAMES)
        {
            divider = 15;
            scaler = Fixed(MY_CLOCKS) / divider;
        }
        else if (mode == THIRTY_FRAMES)
        {
            divider = 30;
            scaler = Fixed(MY_CLOCKS) / divider;
        }
        else if (mode == FIFTY_FRAMES)
        {
            divider = 50;
            scaler = Fixed(MY_CLOCKS) / divider;
        }
        else if (mode == SIXTY_FRAMES)
        {
            divider = 60;
            scaler = Fixed(MY_CLOCKS) / divider;
        }
    #else
        scaler = 0;
        if (mode == FIFTEEN_FRAMES)
            scaler = (float)MY_CLOCKS / 15.0f;
        else if (mode == THIRTY_FRAMES)
            scaler = (float)MY_CLOCKS / 30.0f;
        else if (mode == FIFTY_FRAMES)
            scaler = (float)MY_CLOCKS / 50.0f;
        else if (mode == SIXTY_FRAMES)
            scaler = (float)MY_CLOCKS / 60.0f;
    #endif
        else if (mode == NANO_SECONDS)
            scaler = MY_CLOCKS / 1000000000;
        else if (mode == MICRO_SECONDS)
            scaler = MY_CLOCKS / 1000000;
        else if (mode == MILLI_SECONDS)
            scaler = MY_CLOCKS / 1000;
        else if (mode == CENTI_SECONDS)
            scaler = MY_CLOCKS / 100;
        else if (mode == DECI_SECONDS)
            scaler = MY_CLOCKS / 10;
        else if (mode == SECONDS)
            scaler = MY_CLOCKS;
        else if (mode == MINUTES)
            scaler = MY_CLOCKS * 60;
        else if (mode == HOURS)
            scaler = MY_CLOCKS * 60 * 60;
        else
            scaler = MY_CLOCKS;
}

