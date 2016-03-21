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
	CReviewData rd;

	bool sameFileFlag = false, cmtStartFlag = false;

	oneLine = m_reviewText.Tokenize(L"\r\n", index);
	tmpString = oneLine.Tokenize(L": ", tmpIndex);

	if (tmpString.CompareNoCase(L"url") != 0)
	{
		return false;
	}

	m_url = oneLine;

	while ((oneLine = m_reviewText.Tokenize(L"\r\n", index)) != L"")
	{
		tmpString = oneLine.GetAt(0);
		if (tmpString.CompareNoCase(L"R") == 0)
		{
			if (sameFileFlag == true)
			{
				rd.SetRevision(revision);
				m_reviews.push_back(rd);
				rd.Clear();
				rd.AddComments(L"\r\n");
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
				rd.Clear();
				rd.SetFilePath(oneLine);
				rd.SetRevision(revision);
				oneLine.Delete(0, 3);
				GetTextFromFile((LPWSTR)(LPCWSTR)oneLine, content);
				rd.SetSourceCode(content);
				rd.AddComments(L"\r\n");
			}
			else
			{
				CString content;
				rd.SetRevision(revision);
				m_reviews.push_back(rd);
				rd.Clear();
				rd.SetFilePath(oneLine);
				oneLine.Delete(0, 3);
				GetTextFromFile((LPWSTR)(LPCWSTR)oneLine, content);
				rd.SetSourceCode(content);
				rd.AddComments(L"\r\n");
			}
		}
		else
		{
			rd.AddComments(oneLine);
		}
	}

	if (sameFileFlag == true)
	{
		rd.SetRevision(revision);
		m_reviews.push_back(rd);
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

CString CDataProcessing::GetReview(CString filepath)
{
	std::list<CReviewData>::iterator iter;

	for (iter = m_reviews.begin(); iter != m_reviews.end(); iter++)
	{
		if (filepath.CompareNoCase(iter->GetFilePath()) == 0)
		{
			return iter->GetComment();
		}
	}

	return NULL;
}

CString CDataProcessing::GetSourceCode(CString filepath)
{
	std::list<CReviewData>::iterator iter;

	for (iter = m_reviews.begin(); iter != m_reviews.end(); iter++)
	{
		if (filepath.CompareNoCase(iter->GetFilePath()) == 0)
		{
			return iter->GetSourceCode();
		}
	}

	return NULL;
}

void CDataProcessing::SetReviewText(CString text)
{
	m_reviewText = text;
}