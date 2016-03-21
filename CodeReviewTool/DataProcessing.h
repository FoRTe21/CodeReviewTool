#pragma once
#include <list>
#include "ReviewData.h"

class CDataProcessing
{
protected:
	CString m_reviewText;

	CString m_url;
	std::list<CString> m_revisions;
	std::list<CReviewData> m_reviews;

protected:
	CString ConvertMultibyteToUnicode(LPSTR pMultibyte);
	

public:
	CDataProcessing();
	~CDataProcessing();
	void ClearAllData();
	
	bool GetTextFromFile(LPWSTR filepath, CString& contents);
	bool FillReviewData();

	std::list<CString>* GetRivisions();
	std::list<CReviewData>* GetReviews();

	CString GetReview(CString filepath);
	CString GetSourceCode(CString filepath);

	void SetReviewText(CString text);
};

