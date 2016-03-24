#pragma once
#include <list>
#include "ReviewData.h"


class CDataProcessing
{
public:
	enum Commands { CMD_INCREASE, CMD_DECREASE, CMD_GETCURRENTLINE, CMD_INIT };
	enum Encodings { UNICODE_, UNICODE_BIGENDIAN, UTF8, ANSI };

protected:
	CString m_reviewText;

	CString m_url;
	std::list<CString> m_revisions;
	std::list<CReviewData> m_reviews;

	CReviewData* m_currentReviewData;
	CString m_sourceCodesFilePath;

protected:
	CString ConvertMultibyteToUnicode(LPSTR pMultibyte);
	void ClearAllData();
	bool GetTextFromFile(CString filepath, CString& contents);
	bool FillReviewData();
	void SetReviewText(CString text);
	int AddLineNumbers(CString numbers, CReviewData* reviewData);
	int CheckEncoding(CFile* file);
	bool ExportFileFromRepository(CString revision, CString filepath);
	CString ExtractFileNameFromFilePath(CString filepath);
	bool DeleteSourceCodeFile(CString filepath);

public:
	CDataProcessing();
	~CDataProcessing();

	std::list<CString>* GetRivisions();
	std::list<CReviewData>* GetReviews();

	int EditorScrollControl(int command);
	

	bool FillAllDataFromFile(CString filepath);
	bool GetReviewNCodeText(CString filepath, CString* reviewText, CString* sourceCodeText);
};

