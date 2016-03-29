#pragma once
#include <list>
#include <vector>
#include "ReviewData.h"

class CDataProcessing final
{
public:
	enum Commands { CMD_INCREASE, CMD_DECREASE, CMD_GETCURRENTLINE, CMD_INIT };
	enum Encodings { UTF16, UTF16BIGENDIAN, UTF8, ANSI };

protected:
	CString m_reviewText;

	CString m_url;
	std::list<CString> m_revisions;
	std::list<CReviewData> m_reviews;

	CReviewData m_currentReviewData;
	
	CString m_sourceCodesFilePath;
	const CString m_temporaryFileDirectory = L"temporaryCodeDir";
protected:
	void ClearAllData();
	bool GetTextFromFile(CString filepath, CString& contents);
	bool FillReviewData();
	void SetReviewText(CString text);
	int AddLineNumbers(CString numbers, CReviewData& reviewData);
	Encodings CheckEncoding(CFile& file);
	bool ExportFileFromRepository(CString revision, CString filepath);
	CString ExtractFileNameFromFilePath(CString filepath);
	bool DeleteSourceCodeFile(CString filepath);
	bool FindTemporaryFileDirectory();

	
	template<typename BufferType> std::vector<BufferType> ReadFile(CFile& reviewFile);
	
	CString ReadANSIFile(CFile& reviewFile);
	CString ReadUTF16LeFile(CFile& reviewFile);
	CString ReadUTF16BeFile(CFile& reviewFile);
	CString ReadUTF8File(CFile& reviewFile);

	WCHAR ConvertWCHAREndian(WCHAR data);
public:
	CDataProcessing();
	~CDataProcessing();

	const std::list<CString> GetRivisions() const;
	const std::list<CReviewData> GetReviews() const;

	int EditorScrollControl(int command);

	bool FillAllDataFromFile(CString filepath);
	bool GetReviewNCodeText(CString filepath, TextData& textData);

	bool InitDataProcessor();
};

