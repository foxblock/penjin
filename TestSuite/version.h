#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "09";
	static const char MONTH[] = "12";
	static const char YEAR[] = "2009";
	static const double UBUNTU_VERSION_STYLE = 9.12;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 429;
	static const long REVISION = 2301;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 788;
	#define RC_FILEVERSION 0,1,429,2301
	#define RC_FILEVERSION_STRING "0, 1, 429, 2301\0"
	static const char FULLVERSION_STRING[] = "0.1.429.2301";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 29;
	

}
#endif //VERSION_h
