#include "TextDoc.h"

void TextDoc::append(CRstring data)
{
	docData.push_back(data);
}

void TextDoc::editLine(CRint line,CRstring newData)
{
	docData[line] = newData;
}

int TextDoc::findLine(CRstring target)
{
	for(int i = docData.size()-1; i >= 0; --i)
	{
		if(strstr(docData[i].c_str(),target.c_str()))
		{
			return i;
		}
	}
	return PENJIN_ERROR;
}

void TextDoc::clear()
{
    docData.clear();
}

PENJIN_ERRORS TextDoc::load(CRstring file)
{
	ifstream ifile(file.c_str());//load infile
	if(!ifile.is_open())
	{
		return PENJIN_FILE_NOT_FOUND;
	}

    clear();

    string temp = "NULL";
	vector <string> tStrings;
	while(ifile.good())
	{
	    getline(ifile,temp);
	    temp+="\n";
	    if(temp == "\n")
            break;
		docData.push_back(temp);
	}
	if(ifile.is_open())
	{
		ifile.close();
		return PENJIN_OK;
	}
	return PENJIN_ERROR;
}

PENJIN_ERRORS TextDoc::save(CRstring file)
{
	ofstream ofile(file.c_str());//save ofile
	if(!ofile.is_open())
	{
		return PENJIN_UNABLE_TO_SAVE;
	}
	size_t size = docData.size();
	for (size_t i = 0; i < size; ++i)
	{
			ofile << docData[i];

			if(i < docData.size()-1)
			{
				ofile << "\n";
			}
	}
	if(ofile.is_open())
	{
		ofile.close();
		return PENJIN_OK;
	}
	return PENJIN_ERROR;
}

string TextDoc::getLine(CRint line)
{
	if(line<(int)docData.size())
		return docData[line];
	return ErrorHandler().getErrorString(PENJIN_INVALID_INDEX);
}

void TextDoc::search(CRstring target)
{
}

void TextDoc::viewDoc()
{
	for (size_t i = 0; i < docData.size(); ++i)
		cout << "L:" << i << " " <<this->docData[i] << endl;
}

