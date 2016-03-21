#pragma once

#include <list>

class CReviewData
{
protected:
	CString m_filepath;
	CString m_revision;

	CString m_comments;
	CString m_sourceCode;

public:
	CReviewData();
	~CReviewData();

	void SetFilePath(CString filepath);
	void SetRevision(CString revision);
	void SetSourceCode(CString sourceCode);
	void AddComments(CString comments);

	CString GetFilePath();
	CString GetRevision();
	CString GetComment();
	CString GetSourceCode();
	void Clear();
};

