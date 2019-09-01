#pragma once
#include <Windows.h>
#define W_MAX_PATH MAX_PATH * 2

class CIniRW
{
public:
	CIniRW();
	CIniRW(char* szFileName);
	int Read(char* szSect, char* szKey, int iDefVal);
	double Read(char* szSect, char* szKey, double dblDefVal);
	bool Read(char* szSect, char* szKey, bool bolDefVal);
	char* Read(char* szSect, char* szKey, const char* szDefVal);
	void Write(char* szSect, char* szKey, int iVal);
	void Write(char* szSect, char* szKey, double dblVal);
	void Write(char* szSect, char* szKey, bool bolVal);
	void Write(char* szSect, char* szKey, char* szVal);
	void CreateTestIni();

	void DispWhole();
	bool Check();
	bool IsModified();

	~CIniRW();

private:
	char m_szFileName[MAX_PATH];
	wchar_t m_wszFileName[W_MAX_PATH];
	FILETIME m_ftWrite;
};

