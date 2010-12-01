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
#include "Parser.h"

Command Parser::getNextCommand()
{
	Command temp;
	temp.commandType = -1; // ERROR

	if (!commandList.empty())
	{
		temp = commandList.front();
		commandList.pop();
	}
	return temp;
}

uint Parser::countNumCommands(CRint com)
{
    queue <Command> tList;
    tList = commandList;
    Command tCom;
    uint comCount = 0;
    while(!tList.empty())
	{
	    tCom = tList.front();
		if(tCom.commandType == com)
            ++comCount;
		tList.pop();
	}
    return comCount;
}


PENJIN_ERRORS Parser::loadParserConfig(const vector<string>& lines)
{
    PENJIN_ERRORS status = doc.load(lines);
    //  Load the parser's configuration script
    if(status != PENJIN_OK)
        return status;

    keyWords.clear();

    KeyWord tempKey;
    string tempLine;
    int variableCount = -1;

    //  Run through the file
    for(uint i = 0; i < doc.size();++i)
    {
        // Reset tempKey and comment
        tempKey = "NULL";
        tempKey = NULL;

        /// Get a line to work with
        tempLine = doc.getLine(i);
        if(tempLine[0] == ';')
            continue;
        // Get a variable name
        if(tempLine.find(":") != tempLine.npos)
        {
			tempKey = getVariableName(tempLine);	//	Get the name of the variable
			tempLine = stripVariableName(tempLine); //	Now leave only the values
            if(!tempKey.getKeyWord().empty())
                ++variableCount;
            else
                return PENJIN_PARSE_ERROR;
            tempKey = variableCount;
        }
        else if(tempLine.find(";") != tempLine.npos)
        {
            // it's only a comment don't parse it
            status = PENJIN_OK;
            continue;
        }
        else
            return PENJIN_PARSE_ERROR;
        /// next get number of alpha parameters
        tempKey.setNumAlphas (stringToInt(getValue(tempLine)));
        tempLine = stripValue(tempLine);
        /// next get number of numerics
        tempKey.setNumNumerics(stringToInt(getValue(tempLine)));
        tempLine = stripValue(tempLine);
        keyWords.push_back(tempKey);
        status = PENJIN_OK;
    }
    return status;
}

PENJIN_ERRORS Parser::loadParserConfig(CRstring fileName)
{
    PENJIN_ERRORS status = doc.load(fileName);
    //  Load the parser's configuration script
    if(status != PENJIN_OK)
        return status;

    keyWords.clear();

    KeyWord tempKey;
    string tempLine;
    int variableCount = -1;

    //  Run through the file
    for(uint i = 0; i < doc.size();++i)
    {
        // Reset tempKey and comment
        tempKey = "NULL";
        tempKey = NULL;

        /// Get a line to work with
        tempLine = doc.getLine(i);
        if(tempLine[0] == ';')
            continue;
        // Get a variable name
        if(tempLine.find(":") != tempLine.npos)
        {
			tempKey = getVariableName(tempLine);	//	Get the name of the variable
			tempLine = stripVariableName(tempLine); //	Now leave only the values
            if(!tempKey.getKeyWord().empty())
                ++variableCount;
            else
                return PENJIN_PARSE_ERROR;
            tempKey = variableCount;
        }
        else if(tempLine.find(";") != tempLine.npos)
        {
            // it's only a comment don't parse it
            status = PENJIN_OK;
            continue;
        }
        else
            return PENJIN_PARSE_ERROR;
        /// next get number of alpha parameters
        tempKey.setNumAlphas (stringToInt(getValue(tempLine)));
        tempLine = stripValue(tempLine);
        /// next get number of numerics
        tempKey.setNumNumerics(stringToInt(getValue(tempLine)));
        tempLine = stripValue(tempLine);
        keyWords.push_back(tempKey);
        status = PENJIN_OK;
    }
    return status;
}

PENJIN_ERRORS Parser::saveParserConfig(CRstring fileName)
{
    doc.clear();
    doc.append(";   Parser configuration File.");
    doc.append(";   Saved by Penjin Parser::saveParserConfigFile(CRstring fileName)");
    if(keyWords.empty())
        return PENJIN_ERROR;
    for(uint i = 0; i < keyWords.size(); ++i)
    {
        doc.append(keyWords.at(i).getKeyWord() + ":"
        + StringUtility::intToString(keyWords.at(i).getNumAlphas())
        + "," + StringUtility::intToString(keyWords.at(i).getNumNumerics()) + ";");
    }
    return doc.save(fileName);
}

PENJIN_ERRORS Parser::saveCommandList(CRstring fileName)
{
    doc.clear();
    doc.append(";   Parser command list File.");
    doc.append(";   Saved by Penjin Parser::saveCommandList(CRstring fileName)");
    queue <Command> t = Parser::getCommandList();
    while(!t.empty())
    {
        Command c = t.front();
        int ID = c.commandType;
        if(ID != -1)
        {
            string out = keyWords.at(ID).getKeyWord() + ":";

            for(uint p = 0; p < c.params.size(); ++p)
            {
                if(c.params.at(p).hasString())
                    out+=c.params.at(p).getString() + ",";
                else if(c.params.at(p).hasFloat())
                    out+= StringUtility::floatToString( c.params.at(p).getFloat()) + ",";
            }
            out.at(out.size()-1) = ';';
            doc.append(out);
        }
        else
            return PENJIN_ERROR;
    }
    return doc.save(fileName);
}

