#pragma once
class CDataProcessing
{
private:
	LPTSTR m_preCodeFileName;
	LPTSTR m_cmtCodeFileName;

	LPWSTR m_preSourceCode;
	LPWSTR m_cmtSourceCode;
	
public:
	CDataProcessing();
	~CDataProcessing();

	bool ReadCodeFile(LPTSTR arguments);
	LPWSTR GetPreSourceCode();
	LPWSTR GetCmtSourceCode();
};

