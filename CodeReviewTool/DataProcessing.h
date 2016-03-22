#pragma once
#include <list>
#include "ReviewData.h"

enum Commands{ CMD_INCREASE, CMD_DECREASE, CMD_GETCURRENTLINE, CMD_INIT };
enum Encodings { UNICODE_, UNICODE_BIGENDIAN, UTF8, ANSI };
class CDataProcessing
{
protected:
	CString m_reviewText;

	CString m_url;
	std::list<CString> m_revisions;
	std::list<CReviewData> m_reviews;

	CReviewData* m_currentReviewData;
protected:
	CString ConvertMultibyteToUnicode(LPSTR pMultibyte);
	void ClearAllData();
	bool GetTextFromFile(LPWSTR filepath, CString& contents);
	bool FillReviewData();
	void SetReviewText(CString text);
	int AddLineNumbers(CString numbers, CReviewData* reviewData);
	int CheckEncoding(CFile* file, LPSTR buffer);

public:
	CDataProcessing();
	~CDataProcessing();

	std::list<CString>* GetRivisions();
	std::list<CReviewData>* GetReviews();

	int EditorScrollControl(int command);
	

	bool FillAllDataFromFile(LPWSTR filepath);
	bool GetReviewNCodeText(CString filepath, CString* reviewText, CString* sourceCodeText);
};