PENJIN_ERRORS Parser::loadCommandList(const vector<string>& lines)
{
    // Check if parser has been configured
    if(keyWords.empty())
        return PenjinErrors::PENJIN_PARSE_ERROR;
	///	open script file
	PENJIN_ERRORS status = doc.load(lines);
	if(status != PENJIN_OK)
        return status;

    /// Now the script is open, we need to compare extracted KeyWords to the keywords
    //  We have stored.
    string tempLine;
    string var;
    for(uint i = 0; i < doc.size();++i)
    {
        tempLine = doc.getLine(i);

        if(tempLine[0] == ';')
            continue;

        if(countColons(tempLine) != 1)
            return PENJIN_PARSE_ERROR;

        if(tempLine.find(":") != tempLine.npos)
        {
            //  get the variable name
            var = getVariableName(tempLine);
            if(var.empty())
                return PENJIN_PARSE_ERROR;
            int ID = -1;
            /// Check the variable against all of the configd ids
            for(uint j = 0; j < keyWords.size(); ++j)
            {
                if(var == keyWords[j].getKeyWord())
                {
                    ID = keyWords[j].getKeyType();
                    break;
                }
            }
            if( ID == -1)
                return PENJIN_PARSE_ERROR;
            /// Otherwise create a command
            Command tempCommand;
            tempCommand.commandType = ID;
            tempLine = stripVariableName(tempLine);
            Variable tempVariable;
            /// Now get the number of alpha components from KeyWord object
            if(keyWords[ID].getNumAlphas() == -1)
            {
                /// This is an indefinite number of parameters We just have to try to parse what we find
                while(!tempLine.empty())
                {
                    tempVariable.setNULL();
                    tempVariable = getValue(tempLine);
                    tempLine = stripValue(tempLine);
                    tempCommand.params.push_back(tempVariable);
                }
            }
            else
            {
                for (int j = 0; j < keyWords[ID].getNumAlphas(); ++j)
                {
                    tempVariable.setNULL();
                    tempVariable = getValue(tempLine);
                    tempLine = stripValue(tempLine);
                    tempCommand.params.push_back(tempVariable);
                }
            }
            /// Now get the number of numeric components from KeyWord object
            if(keyWords[ID].getNumNumerics() == -1)
            {
                /// This is an indefinite number of parameters We just have to try to parse what we find
                while(!tempLine.empty())
                {
                    tempVariable.setNULL();
                    tempVariable.setFloat(stringToFloat(getValue(tempLine)));
                    tempLine = stripValue(tempLine);
                    tempCommand.params.push_back(tempVariable);
                }
            }
            else
            {
                for (int j = 0; j < keyWords[ID].getNumNumerics(); ++j)
                {
                    tempVariable.setNULL();
                    tempVariable.setFloat(stringToFloat(getValue(tempLine)));
                    tempLine = stripValue(tempLine);
                    tempCommand.params.push_back(tempVariable);
                }
            }
            /// add the constructed command onto the list
            commandList.push(tempCommand);
        }

    }
	return status;
}

PENJIN_ERRORS Parser::loadCommandList(CRstring fileName)
{
    // Check if parser has been configured
    if(keyWords.empty())
        return PenjinErrors::PENJIN_PARSE_ERROR;
	///	open script file
	PENJIN_ERRORS status = doc.load(fileName);
	if(status != PENJIN_OK)
        return status;

    /// Now the script is open, we need to compare extracted KeyWords to the keywords
    //  We have stored.
    string tempLine;
    string var;
    for(uint i = 0; i < doc.size();++i)
    {
        tempLine = doc.getLine(i);

        if(tempLine[0] == ';')
            continue;

        if(countColons(tempLine) != 1)
            return PENJIN_PARSE_ERROR;

        if(tempLine.find(":") != tempLine.npos)
        {
            //  get the variable name
            var = getVariableName(tempLine);
            if(var.empty())
                return PENJIN_PARSE_ERROR;
            int ID = -1;
            /// Check the variable against all of the configd ids
            for(uint j = 0; j < keyWords.size(); ++j)
            {
                if(var == keyWords[j].getKeyWord())
                {
                    ID = keyWords[j].getKeyType();
                    break;
                }
            }
            if( ID == -1)
                return PENJIN_PARSE_ERROR;
            /// Otherwise create a command
            Command tempCommand;
            tempCommand.commandType = ID;
            tempLine = stripVariableName(tempLine);
            Variable tempVariable;
            /// Now get the number of alpha components from KeyWord object
            if(keyWords[ID].getNumAlphas() == -1)
            {
                /// This is an indefinite number of parameters We just have to try to parse what we find
                while(!tempLine.empty())
                {
                    tempVariable.setNULL();
                    tempVariable = getValue(tempLine);
                    tempLine = stripValue(tempLine);
                    tempCommand.params.push_back(tempVariable);
                }
            }
            else
            {
                for (int j = 0; j < keyWords[ID].getNumAlphas(); ++j)
                {
                    tempVariable.setNULL();
                    tempVariable = getValue(tempLine);
                    tempLine = stripValue(tempLine);
                    tempCommand.params.push_back(tempVariable);
                }
            }
            /// Now get the number of numeric components from KeyWord object
            if(keyWords[ID].getNumNumerics() == -1)
            {
                /// This is an indefinite number of parameters We just have to try to parse what we find
                while(!tempLine.empty())
                {
                    tempVariable.setNULL();
                    tempVariable.setFloat(stringToFloat(getValue(tempLine)));
                    tempLine = stripValue(tempLine);
                    tempCommand.params.push_back(tempVariable);
                }
            }
            else
            {
                for (int j = 0; j < keyWords[ID].getNumNumerics(); ++j)
                {
                    tempVariable.setNULL();
                    tempVariable.setFloat(stringToFloat(getValue(tempLine)));
                    tempLine = stripValue(tempLine);
                    tempCommand.params.push_back(tempVariable);
                }
            }
            /// add the constructed command onto the list
            commandList.push(tempCommand);
        }

    }
	return status;
}

