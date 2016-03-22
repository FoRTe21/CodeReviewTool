#pragma once

#include <list>

class CReviewData
{
protected:
	CString m_filepath;
	CString m_revision;

	CString m_comments;
	CString m_sourceCode;
	std::list <int> m_lineNumber;
	std::list<int>::iterator m_lineNumberIter;

protected:
	CString GetComment();
	CString GetSourceCode();

public:
	CReviewData();
	~CReviewData();

	void SetFilePath(CString filepath);
	void SetRevision(CString revision);
	
	void SetSourceCode(CString sourceCode);
	void AddComments(CString comments);
	void AddLineNumber(int number);

	CString GetFilePath();
	CString GetRevision();
	
	int GetLineNumber();
	void GetReviewNSourceCode(CString* review, CString* sourceCode);
	void NextLineNumber();
	void PrevLineNumber();
	void InitLineNumber();
	void Clear();
};

