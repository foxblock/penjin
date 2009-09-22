#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "03";
	static const char MONTH[] = "09";
	static const char YEAR[] = "2009";
	static const double UBUNTU_VERSION_STYLE = 9.09;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 0;
	static const long BUILD = 57;
	static const long REVISION = 306;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 83;
	#define RC_FILEVERSION 0,0,57,306
	#define RC_FILEVERSION_STRING "0, 0, 57, 306\0"
	static const char FULLVERSION_STRING[] = "0.0.57.306";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 57;
	

}
#endif //VERSION_h
