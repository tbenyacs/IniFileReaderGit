/*
IniFileReader.cpp
© 2019 Tamás Benyács

Command line utility
Input parameters (mandatory):
1.) Path of the .ini file

Output:
A console list of the content of the given .ini file sensing the modifications.

E.g.:
IniFileReader.exe c:\Windows\test.ini
*/

#include "stdafx.h"
#include "IniRW.h"
#include <iostream>
#include <conio.h>
#include <filesystem>

using namespace std;

const long long DIVIDER = 1000;

int main(int argc, const char* argv[])
{
	cout << "Windows ini file reader V1.0 (C) 2019 Tamas Benyacs" << endl;

	int nArgIdx = 0;
	char sTmpProgName[MAX_PATH] = { 0 };
	strcpy_s(sTmpProgName, argv[nArgIdx++]);
	if (argc < 2)
	{
		cout << "Usage: " << sTmpProgName << " fully-qualified path" << endl << endl;
		exit(-1);
	}
	char sTmpPath[MAX_PATH] = { 0 };
	strcpy_s(sTmpPath, argv[nArgIdx]);

	try
	{
		CIniRW r(sTmpPath);
		long long nCnt = 0;

		do
		{
			if (!(nCnt++ % DIVIDER))
				if (r.IsModified())
					r.DispWhole();
		} while (!_kbhit());
	}
	catch (string e)
	{
		cout << e << endl;
		return 1;
	}
	catch (...)
	{
		cout << "Unspecified exception occurred." << endl;
		return 1;
	}

	cout << "Bye" << endl;

	int w = 0;
	cin >> w;

	return 0;
}
