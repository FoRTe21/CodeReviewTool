#pragma once
class CDataProcessing
{
private:
	LPWSTR m_preCodeFileName;
	LPWSTR m_cmtCodeFileName;

	LPWSTR m_preSourceCode;
	LPWSTR m_cmtSourceCode;
	
public:
	CDataProcessing();
	~CDataProcessing();

	bool ReadCodeFile(LPTSTR arguments);
	LPWSTR GetPreSourceCode();
	LPWSTR GetCmtSourceCode();

	bool SaveCodeData(LPWSTR srcCode, int txtLength);
};

