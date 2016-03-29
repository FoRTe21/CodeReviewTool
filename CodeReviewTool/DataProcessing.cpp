#include "stdafx.h"
#include "DataProcessing.h"

CDataProcessing::CDataProcessing()
{

	
}

CDataProcessing::~CDataProcessing()
{

}

bool CDataProcessing::InitDataProcessor()
{
	WCHAR currentDirectory[MAX_PATH] = { 0, };
	if (GetCurrentDirectoryW(_countof(currentDirectory), currentDirectory) == 0)
	{
		CString errorStr;
		errorStr.Format(L"현재 디렉토리 경로 찾기 실패 - ErrorCode : %d", GetLastError());
		::AfxMessageBox(errorStr, 0, 0);
		return false;
	}

	m_sourceCodesFilePath.Format(L"%s\\%s", currentDirectory, m_temporaryFileDirectory);
}

bool CDataProcessing::FindTemporaryFileDirectory()
{
	CString findDirectory;
	findDirectory.Format(L"%s\\*.*", m_sourceCodesFilePath);

	CFileFind fileFind;
	BOOL bResult = fileFind.FindFile(findDirectory);
	if (bResult == FALSE)
	{
		bResult = CreateDirectory(m_sourceCodesFilePath + "\\", NULL);
		if (bResult = FALSE)
		{
			::AfxMessageBox(L"임시 저장 디렉토리 생성 실패", 0, 0);
			return false;
		}
	}

	return true;
}

bool CDataProcessing::GetTextFromFile(CString filepath, CString& contents)
{
	CFile reviewFile;
	Encodings unicode;

	if (reviewFile.Open(filepath, CFile::modeRead, 0) == NULL)
	{
		::AfxMessageBox(L"파일을 열수 없습니다", 0, 0);
		return false;
	}
	
	unicode = CheckEncoding(reviewFile);
	switch (unicode)
	{
	case ANSI:
		contents = ReadANSIFile(reviewFile);
		break;
	case UTF16:
		contents = ReadUTF16LeFile(reviewFile);
		break;
	case UTF8:
		contents = ReadUTF8File(reviewFile);
		break;
	case UTF16BIGENDIAN:
		contents = ReadUTF16BeFile(reviewFile);
		break;
	default:
		::AfxMessageBox(L"지원 인코딩 : ANSI, UTF8, UTF16LE, UTF16BE", 0, 0);
		reviewFile.Close();
		return false;
	}

	
	reviewFile.Close();

	return true;
}

CString CDataProcessing::ReadANSIFile(CFile& reviewFile)
{
	std::vector<CHAR> buffer = ReadFile<CHAR>(reviewFile);

	CString strBuffer(buffer.data());
	return strBuffer;
}

CString CDataProcessing::ReadUTF16LeFile(CFile& reviewFile)
{
	std::vector<WCHAR> buffer = ReadFile<WCHAR>(reviewFile);

	CString strBuffer(buffer.data());
	return strBuffer;
}

CString CDataProcessing::ReadUTF16BeFile(CFile& reviewFile)
{
	std::vector<WCHAR> buffer = ReadFile<WCHAR>(reviewFile);

	for (ULONG i = 0; i < buffer.size(); i++)
	{
		buffer[i] = ConvertWCHAREndian(buffer[i]);
	}

	CString strBuffer(buffer.data());
	return strBuffer;
}

CString CDataProcessing::ReadUTF8File(CFile& reviewFile)
{
	std::vector<CHAR> buffer = ReadFile<CHAR>(reviewFile);
	const int byteNumberPerCharacterInUtf8 = 4;
	std::vector<WCHAR> wideCharArray(buffer.size() * byteNumberPerCharacterInUtf8);
	MultiByteToWideChar(CP_UTF8, 0, (LPCCH)buffer.data(), buffer.size(), wideCharArray.data(), buffer.size() * byteNumberPerCharacterInUtf8);

	CString strBuffer(wideCharArray.data());
	return strBuffer;
}

