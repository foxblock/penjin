#include "ASCII_Title.h"

ASCII_Title::ASCII_Title()
{
    //ctor
    title = Penjin::getApplicationName();
    version = (string)AutoVersion::FULLVERSION_STRING + (string)AutoVersion::STATUS_SHORT;
    description = "Default Penjin Application.";
}

ASCII_Title::~ASCII_Title()
{
    //dtor
}

void ASCII_Title::render()
{
	for (int i = 0; i < (int)title.length()+2; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "#" << title.c_str() << "#" << endl;
	string versiontext = "Version: ";
	cout << "#";
	for (int i = 0; i < ( ( (int)title.length() - ( (int)versiontext.length() + (int)version.length() ) ) / 2 ); i++)
	{
		cout << '~';
	}
	cout << versiontext.c_str() << version.c_str();
	for (int i = 0; i < ( ( (int)title.length() - ( (int)versiontext.length() + (int)version.length() ) ) / 2); i++)
	{
		cout << "~";
	}
	cout << "#" << endl;
	cout << "#";
	for (int i = 0; i < (int)title.length(); i++)
	{
		cout << "-";
	}
	cout << "#" << endl;
	cout << description.c_str() << endl << endl;
}
