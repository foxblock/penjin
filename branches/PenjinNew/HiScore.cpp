/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "HiScore.h"
#include "StringUtility.h"
using namespace StringUtility;

HiScore::HiScore()
{
	mode = HIGH_TO_LOW;
	numScores = 10;
	numInitials = 3;
	lastNameIndex = 0;
	nameTable = NULL;
	scoreTable = NULL;
	nameTable = new string[numScores];
	scoreTable = new uint[numScores];
	tableTitle = "Hi Scores";
	initialiseTables();
	text.setRelativity(true);
	//text.setCentreText(true);
	#ifndef PENJIN_3D
        startPos = Vector2di(120,5);
    #else
        startPos = Vector3df(120.0f,5.0f,0.0f);
    #endif
}

HiScore::HiScore(CRuint numScores,CRuint numInitials)
{
	mode = HIGH_TO_LOW;
	this->numScores = numScores;
	this->numInitials = numInitials;
    lastNameIndex = 0;
	nameTable = NULL;
	scoreTable = NULL;
	nameTable = new string[numScores];
	scoreTable = new uint[numScores];
	tableTitle = "Hi Scores";
	initialiseTables();
	text.setRelativity(true);
    #ifndef PENJIN_3D
        startPos = Vector2di(120,5);
    #else
        startPos = Vector3df(120.0f,5.0f,0.0f);
    #endif
}

HiScore::~HiScore()
{
	clear();
}

void HiScore::clear()
{
	if(nameTable)
		delete [] nameTable;
	if(scoreTable)
        delete [] scoreTable;
    nameTable = NULL;
    scoreTable = NULL;
}

void HiScore::initialiseTables()
{
	for (uint i = 0; i < numScores; ++i)
	{
		nameTable[i] = "AAA";
		scoreTable[i] = 0;
	}
}

PENJIN_ERRORS HiScore::loadScores(CRstring fileName)
{
	doc.clear();
	doc.load(fileName);
	if(!doc.size())
		return PENJIN_FILE_NOT_FOUND;

	for (uint i = 0; i < numScores; ++i)
		nameTable[i] = crypt.decryptBuffer(doc.getLine(i));
	for (uint i = numScores; i < numScores*2; ++i)
		scoreTable[i-10] = stringToInt(crypt.decryptBuffer(doc.getLine(i)));
    //  now get the index of the last enterred name
    if(doc.size() >numScores*2)
        lastNameIndex = stringToInt(crypt.decryptBuffer(doc.getLine(numScores*2)));
	return PENJIN_OK;
}

PENJIN_ERRORS HiScore::loadScoresBinary(CRstring fileName)
{
	return PENJIN_FILE_NOT_FOUND;
}

void HiScore::nameEntry(string name, uint score)
{
	// get a score, then compare with the other scores
	for (uint i = 0; i < numScores; ++i)
	{
		for(uint x = 0; x < numScores; ++x)
		{
			if(mode == HIGH_TO_LOW)
			{
				//	Check which score is the highest in value
				if(score > scoreTable[x])
				{
					//	If the score is bigger then swap the bigger score into the temp value
					uint temp = scoreTable[x];
					string sTemp = nameTable[x];

					scoreTable[x] = score;
					nameTable[x] = name;

					score = temp;
					name = sTemp;
					lastNameIndex = x;
				}
			}
			else
			{
				//	Check which score is the lowest or equal in value
				if(score <= scoreTable[x] || scoreTable[x] == 0)
				{
					//	If the score is lower then swap the lower score into the temp value
					uint temp = scoreTable[x];
					string sTemp = nameTable[x];

					scoreTable[x] = score;
					nameTable[x] = name;

					score = temp;
					name = sTemp;
					lastNameIndex = x;
				}
			}
		}
	}
}

#ifdef PENJIN_SDL
void HiScore::render(SDL_Surface* screen)
{
    text.setPosition(centrePos.x,startPos.y);
    text.print(screen,tableTitle + (string)" \n \n");
    for (uint i = 0; i < numScores; ++i)
    {
        text.setPosition(startPos.x, text.getPosition().y);
        text.print(screen,(int)i+1);
        text.setPosition(centrePos.x, text.getPosition().y);
        text.print(screen,nameTable[i]);
        text.setPosition(endPos.x, text.getPosition().y);
        text.print(screen,(int)scoreTable[i]);text.print(screen,(string)" \n");	//	GP2X Spacing fix... hopefully
    }
}
#else
    void HiScore::render()
    {
        text.setPosition(centrePos.x,startPos.y);
        text.print(tableTitle + (string)" \n \n");
        for (uint i = 0; i < numScores; ++i)
        {
            text.setPosition(startPos.x, text.getPosition().y);
            text.print((int)i+1);
            text.setPosition(centrePos.x, text.getPosition().y);
            text.print(nameTable[i]);
            text.setPosition(endPos.x, text.getPosition().y);
            text.print((int)scoreTable[i]);text.print((string)" \n");	//	GP2X Spacing fix... hopefully
        }
    }
#endif
PENJIN_ERRORS HiScore::saveScores(CRstring fileName)
{
	doc.clear();
	for (uint i = 0; i < numScores; ++i)
		doc.append(crypt.encryptBuffer(nameTable[i]));
	for (uint i = 0; i < numScores; ++i)
		doc.append(crypt.encryptBuffer(intToString(scoreTable[i])));
    doc.append(crypt.encryptBuffer(intToString(lastNameIndex)));
	doc.save(fileName);
	return PENJIN_OK;
}

PENJIN_ERRORS HiScore::saveScoresBinary(CRstring fileName)
{
	return PENJIN_FILE_NOT_FOUND;
}

void HiScore::setMode(CRuint mode)
{
	this->mode = mode;
}

void HiScore::setBoundaries(const SDL_Rect& b)
{
    text.setBoundaries(b);
    startPos.x = b.x + (0.1f * b.w);
    startPos.y = b.y + (0.1f * b.h);
    endPos.x = b.x + (0.7f * b.w);
    endPos.y = b.y + (0.7f * b.h);
    centrePos = endPos - startPos;
    centrePos *=0.5f;
}
