#include "stdafx.h"
#include "IniRW.h"
#include <iostream>
#include <string>
#include <atlstr.h>

using namespace std;

const unsigned int MAX_PROFILE_SECT = 32767;
const unsigned long MIN_READ_CHARS = 2;

CIniRW::CIniRW()
{
}

//This constructor should be used for instantiate.
//It checks the ini file given in the input parameter.
//If the given path does not exist create and open it.
CIniRW::CIniRW(char* szFileName)
{
	memset(m_szFileName, 0x00, MAX_PATH);
	memcpy(m_szFileName, szFileName, strlen(szFileName));
	Check();
	DispWhole();
}

//Display the whole ini file given in the constructor parameter.
void CIniRW::DispWhole()
{
	system("cls");
	char szSectNames[MAX_PROFILE_SECT];
	unsigned long nCharsSect = GetPrivateProfileSectionNamesA(szSectNames, sizeof(szSectNames) / sizeof(szSectNames[0]), m_szFileName);
	if (nCharsSect < MIN_READ_CHARS)
		throw string(m_szFileName) + " is not a valid Windows ini file.";

	cout << m_szFileName << endl;
	for (char* pSect = szSectNames; *pSect; ++pSect)
	{
		char szKeyValPairs[MAX_PROFILE_SECT];
		unsigned long nChars = GetPrivateProfileSectionA(pSect, szKeyValPairs, sizeof(szKeyValPairs) / sizeof(szKeyValPairs[0]), m_szFileName);
		if (nChars < MIN_READ_CHARS)
			cout << "There is no key in this section." << endl;

		cout << "[" << pSect << "]" << endl;
		for (char* pKeyVal = szKeyValPairs; *pKeyVal; ++pKeyVal)
		{
			cout << pKeyVal << endl;
			pKeyVal += strlen(pKeyVal);
		}
		cout << endl;

		pSect += strlen(pSect);
	}
}

//Examine if the given ini file has been modified externally.
bool CIniRW::IsModified()
{
	bool bRet = false;
	HANDLE hFile;

	hFile = CreateFileA(m_szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		throw string(m_szFileName) + " unable to open.";

	FILETIME ftCreate, ftAccess, ftWrite;
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
	{
		CloseHandle(hFile);
		return bRet;
	}

	long n = CompareFileTime(&m_ftWrite, &ftWrite);
	if (n < 0)
	{
		m_ftWrite = ftWrite;
		bRet = true;
	}
	CloseHandle(hFile);

	return bRet;
}

//Check the ini file given in the constructor parameter.
//If the given path does not exist create and open it.
bool CIniRW::Check()
{
	HANDLE hFile;

	hFile = CreateFileA(m_szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		CreateTestIni(); // If the given file does not exist create and open it.
		hFile = CreateFileA(m_szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			throw string(m_szFileName) + " unable to open.";
	}

	FILETIME ftCreate, ftAccess;

	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &m_ftWrite))
		return false;

	CloseHandle(hFile);

	return true;
}

//integer value reader method.
int CIniRW::Read(char* szSect, char* szKey, int iDefVal)
{
	int iResult = GetPrivateProfileIntA(szSect, szKey, iDefVal, m_szFileName);
	return iResult;
}

//double value reader method.
double CIniRW::Read(char* szSect, char* szKey, double dblDefVal)
{
	char szResult[MAX_PATH];
	char szDef[MAX_PATH];
	double fltResult;
	sprintf_s(szDef, "%f", dblDefVal);
	GetPrivateProfileStringA(szSect, szKey, szDef, szResult, MAX_PATH, m_szFileName);
	fltResult = atof(szResult);

	return fltResult;
}

//boolean value reader method.
bool CIniRW::Read(char* szSect, char* szKey, bool bDefVal)
{
	char szResult[MAX_PATH];
	char szDef[MAX_PATH];
	bool bolResult;
	sprintf_s(szDef, "%s", bDefVal ? "True" : "False");
	GetPrivateProfileStringA(szSect, szKey, szDef, szResult, MAX_PATH, m_szFileName);
	bolResult = (strcmp(szResult, "True") == 0 || strcmp(szResult, "true") == 0) ? true : false;

	return bolResult;
}

//null - terminated ASCII character array value reader method.
char* CIniRW::Read(char* szSect, char* szKey, const char* szDefVal)
{
	char* szResult = new char[MAX_PATH];
	memset(szResult, 0x00, MAX_PATH);
	GetPrivateProfileStringA(szSect, szKey, szDefVal, szResult, MAX_PATH, m_szFileName);

	return szResult;
}

//integer value writer method.
void CIniRW::Write(char* szSection, char* szKey, int iVal)
{
	char szVal[MAX_PATH];
	sprintf_s(szVal, "%d", iVal);
	WritePrivateProfileStringA(szSection, szKey, szVal, m_szFileName);
}

//double value writer method.
void CIniRW::Write(char* szSection, char* szKey, double dblVal)
{
	char szVal[MAX_PATH];
	sprintf_s(szVal, "%f", dblVal);
	WritePrivateProfileStringA(szSection, szKey, szVal, m_szFileName);
}

//boolean value writer method.
void CIniRW::Write(char* szSection, char* szKey, bool bolValue)
{
	char szVal[MAX_PATH];
	sprintf_s(szVal, "%s", bolValue ? "True" : "False");
	WritePrivateProfileStringA(szSection, szKey, szVal, m_szFileName);
}

//null - terminated ASCII character array value writer method.
void CIniRW::Write(char* szSection, char* szKey, char* szValue)
{
	WritePrivateProfileStringA(szSection, szKey, szValue, m_szFileName);
}

/*
Creates a test ini file if the given path does not exist:
[Elso]
Kulcs1 = Ertek1
Kulcs2 = 10
Kulcs3 = 11.45
Kulcs4 = false

[Masodik]
KulcsM1 = Masodik szekcio elso erteke
KulcsM2 = true
KulcsM3 = 8686
KulcsM4 = b
*/
void CIniRW::CreateTestIni()
{
	Write("Elso", "Kulcs1", "Ertek1");
	Write("Elso", "Kulcs2", 10);
	Write("Elso", "Kulcs3", 11.45f);
	Write("Elso", "Kulcs4", false);

	Write("Masodik", "KulcsM1", "Masodik szekcio elso erteke");
	Write("Masodik", "KulcsM2", true);
	Write("Masodik", "KulcsM3", 8686);
	Write("Masodik", "KulcsM4", "b");
}

CIniRW::~CIniRW()
{
}
