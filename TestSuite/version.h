#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "28";
	static const char MONTH[] = "10";
	static const char YEAR[] = "2009";
	static const double UBUNTU_VERSION_STYLE = 9.10;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 0;
	static const long BUILD = 62;
	static const long REVISION = 332;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 91;
	#define RC_FILEVERSION 0,0,62,332
	#define RC_FILEVERSION_STRING "0, 0, 62, 332\0"
	static const char FULLVERSION_STRING[] = "0.0.62.332";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 62;
	

}
#endif //VERSION_h