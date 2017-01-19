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
#ifndef FILELISTER_H
#define FILELISTER_H

/*
About: cross platform file and directory lister.
Parses directory and gives strings so you can load needed files.
*/

#ifdef _WIN32
    //#include <direct.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <stdlib.h>
    #define DT_DIR _S_IFDIR
    #define DT_REG _S_IFREG
#else
    #include <dirent.h>
    #include <unistd.h>
    //#include <sys/stat.h>
    #include <limits.h>
    #define _MAX_PATH PATH_MAX
    #ifdef PLATFORM_WII
        #define DT_DIR 4
        #define DT_REG 8
    #endif
#endif
#include "Menu.h"

class FileLister : public Menu
{
    public:
        FileLister();
        FileLister(CRstring startDir);
        virtual ~FileLister();

        virtual void render();
        virtual void update();

        string getPath()const{return workingDir;}
        // Set the working directory and create the listing (set all other settings and filters beforehand!)
        void setPath(CRstring path){workingDir = path; createListing();}
        void setCheckFolderDepth(CRbool check){checkFolderDepth = check;}
        string getSelected();       //  Return the string of selected item
        int getSelectedType();      //  Return the type of the selected item (dir or not)
        vector<string> getListing(){return listing;}//  Return entire director listing as a vector of strings.
        void clearListing(); 		//  Clear current listing
        string enter();             //  Enter the selected item(if directory) and return full path string of item.
        void goUp();                //  Go up one level in the directory tree

		// Filter results by file extension. Only files with a matching extension
		// will show up in the listing.
		// Pass file extension without the leading dot (CORRECT: "txt", WRONG: ".txt")
		// Use special filter "DIR" to filter for directories
        void addFilter(CRstring f){filters.push_back(f);}
        void clearFilters(){filters.clear();}
        // Include ".." in listing to go to parent directory. Only works when "DIR" filter is used.
        void includeParentDirInListing(CRbool inclParent) {includeParent = inclParent;}
        // Include "." element. Only has an effect when "DIR" filter is used.
        void includeThisDirInListing(CRbool inclThis) {includeThis = inclThis;}
        // Include workingDir label-element at the beginning of the listing.
        void includePathLabelInListing(CRbool inclLabel) {includeLabel = inclLabel;}

    private:
        void createListing();   //  creates strings for dir listing.
        void createDisplay();   //  builds MenuItems to show listing.

        string workingDir;
        int folderDepth;
        bool checkFolderDepth;
        vector<string> listing;
        vector<string> filters;
        enum DIR_TYPES
        {
            UNKNOWN=0,
            PATH
        };
        vector<int> listingTypes;
		bool includeParent;
		bool includeThis;
		bool includeLabel;
};

#endif // FILELISTER_H