string Parser::getVariableName(string line)
{
	char outString[1000];
	unsigned int x =0 ;
	while( x < strlen(line.c_str()))
	{
		if(line[x] != ':')
		{
			outString[x] = line[x];
		}
		else
		{
			break;
		}
		++x;
	}
	outString[x] = 0;
	line = outString;
	return line;
}

string Parser::stripVariableName(string line)
{
	char outString[1000];
	int x = 0;

	//	get to point where variable name stops
	while(line[x] != ':')
	{
		++x;
	}
	++x;

	//	Copy string accross
	uint i = 0 ;
	while( i < strlen(line.c_str()))
	{
		if(line[x] == ';')
		{
			line[x+1] = 0;
		}
		else if(line[x] == 0)
		{
			break;
		}

		outString[i] = line[x];
		++x;++i;
	}
		outString[i] = 0;
		return outString;
}

string Parser::getParentDirectory(string fileName)
{
	uint x = (uint)strlen(fileName.c_str()) ;
	while( x > 0)
	{
		if(fileName[x] == '/' || fileName[x] == '\\')	//Check for furthest forwardslash
		{
			//fileName[x+1] = 0;	//chop off the filename
			break;
		}
		--x;
	}

	char output[1000];
	unsigned int i = 0;

	while ( i < x+1)
	{
		output[i] = fileName[i];
		++i;
	}
	output[i] = 0;
	fileName = output;
	return fileName;	//	Return just the path
}

string Parser::stripParentDirectory(string line)
{
	char outString[1000];
	int x = 0;

	//	get to point where variable stops
	while(line[x] != '/')
	{
		++x;
	}
	++x;

	//	Copy string accross
	uint i = 0 ;
	while( i < strlen(line.c_str()))
	{
		if(line[x] == ';')
		{
			line[x+1] = 0;
		}
		else if(line[x] == 0)
		{
			break;
		}

		outString[i] = line[x];
		++x;++i;
	}
	outString[i] = 0;
	return outString;
}

string Parser::getValue(string var)
{
	char outString[1000];
	unsigned int x =0 ;
	while( x < strlen(var.c_str()))
	{
		if(var[x] != ';' && var[x] != ',')
		{
			outString[x] = var[x];
		}
		else
		{
			break;
		}
		++x;
	}
	outString[x] = 0;
	return outString;
}

string Parser::stripValue(string line)
{
	char outString[1000];
	int x = 0;

	//	get to point where variable stops
	while(line[x] != ',' && line[x] != ';')
	{
		++x;
	}
	++x;

	//	Copy string accross
	uint i = 0 ;
	while( i < strlen(line.c_str()))
	{
		if(line[x] == ';')
		{
			line[x+1] = 0;
		}
		else if(line[x] == 0)
		{
			break;
		}

		outString[i] = line[x];
		++x;++i;
	}
	outString[i] = 0;
	return outString;
}

string Parser::getExtensionlessFilename(string line)
{
	char outString[1000];
	uint x =0 ;
	while( x < strlen(line.c_str()))
	{
		if(line[x] != '.')
		{
			outString[x] = line[x];
		}
		else
		{
			break;
		}
		++x;
	}
	outString[x] = 0;
	line = outString;
	return line;
}

string Parser::getExtension(string line)
{
	char outString[5];
	int x = strlen(line.c_str())-1;
	int y = 0;
	while( x > 0)
	{
		if(line[x] != '.')
		{
			outString[y] = line[x];
		}
		else
		{
			break;
		}
		--x;++y;
	}
	outString[y] = 0;
	StringUtility::reverse(outString);
	line = outString;
	return line;
}

uint Parser::countColons(CRstring line)
{
    uint count = 0;
    for(int i = line.size()-1; i>=0;--i)
        if(line[i] == ':')
            ++count;
    return count;
}
