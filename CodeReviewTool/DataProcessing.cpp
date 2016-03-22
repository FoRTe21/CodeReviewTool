#include "stdafx.h"
#include "DataProcessing.h"


CDataProcessing::CDataProcessing()
{
	m_reviewText.Empty();
}


CDataProcessing::~CDataProcessing()
{

}

bool CDataProcessing::GetTextFromFile(LPWSTR filepath, CString& contents)
{
	CFile reviewFile;
	LPSTR buffer = NULL;
	int fileSize = 0;

	if (reviewFile.Open(filepath, CFile::modeRead, 0) == NULL)
	{
		return false;
	}
	
	fileSize = reviewFile.GetLength();

	buffer = new char[fileSize + 1];
	buffer[fileSize] = '\0';

	reviewFile.Read(buffer, reviewFile.GetLength());

	contents = ConvertMultibyteToUnicode(buffer);

	delete[] buffer;
	reviewFile.Close();
	
	return true;
}

int CheckEncoding(CFile* file, LPSTR buffer)
{
	unsigned char encodingHeader[2] = { 0, };
	DWORD encodingType = 0;

	file->Read(encodingHeader, 2);

	if (encodingHeader[0] == 0xff && encodingHeader[1] == 0xfe)
	{
		encodingType = UNICODE_;
	}
	else if (encodingHeader[0] == 0xfe && encodingHeader[1] == 0xff)
	{
		encodingType = UNICODE_BIGENDIAN;
	}
	else if (encodingHeader[0] == 0xef && encodingHeader[1] == 0xbb)
	{
		file->Read(encodingHeader, 1);
		if (encodingHeader[0] == 0xbf)
		{
			encodingType = UTF8;
		}
	}
	else
	{
		encodingType = ANSI;
	}
	file->SeekToBegin();

	return encodingType;
}

void CDataProcessing::ClearAllData()
{
	std::list<CReviewData>::iterator iter;

	m_reviewText.Empty();
	m_url.Empty();
	m_revisions.clear();
	for (iter = m_reviews.begin(); iter != m_reviews.end(); iter++)
	{
		iter->Clear();
	}
	m_reviews.clear();
}

CString CDataProcessing::ConvertMultibyteToUnicode(LPSTR pMultibyte)
{
	int nLen = strlen(pMultibyte);

	WCHAR *pWideChar = new WCHAR[nLen];
	memset(pWideChar, 0x00, (nLen)*sizeof(WCHAR));

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pMultibyte, -1, pWideChar, nLen);

	CString strUnicode;
	strUnicode.Format(L"%s", pWideChar);

	delete[] pWideChar;

	return strUnicode;
}

bool CDataProcessing::FillReviewData()
{
	CString oneLine, tmpString, revision, tmpComment;
	int index = 0, tmpIndex = 0;
	CReviewData tempReviewData;
	bool sameFileFlag = false;

	oneLine = m_reviewText.Tokenize(L"\r\n", index);
	tmpString = oneLine.Tokenize(L": ", tmpIndex);

	if (tmpString.CompareNoCase(L"url") == 0)
	{
		m_url = oneLine;
	}
	else
	{
		return false;
	}

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
			revision = oneLine;
			m_revisions.push_back(revision);
		}
		else if (tmpString.CompareNoCase(L"*") == 0)
		{
			if (sameFileFlag == false)
			{
				CString content;
				sameFileFlag = true;
				tempReviewData.Clear();
				tempReviewData.SetFilePath(oneLine);
				tempReviewData.SetRevision(revision);
				oneLine.Delete(0, 3);
				GetTextFromFile((LPWSTR)(LPCWSTR)oneLine, content);
				tempReviewData.SetSourceCode(content);
				tempReviewData.AddComments(L"\r\n");
			}
			else
			{
				CString content;
				tempReviewData.SetRevision(revision);
				m_reviews.push_back(tempReviewData);
				tempReviewData.Clear();
				tempReviewData.SetFilePath(oneLine);
				oneLine.Delete(0, 3);
				GetTextFromFile((LPWSTR)(LPCWSTR)oneLine, content);
				tempReviewData.SetSourceCode(content);
				tempReviewData.AddComments(L"\r\n");
			}
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
						AddLineNumbers(tmpString.Tokenize(L":", i), &tempReviewData);
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

std::list<CString>* CDataProcessing::GetRivisions()
{
	return &m_revisions;
}

std::list<CReviewData>* CDataProcessing::GetReviews()
{
	return &m_reviews;
}

void CDataProcessing::SetReviewText(CString text)
{
	m_reviewText = text;
}

int CDataProcessing::AddLineNumbers(CString numbers, CReviewData* reviewData)
{
	CString number;
	int index = 0, count = 0;
	numbers.Delete(0, 2);

	while ((number = numbers.Tokenize(L",", index)) != "")
	{
		++count;
		reviewData->AddLineNumber(_ttoi(number));
	}

	return count;
}

int CDataProcessing::EditorScrollControl(int command)
{
	switch (command)
	{
	case CMD_INCREASE:
	{
		m_currentReviewData->NextLineNumber();
		break;
	}
	case CMD_DECREASE:
	{
		m_currentReviewData->PrevLineNumber();
		break;
	}
	case CMD_GETCURRENTLINE:
	{
		break;
	}
	case CMD_INIT:
	{
		m_currentReviewData->InitLineNumber();
		break;
	}
	default:
	{
		return 0;
	}
	}
	return m_currentReviewData->GetLineNumber();
}

bool CDataProcessing::FillAllDataFromFile(LPWSTR filepath)
{
	CString content;

	ClearAllData();
	if (GetTextFromFile(filepath, content) == false)
	{
		return false;
	}
	SetReviewText(content);
	if (FillReviewData() == false)
	{
		return false;
	}
}

bool CDataProcessing::GetReviewNCodeText(CString filepath, CString* reviewText, CString* sourceCodeText)
{
	std::list<CReviewData>::iterator iter;

	for (iter = m_reviews.begin(); iter != m_reviews.end(); iter++)
	{
		if (filepath.CompareNoCase(iter->GetFilePath()) == 0)
		{
			m_currentReviewData = (CReviewData*)&(*iter);
			m_currentReviewData->InitLineNumber();
			iter->GetReviewNSourceCode(reviewText, sourceCodeText);
			return true;
		}
	}

	return false;
}