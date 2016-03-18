#include "stdafx.h"
#include "DataProcessing.h"


CDataProcessing::CDataProcessing()
{
	m_preCodeFileName = NULL;
	m_cmtCodeFileName = NULL;

	m_preSourceCode = NULL;
	m_cmtSourceCode = NULL;

	m_outputList.clear();
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
	LPTSTR context = NULL;
	
	size_t len = 0;

	m_preCodeFileName = wcstok_s(arguments, TEXT(" "), &context);
	m_cmtCodeFileName = wcstok_s(context, TEXT(" "), &context);

	OpenCodeFile(m_preCodeFileName, m_cmtCodeFileName);

	return true;
}

bool CDataProcessing::OpenCodeFile(LPWSTR preCode, LPWSTR cmdCode)
{
	CFile preFile, cmtFile;
	int preFileLength, cmtFileLength;
	char* tmp = NULL;

	preFile.Open(preCode, CFile::modeRead, 0);

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


	cmtFile.Open(cmdCode, CFile::modeRead, 0);

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

	m_outputFileName = new WCHAR[wcslen(m_cmtCodeFileName) + wcslen(L".mcrt") + 1];
	wsprintf(m_outputFileName, L"%s.mcrt", m_cmtCodeFileName);

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
	
	m_cmtSourceCode = srcCode;
	m_txtLength = txtLength;

	ParsingData();

	if (WriteCmtInFile() == false)
	{
		return false;
	}
	return true;
}

void CDataProcessing::ParsingData()
{
	// 문제 발견. 차후에 코드 변경.
	int i = 0;
	int lineCnt = 1;
	int sCmtPoint, eCmtPoint;
	bool cmtFlag = false;
	LPWSTR cmtStr = NULL;
	LPWSTR outputData = NULL;

	CleanOutputList();

	for (i = 0; i < m_txtLength; i++)
	{
		if ((cmtFlag == false) && (m_cmtSourceCode[i] == L'\r'))
		{
			lineCnt++;
		}
		if ((cmtFlag == false) && (m_cmtSourceCode[i] == L'/') && (m_cmtSourceCode[i + 1] == L'+'))
		{
			i++;
			cmtFlag = true;
			sCmtPoint = i + 1;
		}
		if ((cmtFlag == true) && (m_cmtSourceCode[i] == L'+') && (m_cmtSourceCode[i + 1] == L'/'))
		{
			eCmtPoint = i - 1;
			cmtStr = new WCHAR[eCmtPoint - sCmtPoint + 1];
			wmemset(cmtStr, 0, eCmtPoint - sCmtPoint + 1);
			wcsncpy_s(cmtStr, eCmtPoint - sCmtPoint + 1, &m_cmtSourceCode[sCmtPoint], eCmtPoint - sCmtPoint);
			
			outputData = new WCHAR[30 + eCmtPoint - sCmtPoint + 1];
			wmemset(outputData, 0, 30 + eCmtPoint - sCmtPoint + 1);

			wsprintf(outputData, L"%d :%s\r\n", lineCnt, cmtStr);
			m_outputList.push_back(outputData);

			delete[] cmtStr;
			cmtStr = NULL;
			cmtFlag = false;
		}
	}
}

bool CDataProcessing::WriteCmtInFile()
{
	CFile outputFile;
	WORD wd = 0xfeff;
	WCHAR tmp[2];
	std::list<LPWSTR>::iterator iter;

	outputFile.Open(m_outputFileName, CFile::modeCreate | CFile::modeWrite, 0);
	memcpy(tmp, &wd, 2);
	outputFile.Write(tmp, 2);

	for (iter = m_outputList.begin(); iter != m_outputList.end(); iter++)
	{
		outputFile.Write(*iter, wcslen(*iter) * 2);
	}
	outputFile.Close();

	return true;
}

void CDataProcessing::CleanOutputList()
{
	std::list<LPWSTR>::iterator iter;
	if (!m_outputList.empty())
	{
		for (iter = m_outputList.begin(); iter != m_outputList.end(); iter++)
		{
			delete[](*iter);
		}

		m_outputList.clear();
	}
}