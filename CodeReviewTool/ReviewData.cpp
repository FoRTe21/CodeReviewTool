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
	filepath.Delete(0, 3);
	m_filepath = filepath;
}

void CReviewData::SetRevision(CString revision)
{
	m_revision = revision;
}

void CReviewData::AddComments(CString comments)
{
	if (m_comments.IsEmpty())
	{
		m_comments.Format(L"%s\r\n", comments);
	}
	else
	{
		m_comments.AppendFormat(L"%s\r\n", comments);
	}
}

void CReviewData::Clear()
{
	m_filepath.Empty();
	m_revision.Empty();
	m_comments.Empty();
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