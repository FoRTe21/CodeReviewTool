#include "stdafx.h"
#include "ReviewData.h"


CReviewData::CReviewData()
{
}


CReviewData::~CReviewData()
{
}

void CReviewData::SetFilePath(CString filepath)
{
	m_filepath = filepath;
}

void CReviewData::SetRevision(CString revision)
{
	m_revision = revision;
}

void CReviewData::AddComments(CString comments)
{
		m_comments.AppendFormat(L"%s\r\n", comments);
}

void CReviewData::Clear()
{
	m_filepath.Empty();
	m_revision.Empty();
	m_comments.Empty();

	m_lineNumber.clear();
	m_lineNumberIter = m_lineNumber.begin();
}

CString CReviewData::GetFilePath()
{
	return m_filepath;
}

CString CReviewData::GetRevision()
{
	return m_revision;
}

CString CReviewData::GetComment()
{
	return m_comments;
}

void CReviewData::SetSourceCode(CString sourceCode)
{
	m_sourceCode = sourceCode;
}

CString CReviewData::GetSourceCode()
{
	return m_sourceCode;
}

void CReviewData::AddLineNumber(int number)
{
	m_lineNumber.push_back(number);
}

int CReviewData::GetLineNumber()
{
	return (*m_lineNumberIter);
}

void CReviewData::NextLineNumber()
{
	if (m_lineNumberIter != m_lineNumber.end())
	{
		++m_lineNumberIter;
	}
	if (m_lineNumberIter == m_lineNumber.end())
	{
		--m_lineNumberIter;
	}
}

void CReviewData::PrevLineNumber()
{
	if (m_lineNumberIter != m_lineNumber.begin())
	{
		--m_lineNumberIter;
	}
}

void CReviewData::InitLineNumber()
{
	m_lineNumberIter = m_lineNumber.begin();
}

void CReviewData::GetReviewNSourceCode(CString* review, CString* sourceCode)
{
	if (review != NULL)
	{
		*review = m_comments;
	}
	if (sourceCode != NULL)
	{
		*sourceCode = m_sourceCode;
	}
}