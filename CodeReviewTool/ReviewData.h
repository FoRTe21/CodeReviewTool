#pragma once

#include <list>

struct TextData
{
	CString m_strComments;
	CString m_strSourceCode;
};

class CReviewData final
{
protected:
	CString m_filepath;
	CString m_revision;

	CString m_comments;
	CString m_sourceCode;
	std::list <int> m_lineNumber;
	std::list<int>::iterator m_lineNumberIter;

protected:
	const CString GetComment() const;
	const CString GetSourceCode() const;

public:
	CReviewData();
	~CReviewData();

	void SetFilePath(CString filepath);
	void SetRevision(CString revision);
	
	void SetSourceCode(CString sourceCode);
	void AddComments(CString comments);
	void AddLineNumber(int number);

	const CString GetFilePath() const;
	const CString GetRevision() const;
	
	const int GetLineNumber() const;
	const TextData GetTextData() const;
	void GoToNextLineNumber();
	void GoToPrevLineNumber();
	void InitLineNumber();
	void Clear();
};

