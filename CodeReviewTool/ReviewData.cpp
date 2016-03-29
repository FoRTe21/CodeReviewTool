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

const CString CReviewData::GetFilePath() const
{
	return m_filepath;
}

const CString CReviewData::GetRevision() const
{
	return m_revision;
}

const CString CReviewData::GetComment() const
{
	return m_comments;
}

void CReviewData::SetSourceCode(CString sourceCode)
{
	m_sourceCode = sourceCode;
}

const CString CReviewData::GetSourceCode() const
{
	return m_sourceCode;
}

void CReviewData::AddLineNumber(int number)
{
	m_lineNumber.push_back(number);
}

const int CReviewData::GetLineNumber() const
{
	return (*m_lineNumberIter);
}

void CReviewData::GoToNextLineNumber()
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

void CReviewData::GoToPrevLineNumber()
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

const TextData CReviewData::GetTextData() const
{
	TextData textData;
	textData.m_strComments = m_comments;
	textData.m_strSourceCode = m_sourceCode;

	return textData;
}