WCHAR CDataProcessing::ConvertWCHAREndian(WCHAR data)
{
	return (((data & 0xff) << 8) | ((data >> 8) & 0xff));
}

template<typename BufferType> std::vector<BufferType> CDataProcessing::ReadFile(CFile& reviewFile)
{
	UINT fileSize = static_cast<UINT>(reviewFile.GetLength());
	std::vector<BufferType> buffer(fileSize);
	buffer.push_back('\0');

	reviewFile.Read(buffer.data(), fileSize);

	return buffer;
}

CDataProcessing::Encodings CDataProcessing::CheckEncoding(CFile& file)
{
	unsigned char encodingHeader[2] = { 0, };
	enum Encodings encodingType;

	file.Read(encodingHeader, 2);

	if (encodingHeader[0] == 0xff && encodingHeader[1] == 0xfe)
	{
		encodingType = UTF16;
	}
	else if (encodingHeader[0] == 0xfe && encodingHeader[1] == 0xff)
	{
		encodingType = UTF16BIGENDIAN;
	}
	else if (encodingHeader[0] == 0xef && encodingHeader[1] == 0xbb)
	{
		file.Read(encodingHeader, 1);
		if (encodingHeader[0] == 0xbf)
		{
			encodingType = UTF8;
		}
	}
	else
	{
		encodingType = ANSI;
		file.SeekToBegin();
	}

	return encodingType;
}

void CDataProcessing::ClearAllData()
{
	m_reviewText.Empty();
	m_url.Empty();
	m_revisions.clear();

	for (auto iter = m_reviews.begin(); iter != m_reviews.end(); ++iter)
	{
		iter->Clear();
	}
	m_reviews.clear();
}

bool CDataProcessing::FillReviewData()
{
	
	int tmpIndex = 0;
	CReviewData tempReviewData;
	bool sameFileFlag = false;

	int index = 0;
	CString oneLine = m_reviewText.Tokenize(L"\r\n", index);
	CString tmpString = oneLine.Tokenize(L": ", tmpIndex);

	if (tmpString.CompareNoCase(L"url") == 0)
	{
		oneLine.Delete(0, wcslen(L"url: "));
		m_url = oneLine;
	}
	else
	{
		return false;
	}

	CString revision;

	while ((oneLine = m_reviewText.Tokenize(L"\r\n", index)) != L"")
	{
		tmpString = oneLine.GetAt(0);
		if (tmpString.CompareNoCase(L"R") == 0)
		{
			if (sameFileFlag == true)
			{
				tempReviewData.SetRevision(revision);
				m_reviews.push_back(tempReviewData);
				tempReviewData.Clear();
				tempReviewData.AddComments(L"\r\n");
				sameFileFlag = false;
			}
			oneLine.Delete(0, wcslen(L"Rev."));
			revision = oneLine;
			m_revisions.push_back(revision);
		}
		else if (tmpString.CompareNoCase(L"*") == 0)
		{
			if (sameFileFlag == false)
			{
				sameFileFlag = true;
				tempReviewData.Clear();
				tempReviewData.SetRevision(revision);
			}
			else
			{
				tempReviewData.SetRevision(revision);
				m_reviews.push_back(tempReviewData);
				tempReviewData.Clear();
			}

			oneLine.Delete(0, wcslen(L"* /"));
			CString ExtractedPrefix = oneLine;
			ExportFileFromRepository(revision, ExtractedPrefix);
				
			CString pureFileName = ExtractFileNameFromFilePath(ExtractedPrefix);
			tempReviewData.SetFilePath(pureFileName);
			
			CString filepath;
			filepath.Format(L"%s\\%s", m_sourceCodesFilePath, pureFileName);

			CString content;
			if (GetTextFromFile(filepath, content) == true)
			{
				DeleteSourceCodeFile(filepath);
			}
			tempReviewData.SetSourceCode(content);
			tempReviewData.AddComments(L"\r\n");
		}
		else
		{
			tmpString = oneLine.GetAt(0);
			if (tmpString.CompareNoCase(L"\t") == 0)
			{
				if (oneLine.GetLength() > 2) 
				{
					tmpString = oneLine.GetAt(1);
					if (tmpString.CompareNoCase(L"-") == 0)
					{
						int i = 0;
						tmpString = oneLine;
						AddLineNumbers(tmpString.Tokenize(L":", i), tempReviewData);
					}
				}
			}
			tempReviewData.AddComments(oneLine);
		}
	}

	if (sameFileFlag == true)
	{
		tempReviewData.SetRevision(revision);
		m_reviews.push_back(tempReviewData);
	}

	return true;
}

