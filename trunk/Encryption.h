#ifndef ENCRYPTION_H
#define ENCRYPTION_H
/*
PROJECT:	Simple encryption class
BY:			Kevin Winfield-Pantoja (PokeParadox)
DATE:		Started on 01-07-06
ABOUT:		The encryption algorithm is mainly intended for encrypting game data, such as highscore tables.
			Anyone serious enough could crack it, even without this source.
*/

#include <string>
using namespace std;
#include "Random.h"
#include "NumberUtility.h"

class Encryption
{
    public:
        Encryption();
        ~Encryption();

        //	NOTE: The encryption key(seed value) is stored as the last char of the encrypted string.
        //		  It is stripped from the string on decryption.

        string encryptBuffer(CRstring buff);	//	Takes a string of data and returns an encrypted string.
        string decryptBuffer(string buff);	//	Takes an encrypted string of data and returns a decrypted string.

    private:
        int wrapValue(int val,CRint limit){return (NumberUtility::wrapValue(val,limit));}	//	Brings value with a certain range.
        char key;		//This is the random number seed value
        RandomClass rand;
};

#endif	//	ENCRYPTION_H
