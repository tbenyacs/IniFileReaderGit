========================================================================
    CONSOLE APPLICATION : IniFileReader V 1.0 © 2019 Tamás Benyács
========================================================================
Command line utility
Input parameters (mandatory):
1.) Path of the .ini file

Output:
A console list of the content of the given .ini file sensing the external modifications.

E.g.:
IniFileReader.exe c:\Windows\test.ini

This file contains a summary of what you will find in each of the files that
make up your IniFileReader application.

IniFileReader.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

IniFileReader.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

IniFileReader.cpp
    This is the main application source file.

IniRW.h
IniRW.cpp
	This is the ini file reading and writing class named CIniRW.

	Public methods are:
	CIniRW();
	CIniRW(char* szFileName);
		This constructor should be used for instantiate.
		It checks the ini file given in the input parameter.
		If the given path does not exist create and open it.
		
	int Read(char* szSect, char* szKey, int iDefVal);
		integer value reader method.
		
	double Read(char* szSect, char* szKey, double dblDefVal);
		double value reader method.
		
	bool Read(char* szSect, char* szKey, bool bolDefVal);
		boolean value reader method.
		
	char* Read(char* szSect, char* szKey, const char* szDefVal);
		null-terminated ASCII character array value reader method.
		
	void Write(char* szSect, char* szKey, int iVal);
		integer value writer method.
		
	void Write(char* szSect, char* szKey, double dblVal);
		double value writer method.
		
	void Write(char* szSect, char* szKey, bool bolVal);
		boolean value writer method.
		
	void Write(char* szSect, char* szKey, char* szVal);
		null-terminated ASCII character array value writer method.
		
	void CreateTestIni();
		Creates a test ini file if the given path does not exist.

	void DispWhole();
		Display the whole ini file given in the constructor parameter.
		
	bool Check();
		Check the ini file given in the constructor parameter.
		If the given path does not exist create and open it.
		
	bool IsModified();
		Examine if the given ini file has been modified externally.

	~CIniRW();
	

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named IniFileReader.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
