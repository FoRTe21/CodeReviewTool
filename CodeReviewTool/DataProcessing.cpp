#include "stdafx.h"
#include "DataProcessing.h"


CDataProcessing::CDataProcessing()
{
	m_preCodeFileName = NULL;
	m_cmtCodeFileName = NULL;

	m_preSourceCode = NULL;
	m_cmtSourceCode = NULL;
}


CDataProcessing::~CDataProcessing()
{
	delete[] m_preSourceCode;
	m_preSourceCode = NULL;

	delete[] m_cmtSourceCode;
	m_cmtSourceCode = NULL;
}

bool CDataProcessing::ReadCodeFile(LPTSTR arguments)
{
	// 파일명을 파싱하고 파일명으로 코드 파일을 엶.
	// 이 때 예외처리는 후에 추가.
	CFile preFile, cmtFile;
	char* tmp = NULL;
	LPTSTR context = NULL;
	int preFileLength, cmtFileLength;
	size_t len = 0;
	

	m_preCodeFileName = wcstok_s(arguments, TEXT(" "), &context);
	m_cmtCodeFileName = wcstok_s(context, TEXT(" "), &context);


	preFile.Open(m_preCodeFileName, CFile::modeRead, 0);

	preFileLength = preFile.GetLength();
	tmp = new char[preFileLength + 1];
	tmp[preFileLength] = '\0';

	preFile.Read(tmp, preFileLength); 
	m_preSourceCode = new WCHAR[preFileLength + 1];
	m_preSourceCode[preFileLength] = '\0';
	
	MultiByteToWideChar(CP_ACP, 0, tmp, -1, m_preSourceCode, preFileLength * 2);

	delete[] tmp;
	tmp = NULL;

	preFile.Close();


	cmtFile.Open(m_cmtCodeFileName, CFile::modeRead, 0);

	cmtFileLength = cmtFile.GetLength();
	tmp = new char[cmtFileLength + 1];
	tmp[cmtFileLength] = '\0';

	cmtFile.Read(tmp, cmtFileLength);
	
	m_cmtSourceCode = new WCHAR[cmtFileLength + 1];
	m_cmtSourceCode[cmtFileLength] = '\0';

	MultiByteToWideChar(CP_ACP, 0, tmp, -1, m_cmtSourceCode, cmtFileLength * 2);
	delete[] tmp;
	tmp = NULL;

	cmtFile.Close();
	return true;
}

LPTSTR CDataProcessing::GetPreSourceCode()
{
	return m_preSourceCode;
}


LPTSTR CDataProcessing::GetCmtSourceCode()
{
	return m_cmtSourceCode;
}

bool CDataProcessing::SaveCodeData(LPWSTR srcCode, int txtLength)
{
	//추후에 예외처리
	CFile outputFile;
	LPWSTR outputFileName, context, tmpFileName, copiedFileName;
	WORD wd = 0xfeff;
	WCHAR tmp[2];

	copiedFileName = new WCHAR[wcslen(m_cmtCodeFileName) + 1];
	wcscpy_s(copiedFileName, wcslen(m_cmtCodeFileName) + 1, m_cmtCodeFileName);
	m_cmtSourceCode = srcCode;
	tmpFileName = wcstok_s(copiedFileName, TEXT("."), &context);

	outputFileName = new WCHAR[wcslen(tmpFileName) + wcslen(TEXT(".mcrt")) + 1];
	wsprintfW(outputFileName, TEXT("%s.mcrt"), tmpFileName);

	outputFile.Open(outputFileName, CFile::modeCreate | CFile::modeWrite, 0);
	memcpy(tmp, &wd, 2);
	outputFile.Write(tmp, 2);
	outputFile.Write(srcCode, txtLength * 2);
	outputFile.Close();

	delete[] copiedFileName;
	delete[] outputFileName;
	return true;
}