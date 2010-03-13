#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "13";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2010";
	static const double UBUNTU_VERSION_STYLE = 10.03;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 2;
	static const long BUILD = 852;
	static const long REVISION = 4769;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1456;
	#define RC_FILEVERSION 0,2,852,4769
	#define RC_FILEVERSION_STRING "0, 2, 852, 4769\0"
	static const char FULLVERSION_STRING[] = "0.2.852.4769";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 52;
	

}
#endif //VERSION_h
