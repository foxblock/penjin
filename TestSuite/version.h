#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "14";
	static const char MONTH[] = "10";
	static const char YEAR[] = "2010";
	static const char UBUNTU_VERSION_STYLE[] = "10.10";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 2;
	static const long BUILD = 1131;
	static const long REVISION = 6336;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1923;
	#define RC_FILEVERSION 0,2,1131,6336
	#define RC_FILEVERSION_STRING "0, 2, 1131, 6336\0"
	static const char FULLVERSION_STRING[] = "0.2.1131.6336";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 331;
	

}
#endif //VERSION_H
