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
#include "FileLister.h"
#include "Parser.h"

FileLister::FileLister()
{
    //ctor
    char* temp;
    temp = new char[_MAX_PATH];
    temp = getcwd(temp,_MAX_PATH);
    workingDir = temp;
    delete [] temp;
    createListing();
    folderDepth = -1;
    checkFolderDepth = true;
    includeParent = true;
    includeThis = true;
    includeLabel = true;
}

FileLister::FileLister(CRstring startDir)
{
    workingDir = startDir;
    createListing();
    folderDepth = -1;
    checkFolderDepth = true;
    includeParent = true;
    includeThis = true;
    includeLabel = true;
}

FileLister::~FileLister()
{
    //dtor
}

void FileLister::createListing()
{
    DIR* dir = NULL;
    dirent* dirEnt;
    dir = opendir(workingDir.c_str());
    if(!dir)
        return;

    listing.clear();
    listingTypes.clear();
    if (includeLabel)
	{
		listing.push_back(workingDir);
		listingTypes.push_back(PATH);
	}
    while((dirEnt = readdir(dir)))
    {
        if(filters.size() == 0)
        {
            int type = -1;
            string choice = dirEnt->d_name;
            #ifdef _WIN32
                struct stat fileStat;
                stat(string(workingDir + "/" + dirEnt->d_name).c_str(),&fileStat);
                if(fileStat.st_mode & DT_DIR)
                    type=DT_DIR;
                else if(fileStat.st_mode & DT_REG)
                    type=DT_REG;
                else
                    type=UNKNOWN;
            #else
                if(dirEnt->d_type == DT_DIR)
                    type=DT_DIR;
                else if(dirEnt->d_type == DT_REG)
                    type=DT_REG;
                else
                    type=UNKNOWN;
            #endif
            if ((choice != "." || includeThis) && (choice != ".." || includeParent))
			{
				listing.push_back(choice);
				listingTypes.push_back(type);
			}
        }
        else
        {
            for(int f = filters.size()-1; f>=0; --f)
            {
                int type = -1;
                string choice = dirEnt->d_name;
                #ifdef _WIN32
                    struct stat fileStat;
                    stat(string(workingDir + "/" + dirEnt->d_name).c_str(),&fileStat);
                    if(fileStat.st_mode & DT_DIR)
                        type=DT_DIR;
                    else if(fileStat.st_mode & DT_REG)
                        type=DT_REG;
                    else
                        type=UNKNOWN;
                #else
                    if(dirEnt->d_type == DT_DIR)
                        type=DT_DIR;
                    else if(dirEnt->d_type == DT_REG)
                        type=DT_REG;
                    else
                        type=UNKNOWN;
                #endif
                if ((filters.at(f) == "DIR" && type == DT_DIR && (choice != "." || includeThis) && (choice != ".." || includeParent))
						|| choice.find("." + filters.at(f)) != choice.npos)
                {
                    listing.push_back(choice);
                    listingTypes.push_back(type);
                }
            }
        }
    }
    closedir(dir);
}

void FileLister::createDisplay()
{
    if(listing.empty())
        createListing();

    clear();
    #ifdef _DEBUG
        cout << "Size: " << listing.size() << endl;
    #endif
    for(uint i = 0; i<listing.size(); ++i)
    {
        addItem(MENU_DIR_ITEM);
        #ifdef _DEBUG
        cout << "at(" << i << ") - " <<listing.at(i) << endl;
        #endif
        setMenuItemText(listing.at(i));
        if(i == 0 && includeLabel)
            setIsSelectable(false);
        else
            setIsSelectable(true);
        ((DirMenuItem*)menuItems.back())->setDirType(listingTypes.at(i));
    }
    setSelection(1);
}

string FileLister::getSelected()
{
    return listing.at(getSelection());
}

int FileLister::getSelectedType()
{
	if (menuItems.size() > getSelection())
		return ((DirMenuItem*)menuItems.at(getSelection()))->getDirType();
	else if (listingTypes.size() > getSelection())
		return listingTypes.at(getSelection());
	return -1;
}


string FileLister::enter()
{
    string t = getSelected();
    if(t == "..")       //  Same as goUp()
        goUp();
    else if(t == ".")   //  This directory.
        return t;
    else if(getSelectedType() == DT_DIR)
    {
        #if defined(_WIN32) && !defined(PENJIN_FILE_LISTER_LINUX_PATHS)
            workingDir+= ("\\" + t);
        #else
            workingDir+= ("/" + t);
        #endif
        createListing();
        clear();
        ++folderDepth;
        #ifdef _DEBUG
        cout << "FD: " << folderDepth << endl;
        #endif
    }
    #if defined(_WIN32) && !defined(PENJIN_FILE_LISTER_LINUX_PATHS)
        return getPath() + ("\\" + t);
    #else
        return getPath() + ("/" + t);
    #endif
}

void FileLister::goUp()
{
    if(folderDepth>=0 || !checkFolderDepth)
    {
        workingDir = Parser().getParentDirectory(workingDir);
        size_t back = workingDir.size()-1;
        if(workingDir[0] != 0 && (workingDir.at(back) == '/' || workingDir.at(back) == '\\'))
            workingDir.resize(back);
        createListing();
        clear();
        --folderDepth;
        #ifdef _DEBUG
        cout << "FD: " << folderDepth << endl;
        #endif
    }
}

void FileLister::update()
{
    if(listing.empty())
        createListing();
    ((Menu*)this)->update();
}

void FileLister::render()
{
    if(empty())
        createDisplay();

    ((Menu*)this)->render();
}
