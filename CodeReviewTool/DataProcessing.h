#pragma once
#include <list>

class CDataProcessing
{
protected:
	LPWSTR m_preCodeFileName;
	LPWSTR m_cmtCodeFileName;

	LPWSTR m_outputFileName;

	LPWSTR m_preSourceCode;
	LPWSTR m_cmtSourceCode;
	
	std::list<LPWSTR> m_outputList;
	int m_txtLength;

protected:
	void ParsingData();
	bool WriteCmtInFile();
	void CleanOutputList();

public:
	CDataProcessing();
	~CDataProcessing();

	bool ReadCodeFile(LPTSTR arguments);
	LPWSTR GetPreSourceCode();
	LPWSTR GetCmtSourceCode();

	bool SaveCodeData(LPWSTR srcCode, int txtLength);
	bool OpenCodeFile(LPWSTR preCode, LPWSTR cmdCode);
};

