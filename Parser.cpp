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

PENJIN_ERRORS Parser::loadParserConfigFile(CRstring fileName)
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

PENJIN_ERRORS Parser::createCommandList(CRstring fileName)
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
