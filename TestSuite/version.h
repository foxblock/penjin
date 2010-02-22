#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "22";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2010";
	static const double UBUNTU_VERSION_STYLE = 10.02;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 2;
	static const long BUILD = 833;
	static const long REVISION = 4663;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1427;
	#define RC_FILEVERSION 0,2,833,4663
	#define RC_FILEVERSION_STRING "0, 2, 833, 4663\0"
	static const char FULLVERSION_STRING[] = "0.2.833.4663";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 33;
	

}
#endif //VERSION_h
