#ifndef RANDOM_H
#define RANDOM_H

/*
Pirate Games
Random number class
by Kevin Winfield-Pantoja
*/


#include <ctime>
#include <cstdlib>
#include "PenjinTypes.h"

namespace Random
{
    void setMax(CRint max);
    void setMin(CRint min);
    void setLimits(CRint min,CRint max);

    int nextInt();		//	get the next random int
    float nextFloat();	//	get the next float
    double nextDouble();//	get the next double
    Fixed nextFixed();
    bool nextBool();	//	random deterministic choice

    /// quick random numbers without setting limits
    float nextFloat(CRint min, CRint max);
    Fixed nextFixed(CRint min, CRint max);
    int nextInt(CRint min, CRint max);
    double nextDouble(CRint min, CRint max);

    void setSeed(CRint seed);
    int getSeed();
    int randSeed();			//	Also returns the seed value
}

class RandomClass
{
    public:
        RandomClass(){;}
        RandomClass(CRint min, CRint max);

        void setSeed(CRint s){seed = s;Random::setSeed(s);}
        int getSeed() const {return seed;}

        void setMax(CRint max);
        void setMin(CRint min);
        void setLimits(CRint min,CRint max);

        int nextInt();		//	get the next random int
        float nextFloat();	//	get the next float
        double nextDouble();//	get the next double
        Fixed nextFixed();

    private:
        int seed;
        int min;
        int max;
};
#endif	// RANDOM_H