const std::list<CString> CDataProcessing::GetRivisions() const
{
	return m_revisions;
}

const std::list<CReviewData> CDataProcessing::GetReviews() const
{
	return m_reviews;
}

void CDataProcessing::SetReviewText(CString text)
{
	m_reviewText = text;
}

int CDataProcessing::AddLineNumbers(CString numbers, CReviewData& reviewData)
{
	CString number;
	int index = 0, count = 0;
	numbers.Delete(0, wcslen(L"- "));

	while ((number = numbers.Tokenize(L",", index)) != "")
	{
		++count;
		reviewData.AddLineNumber(_ttoi(number));
	}

	return count;
}

int CDataProcessing::EditorScrollControl(int command)
{
	switch (command)
	{
	case CMD_INCREASE:
		m_currentReviewData.GoToNextLineNumber();
		break;
	case CMD_DECREASE:
		m_currentReviewData.GoToPrevLineNumber();
		break;
	case CMD_GETCURRENTLINE:
		break;
	case CMD_INIT:
		m_currentReviewData.InitLineNumber();
		break;
	default:
		return 0;
	}
	return m_currentReviewData.GetLineNumber();
}

bool CDataProcessing::FillAllDataFromFile(CString filepath)
{
	CString content;

	ClearAllData();

	if (FindTemporaryFileDirectory() == false)
	{
		return false;
	}

	if (GetTextFromFile(filepath, content) == false)
	{
		return false;
	}

	SetReviewText(content);
	
	if (FillReviewData() == false)
	{
		return false;
	}
	
	return true;
}

bool CDataProcessing::GetReviewNCodeText(CString filepath, TextData& textData)
{
	for (auto iter = m_reviews.begin(); iter != m_reviews.end(); ++iter)
	{
		if (filepath.CompareNoCase(iter->GetFilePath()) == 0)
		{
			m_currentReviewData = *iter;
			m_currentReviewData.InitLineNumber();
			textData = iter->GetTextData();
			return true;
		}
	}

	return false;
}

bool CDataProcessing::ExportFileFromRepository(CString revision, CString filepath)
{
	CString command;
	STARTUPINFO startupInfomation = { 0 };
	PROCESS_INFORMATION processInfomation;
	BOOL result = false;
	startupInfomation.cb = sizeof(STARTUPINFO);
	// == for local test == //
	command.Format(L"svn export -r %s file:///%s%s %s", revision, m_url, filepath, m_sourceCodesFilePath);
	
	// == for extern server test == //
	//command.Format(L"svn export -r %s %s%s %s", revision, m_url, filepath, m_sourceCodesFilePath);

	result = CreateProcessW(NULL, (LPWSTR)(LPCWSTR)command, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &startupInfomation, &processInfomation);

	if (result == false)
	{
		CString errorStr;
		errorStr.Format(L"SVN 프로그램 실행 실패 - error : %d", GetLastError());
		::AfxMessageBox(errorStr, 0, 0);
		return false;
	}
	else
	{
		WaitForSingleObject(processInfomation.hProcess, INFINITE);
	}
	return true;
}

CString CDataProcessing::ExtractFileNameFromFilePath(CString filepath)
{
	int index = 0;
	CString tempString;
	CString parsedString;
	while ((parsedString = filepath.Tokenize(L"/", index)) != L"")
	{
		tempString = parsedString;
	}
	return tempString;

}

bool CDataProcessing::DeleteSourceCodeFile(CString filepath)
{
	DeleteFileW((LPCWSTR)filepath);

	return true;
}