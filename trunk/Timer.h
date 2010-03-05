#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#ifndef PENJIN_SYS_TIMER
    #include <SDL/SDL.h>
#else
    #include <ctime>
#endif


#include "PenjinTypes.h"

enum TimerScalers
{
    //	Various modes that the timer can be put in.
    MILLI_SECONDS=1000,
    CENTI_SECONDS=100,
    SIXTY_FRAMES=60,
    FIFTY_FRAMES=50,
    THIRTY_FRAMES=30,
    FIFTEEN_FRAMES=15,
    DECI_SECONDS=10,
    SECONDS=1,
    MINUTES,
    HOURS,
    CUSTOM
};

#ifndef PENJIN_SYS_TIMER
    const static int MY_CLOCKS = 1000 ;
#else
    const static int MY_CLOCKS = CLOCKS_PER_SEC;
#endif
class Timer
{
    public:
        Timer()
        {
            startTicks = 0;
            pausedTicks = 0;
            is_Paused = false;
            is_Started = false;
            mode = MILLI_SECONDS;   // default value
            #ifdef PENJIN_FIXED
                scaler = 1;
            #else
                scaler = 1.0f;
            #endif
        }
        Timer(const TimerScalers& scale)
        {
            startTicks = 0;
            pausedTicks = 0;
            is_Paused = false;
            is_Started = false;
            mode = scale;
            calcScaler();
        }

        void setMode(const TimerScalers& mode)       // Set the timer scaler
        {
            this->mode = mode;
            calcScaler();
        }
        TimerScalers getMode()const{return mode;}

        int getScaledTicks(const TimerScalers& mode)
        {
            setMode(mode);
            return getScaledTicks();
        }
        int getScaledTicks() const              // Return the scaled elapsed time
        {
            #ifdef PENJIN_FIXED
                return Fixed(getTicks()/scaler).intValue>>16;
            #else
                return (int)((float)getTicks() / scaler);
            #endif
        }
        int getTicks() const
        {
            //If the timer is running
            if(is_Started)
            {
                //If the timer is paused
                if(is_Paused)
                {
                    //Return the number of ticks when the the timer was paused
                    return pausedTicks;
                }
                else
                {
                    //Return the current time minus the start time
                    #ifndef PENJIN_SYS_TIMER
                        return SDL_GetTicks() - startTicks;
                    #else
                        return clock() - startTicks;
                    #endif
                }
            }
            //If the timer isn't running
            return 0;
        }

        void start()
        {
            //Start the timer
            is_Started = true;
            //Unpause the timer
            is_Paused = false;
            //Get the current clock time
            #ifndef PENJIN_SYS_TIMER
                startTicks = SDL_GetTicks();
            #else
                startTicks = clock();
            #endif
        }
        void stop()
        {
            is_Started = false;
            is_Paused = false;
        }
        void pause()
        {
            //If the timer is running and isn't already paused
            if(  is_Started && !is_Paused )
            {
                //Pause the timer
                is_Paused = true;
                //Calculate the paused ticks
                #ifndef PENJIN_SYS_TIMER
                    pausedTicks = SDL_GetTicks() - startTicks;
                #else
                    pausedTicks = clock() -startTicks;
                #endif
            }
        }
        void unpause()
        {
            //If the timer is paused
            if( is_Paused == true )
            {
                //Unpause the timer
                is_Paused = false;
                //Reset the starting ticks
                #ifndef PENJIN_SYS_TIMER
                    startTicks = SDL_GetTicks() - pausedTicks;
                #else
                    startTicks = clock() - pausedTicks;
                #endif
                //Reset the paused ticks
                pausedTicks = 0;
            }
        }

        bool isPaused()const{return is_Paused;};
        bool isStarted()const{return is_Started;};

        /// Set a custom timer resolution.
        #ifdef PENJIN_FIXED
            void setScaler(CRFixed scale){setMode(CUSTOM);scaler =scale;}
            Fixed getScaler(){return scaler;}
        #else
            void setScaler(CRfloat scale){setMode(CUSTOM);scaler =scale;}
            float getScaler()const{return scaler;}
        #endif
    protected:
        void calcScaler();   // Calculate the resolution of timer updates

        TimerScalers mode;
        int startTicks;
        int pausedTicks;
        bool is_Paused;
        bool is_Started;
        #ifdef PENJIN_FIXED
            Fixed scaler;
        #else
            float scaler;
        #endif
};
#endif // TIMER_H_INCLUDED