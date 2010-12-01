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
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

#include "Command.h"
#include "TextDoc.h"
#include "StringUtility.h"
using namespace StringUtility;
#include "ErrorHandler.h"
using namespace std;

/// The keyword class stores the info needed to parse each keyword
//  They are stored in an array so the ID is the array index.
#include "KeyWord.h"

class Parser
{
    public:
        PENJIN_ERRORS loadParserConfig(CRstring fileName);      //  Load a config script that tell the parser the format of what it will parse
        PENJIN_ERRORS loadCommandList(CRstring fileName);		    //	Load a script file, parses it and creates a commandlist
        PENJIN_ERRORS loadParserConfig(const vector<string>& lines);      //  Load a config script from raw strings
        PENJIN_ERRORS loadCommandList(const vector<string>& lines);		    //	Load a script file from raw strings
        PENJIN_ERRORS saveParserConfig(CRstring fileName);      //  save a parser config file
        PENJIN_ERRORS saveCommandList(CRstring fileName);           //  save a parser script from a commandList



        uint getNumCommands(){return commandList.size();}
        uint countNumCommands(CRint commandType);          //  counts the number of a specific command
        void setCommandList(const queue<Command>& comList){commandList = comList;}
        queue<Command> getCommandList(){return commandList;}             //  Returns a copy of the commandList

        Command getNextCommand();	//	Gets the next command from the commandlist

        string getExtensionlessFilename(string name);	//	gets a filename minus the extension
        string getExtension(string name);
        string stripParentDirectory(string name);		//	removes the parent directory and just leaves the filename
        string getParentDirectory(string fileName);		//	Strips the filename and only leaves the path to the parent folder
        string getValue(string variable);		        //	Get a single value with the specified variable name.
        string stripValue(string variable);				//	Removes the latest value from the string

        // string* getValues(string variable);		//	Get multiple values with the specified variable name.

        string getVariableName(string line);	//	Extracts the name of a variable from a raw string
        string stripVariableName(string line);	//	Removes the variable name from a string and leaves the values only.

    private:
        uint countColons(CRstring line);
        queue <Command> commandList;	//	stores all decoded commands
        vector<KeyWord> keyWords;       //  List of key words the parser will look for
        TextDoc doc;
};

#endif	//	PARSER_H
