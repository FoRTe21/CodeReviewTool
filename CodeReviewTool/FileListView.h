#pragma once
#include "afxwin.h"
//#include "MainFrm.h"
#include <list>
// CFileListView 대화 상자입니다.

class CReviewData;

class CFileListView : public CDialogEx
{
	DECLARE_DYNAMIC(CFileListView)
protected:
	std::list<CReviewData>* m_reviews;
	std::list<CString>* m_revisions;

	CListBox m_revisionLB;
	CListBox m_fileNameLB;

public:
	CFileListView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFileListView();

	void InitRevisions(std::list<CString>* revisions);
	void InitReviews(std::list<CReviewData>* reviews);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILESELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	
	void ClearFileNameLB();
	void ClearRevisionLB();
	void ViewFileListByIndex(int index);
	virtual void PostNcDestroy();
public:
	afx_msg void OnClose();
	afx_msg void OnLbnSelchangeRevision();
	afx_msg void OnLbnDblclkCodefile();
};
