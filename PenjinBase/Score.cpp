#include "Score.h"

Score::Score()
{
	score = 0;
	lastScore = 0;
	multiplier = 1;
}

int Score::getDifference()const
{
	return score-lastScore;
}

int Score::getMultiplier()const
{
	return multiplier;
}

int Score::getScore()const
{
	return score;
}

void Score::increaseMultiplier()
{
	++multiplier;
}

void Score::changeScore(CRint points)
{
	score += (points * multiplier);
}

void Score::resetScore()
{
	score = 0;
}

void Score::setMultiplier(CRint mult)
{
	multiplier = mult;
}

void Score::storeScore()
{
	lastScore = score;
}

