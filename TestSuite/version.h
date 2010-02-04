#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "16";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2010";
	static const double UBUNTU_VERSION_STYLE = 10.01;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 2;
	static const long BUILD = 819;
	static const long REVISION = 4593;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1412;
	#define RC_FILEVERSION 0,2,819,4593
	#define RC_FILEVERSION_STRING "0, 2, 819, 4593\0"
	static const char FULLVERSION_STRING[] = "0.2.819.4593";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 19;
	

}
#endif //VERSION_h
