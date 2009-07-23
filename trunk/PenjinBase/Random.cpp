#include "Random.h"

namespace Random
{
    int min = 0;
    int max = 1;
    int seed = randSeed();
}

int Random::randSeed()	//	seed the random number generator
{
    int seed = static_cast<int>(time(0));
    srand(seed);
    return seed;
}

int Random::getSeed()
{
    return seed;
}

bool Random::nextBool()
{
    if(rand()%2 == 0)
        return true;
    return false;
}

Fixed Random::nextFixed()
{
    int range = max-min;
    return (min + Fixed(range * rand() /(RAND_MAX + 1.0f)));
}
float Random::nextFloat()
{
	float range = max - min;
	return (min + float(range * rand() / (RAND_MAX + 1.0f )));
}

double Random::nextDouble()
{
	double range = max - min;
	return (min + double(range * rand() / (RAND_MAX + 1.0)));
}

int Random::nextInt(){return (min + rand() % (max - min +1));}

float Random::nextFloat(CRint min, CRint max)
{
	float range = max - min;
	return (min + float(range * rand() / (RAND_MAX + 1.0f )));
}

Fixed Random::nextFixed(CRint min, CRint max)
{
    int range = max-min;
    return (min + Fixed(range * rand() /(RAND_MAX + 1.0f)));
}

double Random::nextDouble(CRint min, CRint max)
{
	double range = max - min;
	return (min + double(range * rand() / (RAND_MAX + 1.0)));
}

int Random::nextInt(CRint min, CRint max){return (min + rand() % (max - min +1));}

void Random::setSeed(CRint s){srand(s);seed=s;}
void Random::setLimits(CRint min,CRint max){setMin(min);setMax(max);}
void Random::setMax(CRint m){max = m;}
void Random::setMin(CRint m){min = m;}

/// random class
RandomClass::RandomClass(CRint min, CRint max){this->min = min;this->max = max;}
void RandomClass::setMax(CRint max){this->max = max;}
void RandomClass::setMin(CRint min){this->min = min;}
void RandomClass::setLimits(CRint min,CRint max){this->min = min;this->max = max;}

int RandomClass::nextInt(){return Random::nextInt(min,max);}		//	get the next random int
float RandomClass::nextFloat(){return Random::nextFloat(min,max);}	//	get the next float
double RandomClass::nextDouble(){return Random::nextDouble(min,max);}//	get the next double
Fixed RandomClass::nextFixed(){return Random::nextFixed(min,max);}
