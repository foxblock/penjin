#include "StringUtility.h"

string StringUtility::linToWin(CRstring line)
{
    string out = line;
	uint iMax = (uint)line.size();
	for (uint i = 0; i < iMax; ++i)
	{
		//	check if the current char is a Linux NL
		if (out[i] == 0x0A)
		{
			//	Remove the NL
			out.erase(out.begin()+i);

			//	Add the windows CR
			out.push_back(0x0D);
		}
	}
	return out;
}

string StringUtility::winToLin(CRstring line)
{
    string out = line;
	//	run through the text line
	uint iMax = (uint)line.size();
	for(uint i = 0; i < iMax; ++i)
	{
		//	check if the current char is a win CR
		if(out[i] == 0x0D)
		{
			//	Remove win CR
			out.erase(out.begin()+i);

			//	Add linux NL
			out.push_back(0x0A);
		}
	}
	return out;
}

string StringUtility::doubleToString(CRdouble value)
{
	stringstream ss;
	string str;
	ss << value;
	ss >> str;
	return str;
}

string StringUtility::floatToString(CRfloat value)
{
	stringstream ss;
	string str;
	#ifdef PENJIN_FIXED
        ss << fixedpoint::fix2float(value);
	#else
        ss << value;
	#endif
	ss >> str;
	return str;
}

string StringUtility::FixedToString(CRFixed value){return floatToString(fixedpoint::fix2float<16>(value.intValue));}

string StringUtility::intToString(CRint n)
{
	stringstream ss;
	string str;
	ss << n;
	ss >> str;
	return str;
}

bool StringUtility::isDigit(CRchar digit)
{
	return true;
}

bool StringUtility::isLetter(CRchar l)
{
	if (l >= 65 && l <= 90)
		return true;
	else if (l >= 97 && l <= 122)
		return true;
	return false;
}

string StringUtility::longToString(CRlong value)
{
	stringstream ss;
	string str;
	ss << value;
	ss >> str;
	return str;
}

char StringUtility::lower(CRchar l)
{
	//	if it's lowercase
	char o = l;
	if (isupper(l))
		o = tolower(l);
	return o;
}

string StringUtility::shortToString(CRshort value)
{
	stringstream ss;
	string str;
	ss << value;
	ss >> str;
	return str;
}

double StringUtility::stringToDouble(CRstring value)
{
	istringstream ins;	//	Create a string stream
	ins.str(value);
	double out = 0;
	ins >> out;
	return out;
}

float StringUtility::stringToFloat(CRstring value)
{
	istringstream ins;	//	Create a string stream
	ins.str(value);
	#ifdef PENJIN_FIXED
        FLOAT out = 0;
	#else
        float out = 0;
	#endif
	ins >> out;
	return out;
}

Fixed StringUtility::stringToFixed(CRstring value)
{
	return Fixed(stringToFloat(value));
}

int StringUtility::stringToInt(CRstring value)
{
	istringstream ins;	//	Create a string stream
	ins.str(value);
	int out = 0;
	ins >> out;
	return out;
}

long StringUtility::stringToLong(CRstring value)
{
	istringstream ins;	//	Create a string stream
	ins.str(value);
	long out = 0;
	ins >> out;
	return out;
}

short StringUtility::stringToShort(CRstring value)
{
	istringstream ins;	//	Create a string stream
	ins.str(value);
	short out = 0;
	ins >> out;
	return out;
}

double StringUtility::cStringToDouble(char* value){return stringToDouble((string)value);}
float StringUtility::cStringToFloat(char* value){return stringToFloat((string)value);}
Fixed StringUtility::cStringToFixed(char* value){return stringToFixed((string)value);}
int StringUtility::cStringToInt(char* value){return stringToInt((string)value);}
long StringUtility::cStringToLong(char* value){return stringToLong((string)value);}
short StringUtility::cStringToShort(char* value){return stringToShort((string)value);}

char StringUtility::upper(CRchar l)
{
    char o = l;
	//	if it's lowercase
	if (islower(l))
		o = toupper(l);
	return o;
}

int StringUtility::charToInt(CRchar n)
{
    char o = n;
	if(n >= 48 && n <= 57)
		o-=48;

	return o;
}

char StringUtility::intToChar(CRint n)
{
    char o = n;
	if(n >= 0 && n <= 57-48)
			o+=48;
	return o;
}

string StringUtility::upper(string word)
{
    for(int i = word.size()-1; i >= 0; --i)
        word[i] = upper((char)word[i]);
    return word;
}

string StringUtility::lower(string word)
{
    for(int i = word.size()-1; i >= 0; --i)
        word[i] = lower((char)word[i]);
    return word;
}
string StringUtility::leadingZero(CRint value){return (value<10?"0":"") + StringUtility::intToString(value);}

void StringUtility::reverse(char* s)
{
  size_t begin = 0;
  size_t end = string(s).size() - 1;

  while (begin < end)
    swap(s[begin++], s[end--]);
}

